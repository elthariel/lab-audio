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
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//

#ifndef _SKIN_H_
#define _SKIN_H_
#include <gtkmm.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <libxml++/libxml++.h>

namespace Thc {

  class Image {
  public:
    typedef Cairo::RefPtr<Cairo::ImageSurface> Ref;
    //throw Cairo::logic_error on file not found
    static Ref create_image(const Glib::ustring &name);
  };

  class Images {
  public:
    typedef boost::shared_ptr<std::vector<Image::Ref> > Ref;
    //throw Cairo::logic_error on file not found
    static Ref create_images(const Glib::ustring &name, int number);
    static Ref create_images(const Glib::ustring &name);
  };
  
  class Xml {
  public:
    //typedef boost::shared_ptr<xmlpp::Node> Ref;
    typedef xmlpp::Node *Ptr;
    Glib::ustring static extract_attribute(const Glib::ustring &name, Ptr node);
  };
  
  class Color {
  public:
    typedef Color* Ptr;
    double r;
    double g;
    double b;
    double a;
  };
  
  class Skin {
  public:
    typedef boost::shared_ptr<Skin> Ref;
    typedef std::map<Glib::ustring, Images::Ref> ImagesList;

    static Ref create_skin(Xml::Ptr node = NULL, const Glib::ustring &path = "");

    //xml
    inline Xml::Ptr get_xml() { return m_xml; };

    //image
    inline Image::Ref get_image(const Glib::ustring &name, int number = 0) {
      if (m_images[name])
        return (*(m_images[name]))[number];
      else
        return Image::Ref();
    }
    inline Images::Ref get_images(const Glib::ustring &name) { return m_images[name]; }
    inline int get_images_count(const Glib::ustring &name) { return m_images[name]->size(); }
    
    //color
    Color::Ptr get_color(const Glib::ustring &name);
    
    //attribute
    Glib::ustring get_attribute(const Glib::ustring &name);
    bool get_bool_attribute(const Glib::ustring &name);
  protected:
    //to create a skin use create_skin();
    //inline void set_xml(Xml::Ptr xml) { m_xml = xml; };
    inline void set_images(const Glib::ustring &name, Images::Ref images) { m_images[name] = images; }
    Skin(Xml::Ptr node = NULL, const Glib::ustring &path = "");
    void load_images_from_xml();
    
    Xml::Ptr m_xml;
    ImagesList m_images;
    Glib::ustring m_path;
  };  
}

#endif

