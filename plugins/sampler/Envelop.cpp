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
///////////////////// Envelop base class /////////////////////////////
//////////////////////////////////////////////////////////////////////

void                    Envelop::note_on(char note, char vel)
{
  m_note = note;
  m_vel = vel;
}

void                    Envelop::note_off()
{
  m_note = -1;
  m_vel = 0;
}

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

double                  EnvD::operator()(unsigned int position,
                                         char mode)
{
  double                res;

  res = 1.0 - m_a * position;
  if (res < 0.0)
    return (0.0);
  else
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

double          		EnvH::operator()(unsigned int x,
                                     char mode)
{
  if ((x < (m_hold * m_beat_length)) && (mode == EnvModeOn))
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

EnvDahdsr::EnvDahdsr(unsigned int sample_rate, unsigned int tempo)
  : m_bpm(tempo), m_sr(sample_rate)
{
  m_beat_length = (60.0 / tempo) * m_sr;
  m_coefs_beat[0] = 1.0;
  m_coefs_beat[1] = 1.0;
  m_coefs_beat[2] = 1.0;
  m_coefs_beat[3] = 1.0;
  m_coefs_beat[4] = 1.0;
  m_coefs_beat[5] = 1.0;

  compute_coefs();
}

void                    EnvDahdsr::set_coefs(double *coefs, unsigned int coef_count)
{
  unsigned int          i;

  if (coefs && coef_count)
    {
      for (i = 0; i < coef_count; i++)
        m_coefs_beat[i] = coefs[i];
      compute_coefs();
    }
}

void                    EnvDahdsr::compute_coefs()
{
  //Compute Delay (nothing to compute
  m_coefs[0] = m_coefs_beat[0] * m_beat_length;
  //Compute attack
  m_coefs[1] = 1.0 / (m_coefs_beat[1] * m_beat_length);
  // Hold -> do not use
  m_coefs[2] = 1.0;
  // Decay
  m_coefs[3] = -((1.0 - m_coefs_beat[4]) / (m_coefs[3] * m_beat_length));
  // Sustain
  m_coefs[4] = m_coefs_beat[4];
  // Release
  m_coefs[5] = m_coefs_beat[5] * m_beat_length;
}

double                  EnvDahdsr::operator()(unsigned int index,
                                              char mode)
{
  if (m_note == EnvModeOn)
    {
      if (index < m_coefs[0])
        return (0.0);
      else if (index < (m_coefs[0] + m_coefs[1] * m_beat_length))
        return ((index - m_coefs[0]) * m_coefs[1]);
      else if (index < (m_coefs[0] + m_coefs_beat[1] * m_beat_length +
                        m_coefs_beat[2] * m_beat_length ))
        return (1.0);
      else if (index < (m_coefs[0] + m_coefs_beat[1] * m_beat_length +
                        m_coefs_beat[2] * m_beat_length +
                        m_coefs_beat[3] * m_beat_length))
        return(1.0 - (index - (m_coefs[0] + m_coefs_beat[1] * m_beat_length +
                               m_coefs_beat[2] * m_beat_length)) * m_coefs[3]);
      else
        return (m_coefs[4]);
    }
  else
    {
      double res = m_coefs[4] -
        m_coefs[5] * (index);
      if (res < 0.0)
        return (0.0);
      else
        return (res);
    }
}

// void                    EnvDahdsr::note_on(char note, char vel)
// {
//   m_note = note;
//   m_vel = vel;
//   m_note_off_index = 0;
// }
// void                    EnvDahdsr::note_off()
// {
//   m_note = -1;
// }

//////////////////////////////////////////////////////////////////////
//////////////////////// EnvSwitch ///////////////////////////////////
//////////////////////////////////////////////////////////////////////

EnvSwitch::EnvSwitch(unsigned int sample_rate, unsigned int tempo)
  : m_bpm(tempo), m_sr(sample_rate), m_current_env(-1),
  	Envelop(sample_rate, tempo)
{
}

void                    EnvSwitch::note_on(char note, char vel)
{
  vector<Envelop *>::iterator iter;

  for (iter = m_envs.begin(); iter != m_envs.end(); iter++)
    {
      (*iter)->note_on(note, vel);
    }
}

void                    EnvSwitch::note_off()
{
  vector<Envelop *>::iterator iter;

  for (iter = m_envs.begin(); iter != m_envs.end(); iter++)
    {
      (*iter)->note_off();
    }
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

double                  EnvSwitch::operator()(unsigned int env_pos,
                                              char mode)
{
  if (m_current_env < 0)
    {
      if (mode == EnvModeOn)
        return (1.0);
      else
        return (0.0);
    }
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
  esw->add_envelop(new EnvDahdsr(sample_rate, tempo));

  return esw;
}
