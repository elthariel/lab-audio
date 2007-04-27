/*
** drumseqview.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Wed Apr 11 14:37:30 2007 Nahlwe
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

#include <stdio.h>
#include "drumseqview.hh"

DrumSeqView::DrumSeqView(DrumSeq &a_drumseq, Sampler &a_sampler,
                         unsigned int a_init_track)
  : m_drumseq(a_drumseq), m_sampler(a_sampler),
    m_track_id(a_init_track)
{
  unsigned int i;

  pack_start(m_seq_hbox);
  for (i = 0; i < 16; i++)
    {
      char label[32];
      sprintf(label, "%d", i);
      m_seq_hbox.pack_start(m_steps[i]);
      m_steps[i].set_label(label);
    }
}
