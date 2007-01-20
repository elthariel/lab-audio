/*
** promethee.hh
** Login : <elthariel@elthariel-desktop>
** Started on  Fri Jan 19 16:49:52 2007 Nahlwe
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

#ifndef   	PROMETHEE_HH_
# define   	PROMETHEE_HH_

#include "lv2instrument.hpp"
#include "lv2plugin.hpp"
#include "lv2-miditype.h"
#include "promethee.peg"
#include "Sample.hh"

//FIXME macro defined twice, use config.h
#define                 SAMPLES_COUNT 8

class Promethee : public LV2Instrument
{
public:
  Promethee(uint32_t rate, const char*, const LV2_Host_Feature**);
  void          run(uint32_t sample_count);
  char*         configure(const char* key, const char* value);
  char*         set_file(const char* key, const char* filename);
  void          load_file(const std::string& path);

protected:
  uint32_t              m_sample_rate;

  Sample                *m_smp[SAMPLES_COUNT];

  void                  dispatch_control_ports(unsigned int sample_id);
  void                  dispatch_midi_ports(unsigned int sample_id,
                                            unsigned int sample_count);
  void                  process_audio(unsigned int sample_id,
                                      unsigned int sample_count);
};


#endif	    /* !PROMETHEE_HH_ */
