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
// Class: Skin
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//
#include <iostream>
//#include <sstream>
#include "boost/format.hpp"
#include "skin.h"

namespace Thc {

  //Image
  Image::Ref Image::create_image(const Glib::ustring &name) {
    return Ref(Cairo::ImageSurface::create_from_png(name.c_str()));
  }

  //Images
  Images::Ref Images::create_images(const Glib::ustring &name, int number) {
    int i = 0;
    std::string imgname;
    //char imgname[2000];
    Images::Ref images(new std::vector<Image::Ref>());
        
    if (i == -1) {
      images->push_back(Image::create_image(name));
    } else for (i = 0; i <= number; i++) {
     imgname = str(boost::format(name) % i);
     //snprintf(imgname, 2000, name.c_str(), i);
     images->push_back(Image::create_image(imgname));
    }
    return images;
  }

  Images::Ref Images::create_images(const Glib::ustring &name) {
    Images::Ref images(new std::vector<Image::Ref>());
    images->push_back(Image::create_image(name));
    return images;
  }
  
  //Xml
  Glib::ustring Xml::extract_attribute(const Glib::ustring &name, Ptr node) {
    if (!node)
      return "";
    const xmlpp::Element* nodeelt = dynamic_cast<const xmlpp::Element*>(node);
    if (!nodeelt)
      return "";
    const xmlpp::Element::AttributeList& attributes = nodeelt->get_attributes();
    for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter){
      const xmlpp::Attribute* attribute = *iter;
      if (attribute->get_name() == name) {
        return attribute->get_value();
      }
    }
    return "";
  }
  
  Color::Ptr Color::create_color(Xml::Ptr node) {
    Glib::ustring r, g, b, a;
    return new Color();
  }

  //Skin
  Skin::Ref Skin::create_skin(Xml::Ptr node, const Glib::ustring &path) {
    return Ref(new Skin(node, path)); 
  }

  Skin::Skin(Xml::Ptr node, const Glib::ustring &path):m_xml(node), m_path(path) {
    load_images_from_xml();
  }
  
  Color::Ptr Skin::get_color(const Glib::ustring &name) {
    if (!m_xml)
      return 0;
    xmlpp::Node::NodeList list = m_xml->get_children("color");
    for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter){
      const xmlpp::Node* node = *iter;
      //if (node->get_name() == name)
      //  return Color::create_color(node);
    }
    return 0;
  }
    
  Glib::ustring Skin::get_attribute(const Glib::ustring &name) {
    return Xml::extract_attribute(name, m_xml);
  }
  
  bool Skin::get_bool_attribute(const Glib::ustring &name) {
    return (Xml::extract_attribute(name, m_xml) == "true");
  }

  void Skin::load_images_from_xml() {
    Glib::ustring name, path, count;
    xmlpp::Node::NodeList list;
    
    if (!m_xml)
      return;
    
    list = m_xml->get_children("images");
    for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter){
      name = Xml::extract_attribute("name", *iter);
      path = Xml::extract_attribute("path", *iter);
      count = Xml::extract_attribute("count", *iter);
      if (name != "" && path != "" && count != "") {
        try {
          m_images[name] = Images::create_images(Glib::build_filename(m_path, path), atoi(count.c_str()));
        } catch(const std::exception& ex) {
          std::cerr << "error loading images(count=" << count << "): " << path << std::endl;
        }
      }
    }
    
    list = m_xml->get_children("image");
    for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter){
      name = Xml::extract_attribute("name", *iter);
      path = Xml::extract_attribute("path", *iter);
      if (name != "" && path != "") {
        try {
          m_images[name] = Images::create_images(Glib::build_filename(m_path, path));
        } catch(const std::exception& ex) {
          std::cerr << "error loading image: " << path << std::endl;
        }
      }
    }
  }

}

