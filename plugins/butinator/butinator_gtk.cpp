#include <iostream>

#include <gtkmm.h>

#include "lv2gtk2gui.hpp"
#include "butinator.peg"


using namespace std;
using namespace Gtk;
using namespace sigc;

class ModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
  ModelColumns() {
    add(m_col_name);
    add(m_col_size);
    add(m_col_bpm);
  }
  Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  Gtk::TreeModelColumn<long> m_col_size;
  Gtk::TreeModelColumn<int> m_col_bpm;
};

class MyPluginGUI : public LV2GTK2GUI {
public:

  MyPluginGUI(LV2Controller& ctrl, const std::string& URI,
              const std::string& bundle_path, Widget*& widget) {
    widget = &m_notebook;
    m_notebook.append_page(m_filechooser, "file chooser");

    m_targetlist.push_back(Gtk::TargetEntry("text/uri-list"));
    add_playlist("hardcore");
    add_playlist("speedcore");
    add_playlist("splitter-core");
  }

  void add_playlist(const Glib::ustring &name) {
		TreeView* treeview;
		Glib::RefPtr<Gtk::ListStore> ref_treemodel;

		treeview = new TreeView();

    ref_treemodel = Gtk::ListStore::create(m_columns);
    treeview->set_model(ref_treemodel);

    treeview->drag_dest_set(m_targetlist);
		treeview->drag_dest_add_uri_targets();
		treeview->signal_drag_data_received().connect(sigc::bind(sigc::mem_fun(*this, &MyPluginGUI::on_drop_drag_data_received), ref_treemodel));

		treeview->append_column("Name", m_columns.m_col_name);
		treeview->append_column("Size", m_columns.m_col_size); //This number will be shown with the default numeric formatting.
		treeview->append_column("Bpm", m_columns.m_col_bpm);
		for(guint i = 0; i < 3; i++) {
			Gtk::TreeView::Column* pColumn = treeview->get_column(i);
			pColumn->set_reorderable();
		}
    m_playlists.push_back(make_pair(treeview, ref_treemodel));
    m_notebook.append_page(*treeview, name);
  }

  void on_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
  															  int,
  															  int,
  															  const Gtk::SelectionData& selection_data,
  															  guint,
  															  guint time,
  															  Glib::RefPtr<Gtk::ListStore> ref_treemodel) {
    if (selection_data.get_data()) {
      std::vector<Glib::ustring> targets = selection_data.get_uris();
      if (! targets.empty()) {
      	for (std::vector<Glib::ustring>::iterator it(targets.begin()); it != targets.end(); ++it) {
				  try {
//				  	std::cout << "item: " << *it << std::endl;
				  	Gtk::TreeModel::Row row = *(ref_treemodel->append());
						row[m_columns.m_col_name] = *it;
						row[m_columns.m_col_size] = 300;
						row[m_columns.m_col_bpm] = 300;
						} catch (const std::exception& ex) {
						g_warning("Error while getting file info for path %s: %s", it->c_str(), ex.what());
					}
				}
			}
		}
  }

protected:
  ModelColumns m_columns;
  std::list<Gtk::TargetEntry> m_targetlist;
  Notebook m_notebook;
  FileChooserWidget m_filechooser;
  std::vector<std::pair<TreeView*,Glib::RefPtr<Gtk::ListStore> > > m_playlists;
};


void initialise() __attribute__((constructor));
void initialise() {
  register_lv2gtk2gui<MyPluginGUI>(peg_uri);
}
