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
// Class: SkinManager
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _SKINMANAGER_H_
#define _SKINMANAGER_H_

#include <map>
#include <vector>
#include <gtkmm.h>
#include "ithcwidget.h"
#include "skin.h"

namespace Thc {

  class SkinManager {
  public:
    inline static void instanciate() { if (!m_skin_manager) m_skin_manager = new SkinManager(); }
    inline static SkinManager *instance() { instanciate(); return m_skin_manager; }
    
    static Skin::Ref get_skin(const Glib::ustring& name) { return instance()->do_get_skin(name); }
    
    void load_all_skins();
    bool load_skin(const Glib::ustring &name);
    void add_path(const Glib::ustring &name);
    void remove_path(const Glib::ustring &name);
    void load_path(const Glib::ustring &name);
   
  protected:
    SkinManager() { };
    inline Skin::Ref do_get_skin(const Glib::ustring& name) { return m_skins[name]; }
    void parse_node(const Xml::Ptr node, const Glib::ustring &path);
    void parse_sub_node(const Xml::Ptr node, const Glib::ustring &path);

  private:
    typedef std::vector<Glib::ustring> PathList;
    typedef std::map<Glib::ustring, Skin::Ref> SkinMap;
    typedef std::vector<boost::shared_ptr<xmlpp::DomParser> > ParserList;
    PathList m_paths;
    SkinMap m_skins;
    ParserList m_parser;
    static SkinManager *m_skin_manager;
  };
  
} //namespace Thc

#endif //_SKINMANAGER_H_

