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
# include "transport.hh"
# include "event.hh"
# include "part.hh"

namespace Seq
{
  /*!
  ** \brief Part container
  ** \see Part
  */
  class Seq
  {
  public:
    Seq(unsigned int a_part_count);
    ~Seq();

    void                run(Transport::Position &, Transport::Position &);
    Part                &part(unsigned int part_id);
  protected:
    std::vector<Part *> m_parts;
    unsigned int        m_part_count;
  };

};

#endif	    /* !SEQ_HH_ */
