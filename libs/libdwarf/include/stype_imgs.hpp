//
// stype_imgs.hpp for libdwarf in /home/elthariel/code/projs/lab-audio/libs/libdwarf
//
// Made by Elthariel
// Login   <elthariel@free.fr>
//
// Started on  Thu Dec 14 00:04:57 2006 Elthariel
// Last update Thu Dec 14 00:45:49 2006 Elthariel
//

#include "skin.hpp"
#include <vector>

class STypeImgs : public SType
{
	int						m_state_count;

public:
	STypeImgs(string a_name, int a_state_count);

	Glib::RefPtr<Pixbuf>	make_pixmap(string a_img_base_path,
                                    unsigned int a_state);
};


template <int p_state_count>
class SEImgs : public SElement<STypeImgs>
{
  SEToggle();

  vector<int, Glib::RefPtr<Pixbuf>> m_imgs;
  string                m_base_path;

  void                  build_imgs();

public:
  SEToggle(string a_element_name, string a_base_path);

	virtual Glib::RefPtr<Pixbuf> render(float *a_states,
                                      unsigned int a_state_count);
};

typedef SEImgs<2>       SEImgsToggle;
typedef SEImgs<4>       SEImgsToggleAnim;
typedef SEImgs<127>     SEImgsSlider;


void                    append_int_to_string(string &str, unsigned int i);
