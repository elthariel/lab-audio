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
    typedef Glib::RefPtr<Gdk::Pixbuf> Ref;
    static Ref create_image(const Glib::ustring &name);
  };

  class Images {
  public:
    typedef boost::shared_ptr<std::vector<Image::Ref> > Ref;
    static Ref create_images(const Glib::ustring &name, int number = -1);
  };
  
  class Xml {
  public:
    typedef boost::shared_ptr<xmlpp::Node> Ref;    
  };
  
  class Skin {
  public:
    typedef boost::shared_ptr<Skin> Ref;
    static Ref create_skin(Xml::Ref node = Xml::Ref());

    inline void set_images(const Glib::ustring &name, Images::Ref images) { m_images[name] = images; }
    inline Image::Ref get_image(const Glib::ustring &name, int number = 0) { return (*(m_images[name]))[number]; }
    inline Images::Ref get_images(const Glib::ustring &name) { return m_images[name]; }
    inline int get_images_count(const Glib::ustring &name) { return m_images[name]->size(); }
    
    inline void set_xml(Xml::Ref xml) { m_xml = xml; };
    inline Xml::Ref get_xml() { return m_xml; };

  protected:
    //to create a skin use create_skin();
    inline Skin(Xml::Ref node = Xml::Ref()): m_xml(node) {}
    void load_images_from_xml();
    
    Xml::Ref m_xml;
    std::map<Glib::ustring, Images::Ref> m_images;
  };  
}

#endif

