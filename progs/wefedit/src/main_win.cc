/*
** main_win.cc
** Login : <lta@elthariel-main>
** Started on  Fri May 25 17:11:32 2007 Elthariel
** $Id$
**
** Copyright (C) 2007 Elthariel
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <iostream>
#include <string>
#include <wef.hh>
#include "main_win.hh"
#include "wef_win.hh"

using namespace std;
using namespace Gtk;
using namespace sigc;

MainWin::MainWin()
{
  set_title("Wef editor");

  add(m_vbox);

  create_actions();

  show_all();
}

void                    MainWin::unimplemented()
{
  cerr << "Unimplemented feature" << endl;
}

void                    MainWin::quit()
{
  Main::quit();
}

void                    MainWin::open()
{
  Gtk::FileChooserDialog dialog("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button("Select", Gtk::RESPONSE_OK);


  Gtk::FileFilter filter_wef;
  filter_wef.set_name("Wef files");
  filter_wef.add_pattern("*.wef");
  dialog.add_filter(filter_wef);

  Gtk::FileFilter filter_any;
  filter_any.set_name("Any files");
  filter_any.add_pattern("*");
  dialog.add_filter(filter_any);

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      string path = dialog.get_filename();

      Wef       *wef = new Wef(path);
      WefWin    *wefwin = new WefWin(*wef);
      wefwin->show();
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

void                    MainWin::create_actions()
{
  Glib::ustring         ui;

  m_action_group = ActionGroup::create();

  /*
   * Create menus & submenus.
   */
  m_action_group->add(Action::create("FileMenu", "File"));

  /*
   * Create actual actions.
   */
  m_action_group->add(Action::create("FileNew",
                                     Stock::NEW, "_New",
                                     "Create a new wef file"),
                      mem_fun(*this, &MainWin::unimplemented));
  m_action_group->add(Action::create("FileOpen",
                                     Stock::OPEN, "_Open",
                                     "Open a wef file"),
                      mem_fun(*this, &MainWin::open));
  m_action_group->add(Action::create("FileQuit",
                                     Stock::QUIT, "_Quit",
                                     "Close this application"),
                      mem_fun(*this, &MainWin::quit));

  m_ui_manager = Gtk::UIManager::create();
  m_ui_manager->insert_action_group(m_action_group);

  add_accel_group(m_ui_manager->get_accel_group());

  ui =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='FileMenu'>"
    "      <menuitem action='FileNew'/>"
    "      <menuitem action='FileOpen'/>"
    "      <menuitem action='FileQuit'/>"
    "    </menu>"
    "  </menubar>"
    "</ui>";

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
    {
      m_ui_manager->add_ui_from_string(ui);
    }
  catch(const Glib::Error& ex)
    {
      std::cerr << "building menus failed: " <<  ex.what();
    }
#else
  std::auto_ptr<Glib::Error> ex;
  m_ui_manager->add_ui_from_string(ui, ex);
  if(ex.get())
    {
      std::cerr << "building menus failed: " <<  ex->what();
    }
#endif //GLIBMM_EXCEPTIONS_ENABLED

  Widget* pMenubar = m_ui_manager->get_widget("/MenuBar");
  if(pMenubar)
    m_vbox.pack_start(*pMenubar, Gtk::PACK_SHRINK);
}
