#ifndef _PLAYLIST_MODEL_H_
#define _PLAYLIST_MODEL_H_

#include <gtkmm.h>

class PlaylistModel : public Gtk::TreeStore {
protected:
  PlaylistModel();

public:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelColumns() {
    	add(m_col_id); add(m_col_name); add(m_col_draggable); add(m_col_receivesdrags);
    }

    Gtk::TreeModelColumn<int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<bool> m_col_draggable;
    Gtk::TreeModelColumn<bool> m_col_receivesdrags;
  };
  ModelColumns m_columns;
  static Glib::RefPtr<PlaylistModel> create();

protected:
  virtual bool row_draggable_vfunc(const Gtk::TreeModel::Path& path) const;
  virtual bool row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data) const;
};

#endif
