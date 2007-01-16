/****************************************************************************

    lv2-OSCtype.h - header file for using OSC in LV2 plugins

    Copyright (C) 2006  Lars Luthman <lars.luthman@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 01222-1307  USA

****************************************************************************/

#ifndef LV2_OSCTYPE_H
#define LV2_OSCTYPE_H


typedef struct {
  char *type;
  char *message;
} OSC_MESSAGE;


typedef struct {

  uint32_t  event_count;

  uint32_t  capacity;

  uint32_t  size;

  unsigned char* data;

} LV2_OSC;



#endif
