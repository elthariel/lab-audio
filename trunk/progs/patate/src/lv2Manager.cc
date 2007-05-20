/*
** lv2Manager.cc
** Login : <elthariel@elthariel-desktop>
** Started on  Sun May 20 19:50:25 2007 Nahlwe
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

#include <iostream>
#include "lv2Manager.hh"

using namespace std;

const LV2_Host_Feature **g_features = NULL;

bool                    lv2_is_synth(SLV2Plugin a_plug)
{
  /*  SLV2Values            values;
  SLV2Value             val;
  unsigned int          i;

  values = slv2_plugin_get_supported_features(a_plug);
  for (i = 0; i < slv2_values_size(values); i++)
    {
      cout << "a supported features" << endl;
      val = slv2_values_get_at(values, i);
      if (slv2_value_is_string(val))
        cout << slv2_value_as_string(val) << endl;
        }*/
  return (true);
}

Lv2Manager::Lv2Manager(Patate &a_patate)
  : m_patate(a_patate)
{
  init_slv2();
}

void                    Lv2Manager::init_slv2()
{
  m_world = slv2_world_new();
  slv2_world_load_all(m_world);
  m_plugins = slv2_world_get_plugins_by_filter(m_world, &lv2_is_synth);

  for (unsigned i = 0; i < slv2_plugins_size(m_plugins); ++i)
    {
      SLV2Plugin p = slv2_plugins_get_at(m_plugins, i);
      cout << "Plugin found : " << slv2_plugin_get_uri(p) << endl;
    }
}













/*
 * Lv2Adapter class.
 */

Lv2Adapter::Lv2Adapter(SLV2Plugin &a_plugin, unsigned int a_sample_rate)
  : m_plugin(a_plugin),
    m_midi_connected(false)
{
  slv2_plugin_instantiate(m_plugin, a_sample_rate, g_features);
  slv2_instance_activate(m_lv2);
  create_ports();
  connect_ports();
}

Lv2Adapter::~Lv2Adapter()
{
  slv2_instance_deactivate(m_lv2);
  slv2_instance_free(m_lv2);
}

void        Lv2Adapter::play_note(const Seq::Note &a_note)
{
}

void        Lv2Adapter::stop_note(const Seq::Note &a_note)
{
}

void        Lv2Adapter::cc(unsigned int control, float value)
{
  if (control < m_port_count)
    {
      m_controls[control] = value;
    }
}

void        Lv2Adapter::flush_note()
{
}

void        Lv2Adapter::render(jack_nframes_t nframes,
                   jack_nframes_t sample_rate,
                   unsigned int chan_count,
                   jack_default_audio_sample_t **out)
{
}

void        Lv2Adapter::create_ports()
{
  m_port_count = slv2_plugin_get_num_ports(m_plugin);

  m_controls = new float[m_port_count];
  m_midi_port.data = new unsigned char[LV2_MIDI_BUFFER_SIZE];
  m_midi_port.event_count = 0;
  m_midi_port.capacity = LV2_MIDI_BUFFER_SIZE;
  m_midi_port.size = 0;
  m_audio_ports_index[0] = -1;
  m_audio_ports_index[1] = -1;
}

void        Lv2Adapter::connect_ports()
{
  unsigned int i;

  for (i = 0; i < m_port_count; i++)
    {
	SLV2Port port = slv2_plugin_get_port_by_index(m_plugin, i);
	SLV2PortClass port_class = slv2_port_get_class(m_plugin, port);
      switch (port_class)
        {
        case SLV2_CONTROL_INPUT:
          m_controls[i] = slv2_port_get_default_value(m_plugin, port);
          slv2_instance_connect_port(m_lv2, i, &m_controls[i]);
          break;
        case SLV2_AUDIO_OUTPUT:
          if (m_audio_ports_index[0] < 0)
            m_audio_ports_index[0] = i;
          else if (m_audio_ports_index[1] < 0)
            m_audio_ports_index[1] = i;
          else
            cout << "This plugin has too much audio ouput" << endl;
          break;
        case SLV2_MIDI_INPUT:
          if (!m_midi_connected)
            {
              m_midi_connected = false;
              slv2_instance_connect_port(m_lv2, i, &m_midi_port);
            }
          break;
        default:
          cout << "This plugins contains port type that are not handled by this program\n"
               << "your plugin may not work correctly" << endl;
          break;
        }
    }
}


