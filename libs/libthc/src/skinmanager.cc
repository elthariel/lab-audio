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
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#include <libxml++/libxml++.h>
#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include "skinmanager.h"
#include "skin.h"
#include "../config.h"

namespace Thc {

  //singleton
  SkinManager* SkinManager::m_skin_manager = 0;

  void SkinManager::instanciate() {
  	if (!m_skin_manager) {
  		Glib::ustring stdpath = THCDATA_DIR;
  		stdpath += "/skins";
  		m_skin_manager = new SkinManager();
  		m_skin_manager->add_path(stdpath);
  		std::cout << "path: " << stdpath << std::endl;
  	}
  }

  void SkinManager::parse_sub_node(const Xml::Ptr node, const Glib::ustring &path) {
    Glib::ustring name;
    const xmlpp::Element* nodeelt = dynamic_cast<const xmlpp::Element*>(node);
    if (!nodeelt)
      return;
    const xmlpp::Element::AttributeList& attributes = nodeelt->get_attributes();

    for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter){
      const xmlpp::Attribute* attribute = *iter;
      if (attribute->get_name() == "name") {
        name = node->get_name() + "/" + attribute->get_value();
        std::cout << "  Attribute " << name << std::endl;
        m_skins[name] = Skin::create_skin(node, Glib::path_get_dirname(path));
      }
    }
  }

  void SkinManager::parse_node(const Xml::Ptr node, const Glib::ustring &path)
  {
    xmlpp::Node::NodeList list = node->get_children();

    if (node->get_name() != "thc")
      throw new std::logic_error("The xml file doesn't contain a thc root node");

    for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter){
      xmlpp::Node* childnode = *iter;
      const xmlpp::TextNode* childnodetext = dynamic_cast<const xmlpp::TextNode*>(childnode);
      const xmlpp::Element* childnodeelt = dynamic_cast<const xmlpp::Element*>(childnode);
      if (!childnodetext || !childnodetext->is_white_space() && childnodeelt) {
        parse_sub_node(*iter, path);
      }
    }
  }

  bool SkinManager::load_skin(const Glib::ustring &name) {
    try {
      boost::shared_ptr<xmlpp::DomParser> parser(new xmlpp::DomParser());
      //parser.set_validate();
      parser->set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
      parser->parse_file(name);
      if(!(*parser))
        return false;
      m_parser.push_back(parser);
      parse_node(parser->get_document()->get_root_node(), name);
      return true;
    } catch(const std::exception& ex) {
      std::cerr << "error loading file:" << name << std::endl;
      return false;
    }
    return false;
  }

  void SkinManager::load_path(const Glib::ustring &name) {
    using namespace boost::filesystem;
    const path dir_path(system_complete(path(name, native)));
    directory_iterator itend;
    directory_iterator it(dir_path);

    if (!exists(dir_path))
      return;
    for (it; it != itend; ++it) {
      if (!is_directory(*it) && extension(*it) == ".xml") {
        load_skin(it->native_file_string());
      }
    }
  }

  void SkinManager::load_all_skins() {
    PathList::iterator it;
    for (it = m_paths.begin(); it != m_paths.end(); ++it) {
      load_path(*it);
    }
  }

  void SkinManager::add_path(const Glib::ustring &name) {
    m_paths.push_back(name);
  }

  void SkinManager::remove_path(const Glib::ustring &name) {
    std::vector<Glib::ustring>::iterator it = std::find(m_paths.begin(), m_paths.end(), name);
    if (it != m_paths.end())
      m_paths.erase(it);
  }

}

