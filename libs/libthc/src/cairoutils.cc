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
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#include <cairomm/cairomm.h>
#include "cairoutils.h"

int CairoUtils::draw_digit(Cairo::RefPtr<Cairo::Context>& cc, char digit) {
  cc->save();
  cc->set_source_rgb(0.7, 0.9, 1.0);
  cc->set_line_width(1);
  
  int width = 0;
  
  switch (digit) {
  case '0':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, -6);
    width = 5;
    break;
    
  case '1':
    cc->rel_move_to(3, 0);
    cc->rel_line_to(0, 6);
    width = 5;
    break;
    
  case '2':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '3':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(-3, 0);
    cc->rel_move_to(0, -3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '4':
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    cc->rel_move_to(0, -3);
    cc->rel_line_to(0, 6);
    width = 5;
    break;
    
  case '5':
    cc->rel_move_to(3, 0);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(-3, 0);
    width = 5;
    break;
    
  case '6':
    cc->rel_move_to(3, 0);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, -3);
    cc->rel_line_to(-3, 0);
    width = 5;
    break;
    
  case '7':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    width = 5;
    break;
    
  case '8':
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, 6);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, -6);
    cc->rel_move_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '9':
    cc->rel_move_to(0, 6);
    cc->rel_line_to(3, 0);
    cc->rel_line_to(0, -6);
    cc->rel_line_to(-3, 0);
    cc->rel_line_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '.':
    cc->rel_move_to(0, 6);
    cc->rel_line_to(0, -1);
    width = 2;
    break;
    
  case '*':
    cc->rel_move_to(0, 1);
    cc->rel_line_to(3, 4);
    cc->rel_move_to(-3, 0);
    cc->rel_line_to(3, -4);
    cc->rel_move_to(-3, 2);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  case '-':
    cc->rel_move_to(0, 3);
    cc->rel_line_to(3, 0);
    width = 5;
    break;
    
  }
  
  cc->stroke();
  cc->restore();
  
  return width;
}


void CairoUtils::draw_string(Cairo::RefPtr<Cairo::Context>& cc, const std::string& str, float x, float y) {
  cc->move_to(x, y);
  int xoffset = 0;
  for (int i = 0; i < str.length(); ++i) {
    xoffset += draw_digit(cc, str[i]);
    cc->move_to(x + xoffset, y);
  }
}

void CairoUtils::draw_port(Cairo::RefPtr<Cairo::Context>& cc, float x, float y) {
  cc->move_to(x, y);
  cc->line_to(x, y + 5);
  cc->line_to(x + 5, y + 5);
  cc->line_to(x + 5, y);
  cc->line_to(x, y);
}

void CairoUtils::draw_ports(Cairo::RefPtr<Cairo::Context>& cc) {

}

