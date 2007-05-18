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

namespace Dsp
{
enum EnvMode
  {
    EnvModeOn,
    EnvModeRelease,
    EnvModeCount
  };

class iEnvelop
{
protected:
  iEnvelop(): m_note(-1), m_vel(0){}

  char                          m_note;
  char                          m_vel;

public:
  virtual ~iEnvelop();
  iEnvelop(unsigned int, unsigned int): m_note(-1), m_vel(0){} //sample_rate, tempo

  virtual double                operator()(unsigned int, EnvMode = EnvModeOn) = 0;
  virtual void                  set_coefs(double *,
                                          unsigned int coef_count) = 0;
  virtual void                  note_on(char note, char vel);
  virtual void                  note_off();

};

//FIXME add destructor
class EnvSwitch : public iEnvelop
{
  unsigned int          m_bpm;
  unsigned int          m_sr;
  int                   m_current_env;
  std::vector<iEnvelop *> m_envs;

public:
  EnvSwitch(unsigned int, unsigned int);
  virtual ~EnvSwitch();

  unsigned int          add_envelop(iEnvelop *, int = -1);

  void                  set_envelop(int);
  virtual double        operator()(unsigned int, EnvMode = EnvModeOn);
  virtual void          set_coefs(double *,
                                  unsigned int coef_count = 1);
  virtual void          note_on(char note, char vel);
  virtual void          note_off();

  static EnvSwitch      *create_switch_full(unsigned int, unsigned int);
};

// Decay only envelop.
class EnvD : public iEnvelop
{
  unsigned int                  m_bpm;
  unsigned int                  m_sr;

  double                        m_decay;        //decay time in beat
  double                        m_a;
  unsigned int                  m_beat_length; //beat length in sample

  void                          compute_a();
  void							set_decay(double);
public:
  EnvD(unsigned int, unsigned int);
  virtual ~EnvD();

  virtual double                operator()(unsigned int, EnvMode = EnvModeOn);
  virtual void                  set_coefs(double *coefs,
                                          unsigned int coef_count = 1);
};

class EnvH : public iEnvelop
{
  unsigned int                  m_bpm;
  unsigned int                  m_sr;

  double                        m_hold;         //hold time in beat
  unsigned int                  m_beat_length; //beat length in sample

  void							set_hold(double);
public:
  EnvH(unsigned int, unsigned int);
  virtual ~EnvH();

  virtual double                operator()(unsigned int, EnvMode = EnvModeOn);
  virtual void                  set_coefs(double *coefs,
                                          unsigned int coef_count = 1);
};


// 'Delay Attack Hold Decay Sustain Release' Envelop
class EnvDahdsr : public iEnvelop
{
  unsigned int                  m_bpm;
  unsigned int                  m_sr;

  double                        m_coefs_beat[6]; // Env coef in beat.
  double                        m_coefs[6];      // Env curve maths coefs.
  double                        m_beat_length;

  void                          compute_coefs();
public:
  EnvDahdsr(unsigned int, unsigned int);
  virtual ~EnvDahdsr();

  virtual double                operator()(unsigned int, EnvMode = EnvModeOn);
  virtual void                  set_coefs(double *coefs,
                                          unsigned int coef_count = 1);
  //  virtual void                  note_on(char note, char vel);
  //  virtual void                  note_off();
};

};
#endif	    /* !ENVELOP_HH_ */
