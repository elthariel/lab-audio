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

#include "skinmanager.h"
#include "skin.h"

namespace Thc {
  SkinManager* SkinManager::m_skin_manager = 0;
  
  
  void SkinManager::parse_sub_node(const Xml::Ptr node) {
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
        m_skins[name] = Skin::create_skin(node);
      }
    }
  }

  void SkinManager::parse_node(const Xml::Ptr node)
  {
    xmlpp::Node::NodeList list = node->get_children();

    if (node->get_name() != "thc")
      throw new std::logic_error("The xml file doesn't contain a thc root node");

    for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter){
      xmlpp::Node* childnode = *iter;
      const xmlpp::TextNode* childnodetext = dynamic_cast<const xmlpp::TextNode*>(childnode);
      const xmlpp::Element* childnodeelt = dynamic_cast<const xmlpp::Element*>(childnode);
      if (!childnodetext || !childnodetext->is_white_space() && childnodeelt) {
        parse_sub_node(*iter);
      }
    } 
  }

  void SkinManager::load_all_skins() {
    PathList::iterator it;
    for (it = m_paths.begin(); it != m_paths.end(); ++it) {
    }
  }
  
  bool SkinManager::load_skin(const Glib::ustring &name) {
    try {
//      boost::shared_ptr<xmlpp::DomParser> parser(new xmlpp::DomParser());
      xmlpp::DomParser* parser = new xmlpp::DomParser();
      //parser.set_validate();
      parser->set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
      parser->parse_file(name);
      if(!parser)
        return false;
      const Xml::Ptr node = parser->get_document()->get_root_node(); //deleted by DomParser.
      parse_node(node);
      //store the parser otherwhise the parser auto kill the dom when he his killed
      //m_parser.push_back(parser);
      return true;
    } catch(const std::exception& ex) {
      std::cerr << "error loading file:" << name << std::endl;
      return false;
    }
    return false;
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

