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
// Class: ThcWidget
//
// Created by: GESTES Cedric <goctaf@gmail.com>
// Created on: Sun Dec  3 19:34:17 2006
//
#include "thcwidget.h"
#include "cairoutils.h"

namespace Thc {
  
  ThcWidget::ThcWidget(Skin::Ref skin)
    : m_skin(skin),
      m_mode(ModeNormal),
      m_supported_mode(ModeNormal & ModeConnect) {
  }
  
  ThcWidget::~ThcWidget() {
    if (ModeManager::instance())
      ModeManager::instance()->remove_widget(this);
  }
  
  void ThcWidget::draw_ports(const Gtk::Allocation &allocation, Cairo::RefPtr<Cairo::Context> cc) {
    int x = 2, y = 2;
    const int width = allocation.get_width();
    const int height = allocation.get_height();
  
    cc->rectangle(0, 0, width, height);  
    cc->stroke();  
    for (int i = 0; i < get_param_count(); i++) {
      CairoUtils::draw_port(cc, x, y);
      x += 15;
    }
  }

}

