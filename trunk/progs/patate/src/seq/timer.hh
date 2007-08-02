/*
** timer.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 10:37:09 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
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

#ifndef   	TIMER_HH_
# define   	TIMER_HH_

#include <time.h>

namespace Seq
{

  class Timer
  {
  public:
    Timer(unsigned int a_bpm, unsigned int a_ppq, unsigned int a_sr);
    void                  set_ppq(unsigned int a_ppq);
    void                  set_bpm(unsigned int a_bpm);
    void                  samples_elapsed(unsigned int samples); /// \todo find better name.
    uint64_t              samples();
    uint64_t              ticks();
  protected:
    void                  update_tick_len();

    unsigned int          m_bpm;
    unsigned int          m_ppq;
    unsigned int          m_sample_rate;

    uint64_t              m_samples;
    double                m_tick_len;
  };

};

#endif	    /* !TIMER_HH_ */
