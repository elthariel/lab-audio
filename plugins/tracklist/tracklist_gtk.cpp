#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "playlist_model.h"
#include "tracklist.peg"


using namespace std;
using namespace Gtk;
using namespace sigc;


class MyPluginGUI : public LV2GTK2GUI {
public:

  MyPluginGUI(LV2Controller& ctrl, const std::string& URI,
              const std::string& bundle_path, Widget*& widget)
    : m_scale(peg_ports[peg_gain].min, peg_ports[peg_gain].max, 0.01),
      m_label("plok") {
    //widget = &m_scale;
    widget = &m_notebook;
    m_notebook.append_page(m_filechooser, "file chooser");
    m_notebook.append_page(m_listview1, "playlist 1");
    m_notebook.append_page(m_listview2, "playlist 2");
    m_notebook.append_page(m_label, "label");
    /*m_scale.signal_value_changed().
      connect(compose(bind<0>(mem_fun(ctrl, &LV2Controller::set_control), peg_gain),
                      mem_fun(m_scale, &HScale::get_value)));
    m_scale.set_size_request(200, 50);*/
    std::list<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("TEXT"));
    listTargets.push_back(Gtk::TargetEntry("STRING"));
    listTargets.push_back(Gtk::TargetEntry("text/plain"));
    listTargets.push_back(Gtk::TargetEntry("text/uri-list"));
    m_listview1.drag_dest_set(listTargets);
		m_listview1.drag_dest_add_uri_targets();

		m_label.drag_dest_set(listTargets);
		m_label.drag_dest_add_uri_targets();

    m_label.signal_drag_data_received().connect( sigc::mem_fun(*this, &MyPluginGUI::on_label_drop_drag_data_received) );
		m_listview1.signal_drag_data_received().connect( sigc::mem_fun(*this, &MyPluginGUI::on_label_drop_drag_data_received) );

		m_refTreeModel = PlaylistModel::create();
		m_listview1.set_model(m_refTreeModel);
		m_listview1.enable_model_drag_source();
		m_listview1.enable_model_drag_dest();
		//Fill the TreeView's model
		Gtk::TreeModel::Row row = *(m_refTreeModel->append());
		row[m_refTreeModel->m_columns.m_col_id] = 1;
		row[m_refTreeModel->m_columns.m_col_name] = "Billy Bob";
		row[m_refTreeModel->m_columns.m_col_draggable] = true;
		row[m_refTreeModel->m_columns.m_col_receivesdrags] = true;

		row = *(m_refTreeModel->append());
		row[m_refTreeModel->m_columns.m_col_id] = 2;
		row[m_refTreeModel->m_columns.m_col_name] = "Joey Jojo";
		row[m_refTreeModel->m_columns.m_col_draggable] = true;
		row[m_refTreeModel->m_columns.m_col_receivesdrags] = true;

		row = *(m_refTreeModel->append());
		row[m_refTreeModel->m_columns.m_col_id] = 3;
		row[m_refTreeModel->m_columns.m_col_name] = "Rob McRoberts";
		row[m_refTreeModel->m_columns.m_col_draggable] = true;
		row[m_refTreeModel->m_columns.m_col_receivesdrags] = true;

		//Add the TreeView's view columns:
		m_listview1.append_column("ID", m_refTreeModel->m_columns.m_col_id); //This number will be shown with the default numeric formatting.
		m_listview1.append_column("Name", m_refTreeModel->m_columns.m_col_name);
		m_listview1.append_column("ID", m_refTreeModel->m_columns.m_col_draggable); //This number will be shown with the default numeric formatting.
		m_listview1.append_column("Name", m_refTreeModel->m_columns.m_col_receivesdrags);

		for(guint i = 0; i < 2; i++) {
			Gtk::TreeView::Column* pColumn = m_listview1.get_column(i);
			pColumn->set_reorderable();
		}
  }

  void on_button_drag_data_get(const Glib::RefPtr<Gdk::DragContext>&, Gtk::SelectionData& selection_data, guint, guint){
    std::cout << "drag" << std::endl;
    selection_data.set(selection_data.get_target(), 8 /* 8 bits format */, (const guchar*)"I'm Data!", 9 /* the length of I'm Data! in bytes */);
  }

  void on_label_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int, int, const Gtk::SelectionData& selection_data, guint, guint time) {
    std::cout << "drop" << std::endl;
    /*if ((selection_data.get_length() >= 0) && (selection_data.get_format() == 8)) {
      std::cout << "Received \"" << selection_data.get_data_as_string() << "\" in label " << std::endl;
    }*/
    //context->drag_finish(false, false, time);
  }

  void set_control(uint32_t port, float value) {
    if (port == peg_gain)
      m_scale.set_value(value);
  }

protected:
  Glib::RefPtr<PlaylistModel> m_refTreeModel;

  HScale m_scale;
  Notebook m_notebook;
  FileChooserWidget m_filechooser;
  TreeView m_listview1;
  TreeView m_listview2;
  Label m_label;
};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
