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
// Class: OscManager
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#include "oscmanager.h"
#include "widgetmanager.h"

OscManager::OscManager(const Glib::ustring &port)
  : m_port(port) {
  m_server = lo_server_new(m_port.c_str(), error_cb);
  if (_server == NULL) {
		cerr << "[OSC] Could not start OSC server.  Aborting." << endl;
		exit(EXIT_FAILURE);
	} else {
		char* lo_url = lo_server_get_url(_server);
		cout << "[OSC] Started OSC server at " << lo_url << endl;
		free(lo_url);
	}

	// For debugging, print all incoming OSC messages
	lo_server_add_method(_server, NULL, NULL, generic_cb, NULL);

	// Set response address for this message.
	// It's important this is first and returns nonzero.
	lo_server_add_method(_server, NULL, NULL, set_response_address_cb, this);
}


/** Create a new responder for this message, if necessary.
 *
 * This is based on the fact that the current responder is stored in a ref
 * counted pointer, and events just take a reference to that.  Thus, events
 * may delete their responder if we've since switched to a new one, or the
 * same one can stay around and serve a series of events.  Reference counting
 * is pretty sweet, eh?
 *
 * If this message came from the same source as the last message, no allocation
 * of responders or lo_addresses or any of it needs to be done.  Unfortunately
 * the only way to check is by comparing URLs, because liblo addresses suck.
 *
 * Really, this entire thing is a basically just a crafty way of partially
 * working around the fact that liblo addresses really suck.  Oh well.
 */
int
OscManager::set_response_address_cb(const char* path, const char* types, lo_arg** argv, int argc, lo_message msg, void* user_data)
{
	OSCEngineReceiver* const me = reinterpret_cast<OSCEngineReceiver*>(user_data);

	//cerr << "SET RESPONSE\n";

	if (argc < 1 || types[0] != 'i') // Not a valid Ingen message
//		return 0; // Save liblo the trouble
		return 1;

	//cerr << "** valid msg\n";

	const int id = argv[0]->i;

	const lo_address addr = lo_message_get_source(msg);
	char* const      url  = lo_address_get_url(addr);

	// Need to respond
	if (id != -1) {
		//cerr << "** need to respond\n";

		// Currently have an OSC responder, check if it's still okay
		if (me->_responder == me->_osc_responder) {
			//cerr << "** osc responder\n";

			if (!strcmp(url, me->_osc_responder->url())) {
				// Nice one, same address, do nothing (just set the ID below)
				//cerr << "** Using cached response address, hooray" << endl;
			} else {
				// Shitty deal, make a new one
				//cerr << "** Setting response address to " << url << "(2)" << endl;
				me->_osc_responder = SharedPtr<OSCResponder>(
					new OSCResponder(me->_engine->broadcaster(), id, url));

				me->set_responder(me->_osc_responder);

				// (responder takes ownership of url, no leak)
			}

		// Otherwise we have a NULL responder, definitely need to set a new one
		} else {
			//cerr << "** null responder\n";
			me->_osc_responder = SharedPtr<OSCResponder>(new OSCResponder(me->_engine->broadcaster(), id, url));
			me->set_responder(me->_osc_responder);
			//cerr << "** Setting response address to " << url << "(2)" << endl;
		}

		me->set_next_response_id(id);

	// Don't respond
	} else {
		me->disable_responses();
		SharedPtr<ClientInterface> client = me->_engine->broadcaster()->client(
			ClientKey(ClientKey::OSC_URL, (const char*)url));
		if (client)
			client->disable();
		else
			cerr << "UNKNOWN CLIENT!\n";

		//cerr << "** Not responding." << endl;
	}

	// If this returns 0 no OSC commands will work
	return 1;
}


void
OscManager::error_cb(int num, const char* msg, const char* path)
{
	cerr << "liblo server error " << num << " in path \"" << "\" - " << msg << endl;
}
