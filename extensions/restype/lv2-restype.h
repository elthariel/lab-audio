/*
** lv2-restype.h
** Login : <elthariel@elthariel-desktop>
** Started on  Sat Aug 25 14:54:12 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Elthariel
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 01222-1307  USA
*/

#ifndef   	LV2_RESTYPE_H_
# define   	LV2_RESTYPE_H_

#include <sndfile.h>

/*! \file lv2-restype.h
 * \brief Lv2 ressource port type
 *
** This data structures is used to allows the host to share data
** between plugins, like samples. A ressource can have differents
** types. Identification can be made at runtime but can also be forced
** using rdf data predicate. A port contain a pointer to the ressource
** and the type of the data which is provided.
**
** Currently defined ressource type is Audio Sample.
** @see LV2_SNDFILE
*/

/// @see LV2_SAMPLE_INTER
#define                         LV2_RES_TYPE_SAMPLE     1

typedef struct                  _LV2_RESSOURCE
{
  uint32_t                      type;
  void                          *data;
}                               LV2_RESSOURCE;

/*! \brief This data structure is used to hold a mono audio sample
** that is shared between the host and its plugins.
**
** Channels are interleaved, and values are normalized between -1.0
** and 1.0
*/
typedef struct                  _LV2_SAMPLE
{
  uint64_t                      size;
  uint32_t                      sample_rate;
  uint32_t                      channels;
  float                         *data;
}                               LV2_SAMPLE_MONO;

#endif 	    /* !LV2_RESTYPE_H_ */

