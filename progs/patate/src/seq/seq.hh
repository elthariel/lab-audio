/*
** seq.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Apr 27 02:08:49 2007 Nahlwe
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

#ifndef   	SEQ_HH_
# define   	SEQ_HH_

# include <vector>
# include "timer.hh"
# include "part.hh"

namespace Seq
{
  class Seq
  {
  public:
    Seq(unsigned int a_bpm, unsigned int a_ppq,
        unsigned int a_part_count, unsigned int a_bar_count,
        iSynthContainer &a_sampler);
    ~Seq();

    void                run();
    Part                &part(unsigned int part_id);
    void                set_bpm(unsigned int a_bpm);
    void                set_ppq(unsigned int a_ppq);
    void                start();
    void                pause();
    void                stop();
    bool                paused();
    bool                started();
  protected:
    Timer               m_timer;
    iSynthContainer     &m_synths;
    std::vector<Part *> m_parts;
    unsigned int        m_part_count;
    unsigned int        m_bar_count;
    unsigned int        m_ppq;
    unsigned int        m_pos;
  };
};

#endif	    /* !SEQ_HH_ */
