/*
** sekrym.hh
** Login : <elthariel@localhost.localdomain>
** Started on  Sun Dec  3 09:55:06 2006 Elthariel
** $Id$
**
** Copyright (C) 2006 Elthariel
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

#ifndef   	SEKRYM_HH_
# define   	SEKRYM_HH_

#include "lv2plugin.hpp"
#include "pattern.cc"

class Sekrym : public LV2Plugin
{
protected:

  Pattern               m_pat[32];

  // remaining samples since the last tick.
  unsigned int          m_remaining_samples.

public:

  Sekrym(unsigned long sample_rate,
         const char* bundle_path,
         const LV2_Host_Feature** features);
  virtual ~Sekrym();

  virtual void          run(uint32_t sample_count);
  virtual void          deactivate();

  /** This reset the playaing state of sekrym.
   */
  void                  reset();

  /** Resets the playing state & clear the pattern bank.
   */
  void                  clear();
};

#endif	    /* !SEKRYM_HH_ */
