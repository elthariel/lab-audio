/*
** synth_manager.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri May 18 00:43:47 2007 Nahlwe
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

#ifndef   	SYNTH_MANAGER_HH_
# define   	SYNTH_MANAGER_HH_

#include <vector>
#include <seq/iSynth.hh>
#include "iSynth.hh"

class SynthManager : public Seq::iSynthContainer
{
public:
  SynthManager(unsigned int size);
  virtual ~SynthManager();

  virtual unsigned int          get_synth_count();
  //virtual void                  set_sample_rate(unsigned int a_sr);
  virtual Seq::iSynth           *synth(unsigned int i);
  virtual void                  synth(unsigned int i, Seq::iSynth &a_synth);
protected:
  std::vector<Seq::iSynth *>    m_synths;
};

#endif	    /* !SYNTH_MANAGER_HH_ */
