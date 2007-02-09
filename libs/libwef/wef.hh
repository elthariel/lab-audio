/*
** wef.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Feb  9 15:40:34 2007 Nahlwe
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

#ifndef   	WEF_HH_
# define   	WEF_HH_

# include "wef_mem_0_2.h"
# include <string>

class Wef
{
public:
  Wef(std::string path);
  ~Wef();

  unsigned int  get_size() const;
  unsigned int  get_grain_count() const;
  unsigned int  get_grain_size(unsigned int grain) const;
  const char    *get_name() const;
  const char    *get_author() const;
  unsigned char version() const;

  // Accessors without grains.
  const double  &operator[](unsigned int index) const;

  // Accessors supporting grains.
  const double  &operator()(unsigned int index,
                            unsigned int grain) const;
protected:
  wfm           *m_wef_mem;
  std::string   m_path;
};

#endif	    /* !WEF_HH_ */
