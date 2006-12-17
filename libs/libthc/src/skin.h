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

  class Skin {
  public:
    typedef boost::shared_ptr<xmlpp::Node> RefXml;
    typedef Glib::RefPtr<Gdk::Pixbuf> RefImage;    
    typedef boost::shared_ptr<std::vector<RefImage> > RefImages;
    typedef std::map<Glib::ustring, RefImages> ImagesCollection;
    typedef boost::shared_ptr<Skin> RefSkin;

    static RefImages create_images(const Glib::ustring &name, int number = -1);    
    static RefSkin create_skin(RefXml node = RefXml(), ImagesCollection images = ImagesCollection());

    inline void set_images(const Glib::ustring &name, RefImages images) { m_images[name] = images; }
    inline RefImage get_images(const Glib::ustring &name, int number = 0) { return (*(m_images[name]))[number]; }
    inline int get_images_count(const Glib::ustring &name) { return m_images[name]->size(); }
    
    inline void set_xml(RefXml xml) { m_xml = xml; };
    inline RefXml get_xml() { return m_xml; };

  protected:
    //to create a skin use create_skin();
    inline Skin(RefXml node = RefXml(), ImagesCollection images = ImagesCollection()): m_xml(node), m_images(images) {}
    
    RefXml m_xml;
    ImagesCollection m_images;
  };  
}

#endif

