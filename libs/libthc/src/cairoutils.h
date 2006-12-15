/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


//
// Class: CairoUtils
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _CAIRO_UTILS_H_
#define _CAIRO_UTILS_H_

#include <cairomm/cairomm.h>

namespace Thc {

  class CairoUtils {
  public:
    static int draw_digit(Cairo::RefPtr<Cairo::Context>& cc, char digit);
    static void draw_string(Cairo::RefPtr<Cairo::Context>& cc, const std::string& str, float x, float y);
  };

}//namespace Thc

#endif
