/*
** part.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Thu Apr 26 12:50:29 2007 Nahlwe
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

#ifndef   	PART_HH_
# define   	PART_HH_

# include <list>
# include "iSynth.hh"

namespace Seq
{
# define NOTE_PARAMS    4

  struct Note
  {
    Note();
    char                note;
    char                vel;
    unsigned int        start;
    unsigned int        len;
    unsigned int        rem;
    float               param[NOTE_PARAMS];
  };

  class Part
  {
    /*
     * TODO : take m_res in count.
     */
  public:
    Part(unsigned int a_ppq, iSynth *a_synth = 0,
         unsigned int a_seq_len = 1, int a_res = 1);
    ~Part();

    void                        play(unsigned int a_pos,
                                unsigned int a_tick);
    void                        flush();
    void                        add_note(Note &a_note);
    bool                        rem_note(unsigned int a_begin = 0,
                                         unsigned int a_end = 0);

    const std::list<Note *>     &get_seq() const;
    void                        set_mres(int a_res = 1);
    void                        set_synth(iSynth *a_synth = 0);

  protected:
    void                        update_note_on(unsigned int a_tick);
    void                        insert_note_on(Note *);

    std::list<Note *>   m_seq;
    std::list<Note *>   m_note_on;
    iSynth              *m_synth;
    unsigned int        m_seq_len;
    unsigned int        m_current_tick;
    int                 m_res;
    unsigned int        m_ppq;
  };
};

#endif	    /* !PART_HH_ */
