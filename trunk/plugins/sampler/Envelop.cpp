/*
** Envelop.cc
** Login : <elthariel@localhost.localdomain>
** Started on  Sun Jan 14 03:24:04 2007 Elthariel
** $Id$
**
** Copyright (C) 2007 Elthariel
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include "Envelop.hh"

using namespace std;

//////////////////////////////////////////////////////////////////////
///////////////////// EnvDecay ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////


EnvD::EnvD(unsigned int sample_rate, unsigned int tempo)
  : m_bpm(tempo), m_sr(sample_rate), m_decay(2.0),
  	Envelop(sample_rate, tempo)
{
  //FIXME may be the wrong formula.
  m_beat_length = (60.0 / m_bpm) * m_sr;

  compute_a();
}

void                    EnvD::compute_a()
{
  double                total_length;

  total_length = m_decay * m_beat_length;
  m_a = 1.0 / total_length;
}

double                  EnvD::operator()(unsigned int position)
{
  double                res;
  double                pos_sec;

  pos_sec = position * (1.0 / m_sr);
  res = pos_sec * m_a;
  return (res);
}

void                    EnvD::set_decay(double decay)
{
  //FIXME do bound check
  m_decay = decay;
  compute_a();
}

void                    EnvD::set_coefs(double *coefs,
                                        unsigned int coef_count)
{
  if (coef_count)
    set_decay(coefs[0]);
}


//////////////////////////////////////////////////////////////////////
//////////////////////// EnvHold /////////////////////////////////////
//////////////////////////////////////////////////////////////////////


EnvH::EnvH(unsigned int sample_rate, unsigned int tempo)
  : m_bpm(tempo), m_sr(sample_rate), m_hold(2.0)
{
  m_beat_length = (60.0 / tempo) * m_sr;
}

double          		EnvH::operator()(unsigned int x)
{
  if (x < (m_hold * m_beat_length))
    return (1.0);
  else
    return (0.0);
}

void                    EnvH::set_hold(double hold)
{
  m_hold = hold;
}

void                    EnvH::set_coefs(double *coefs,
                                        unsigned int coef_count)
{
  if (coef_count)
    set_hold(coefs[0]);
}


//////////////////////////////////////////////////////////////////////
//////////////////////// EnvDahdsr ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//////////////////////// EnvSwitch ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

EnvSwitch::EnvSwitch(unsigned int sample_rate, unsigned int tempo)
  : m_bpm(tempo), m_sr(sample_rate), m_current_env(-1),
  	Envelop(sample_rate, tempo)
{
}

void                    EnvSwitch::set_envelop(int env)
{
  if (env < m_envs.size())
    {
      m_current_env = env;
    }
}

// pos < 0 -> next free offset, if pos exist, the item at that pos will be replaced.
unsigned int            EnvSwitch::add_envelop(Envelop *env, int position)
{
  unsigned int          actual_position;
  bool                  replacing = false;

  if (position < 0)
    actual_position = m_envs.size();
  else if (position < m_envs.size())
    {
      actual_position = position;
      replacing = true;
    }
  else
    actual_position = m_envs.size();

  if (replacing)
    delete m_envs[position];
  cout << "actual position " << actual_position << endl;
  m_envs.push_back(env);

  return (actual_position);
}

double                  EnvSwitch::operator()(unsigned int env_pos)
{
  if (m_current_env < 0)
    return (1.0);
  else
    return ((*m_envs[m_current_env])(env_pos));
}

void                    EnvSwitch::set_coefs(double *coefs,
                                             unsigned int coef_count)
{
  if (m_current_env >= 0)
    {
      m_envs[m_current_env]->set_coefs(coefs, coef_count);
    }
}

EnvSwitch               *EnvSwitch::create_switch_full(unsigned int sample_rate,
                                                       unsigned int tempo)
{
  EnvSwitch             *esw;

  esw = new EnvSwitch(sample_rate, tempo);
  esw->add_envelop(new EnvD(sample_rate, tempo));
  esw->add_envelop(new EnvH(sample_rate, tempo));

  return esw;
}
