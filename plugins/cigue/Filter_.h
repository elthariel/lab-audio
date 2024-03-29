/*
  ZynAddSubFX - a software synthesizer

  Filter_.h - This class is inherited by filter classes
  Copyright (C) 2002-2005 Nasca Octavian Paul
  Author: Nasca Octavian Paul

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License (version 2) for more details.

  You should have received a copy of the GNU General Public License (version 2)
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/

#ifndef FILTER__H
#define FILTER__H

# define REALTYPE float
# define MAX_FILTER_STAGES 3
# define PI 3.14159265358979323846

/*
 * dB
 */
# define LOG_10 2.302585093
# define dB2rap(dB) ((exp((dB)*LOG_10/20.0)))
# define rap2dB(rap) ((20*log(rap)/LOG_10))


class Filter_{
 public:
  virtual ~Filter_(){};
  virtual void filterout(REALTYPE *smp){};
  virtual void setfreq(REALTYPE frequency){};
  virtual void setfreq_and_q(REALTYPE frequency,REALTYPE q_){};
  virtual void setq(REALTYPE q_){};
  virtual void setgain(REALTYPE dBgain){};
  REALTYPE outgain;
 private:
};


#endif

