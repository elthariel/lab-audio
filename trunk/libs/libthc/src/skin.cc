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

//#include <iostream>
//#include <string>
//#include <cairomm/cairomm.h>

#include "skin.h"


namespace Thc {

  //TODO: use ustring not snprintf
  Skin::RefImages Skin::create_images(const Glib::ustring &name, int number) {
    int i = 0;
    char imgname[2000];
    RefImages images(new std::vector<RefImage>());
     
    if (i == -1) {
      RefImage pixbuf(Gdk::Pixbuf::create_from_file(name));
      images->push_back(pixbuf);
    } else for (i = 0; i <= number; i++) {
  	  snprintf(imgname, 2000, name.c_str(), i);
      RefImage pixbuf(Gdk::Pixbuf::create_from_file(imgname));
      images->push_back(pixbuf);
    }
    return images;
  }
    
  Skin::RefSkin Skin::create_skin(RefXml node, ImagesCollection images) {
    return RefSkin(new Skin(node, images)); 
  }
  
}

