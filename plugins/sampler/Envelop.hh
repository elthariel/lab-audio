/*
** Envelop.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Sun Jan 14 03:23:42 2007 Elthariel
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

#ifndef   	ENVELOP_HH_
# define   	ENVELOP_HH_

#include <vector>

class Envelop
{
  Envelop(){}

public:
  Envelop(unsigned int, unsigned int){} //sample_rate, tempo

  virtual double                operator()(unsigned int) = 0;
  virtual void                  set_coefs(double *,
                                          unsigned int coef_count) = 0;

};

class EnvSwitch : public Envelop
{
  unsigned int          m_bpm;
  unsigned int          m_sr;
  int                   m_current_env;
  vector<Envelop *>     m_envs;

public:
  EnvSwitch(unsigned int, unsigned int);

  unsigned int          add_envelop(Envelop *, int = -1);

  void                  set_envelop(int);
  virtual double        operator()(unsigned int);
  virtual void          set_coefs(double *,
                                  unsigned int coef_count = 1);

  static EnvSwitch      *create_switch_full(unsigned int, unsigned int);
};

// Decay only envelop.
class EnvD : public Envelop
{
  unsigned int                  m_bpm;
  unsigned int                  m_sr;

  double                        m_decay;        //decay time in beat
  double                        m_a;
  unsigned int                  m_beat_length; //beat length in sample

  void                          compute_a();
public:
  EnvD(unsigned int, unsigned int);

  virtual double                operator()(unsigned int);
};

class EnvH : public Envelop
{
  unsigned int                  m_bpm;
  unsigned int                  m_sr;

  double                        m_hold;         //hold time in beat
  unsigned int                  m_beat_length; //beat length in sample

public:
  EnvH(unsigned int, unsigned int);

  virtual double                operator()(unsigned int);

};

/*
// 'Delay Attack Hold Decay Sustain Release' Envelop
class EnvDahdsr : public Envelop
{
  unsigned int                  m_bpm;
  unsigned int                  m_sr;

  double                        coefs[6]
public:
  EnvDahdsr(unsigned int, unsigned int);

  virtual double                operator()(unsigned int);
};
*/

#endif	    /* !ENVELOP_HH_ */
