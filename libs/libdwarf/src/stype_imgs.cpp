
#include "stype_imgs.hpp"

STypeImgs::Stypeimgs(string a_name, int a_state_count)
  : SType(a_name), m_state_count(a_state_count)
{
}

Glib::RefPtr<Pixbuf>    StypeImgs::make_pixmap(string a_img_base_path,
                                               unsigned int a_state)
{
  Glib::RefPtr<Pixbuf>  pix;

  if (a_state < m_state_count)
    {
      append_int_to_string(a_img_base_path, a_state);
      a_img_base_path += ".png";
      pix = Pixbuf::create_from_file(a_img_base_path);
    }
  return (pix);
}

void            append_int_to_string(string &str, unsigned int i)
{
  string        tmp;

  while (i > 0)
    {
      tmp.insert(0, i % 10 + '0');
      i /= 10;
    }
  str += "_" += tmp;
}


template <int p_state_count>
void            SEImgs<p_state_count>::build_imgs()
{
  for (int i = 0; i < p_state_count; i++)
    {
      m_imgs[i] = m_stype.make_pixmap(m_base_path, i);
    }
}

template <int p_state_count>
SEImgs<p_state_count>::SEImgs(string a_element_name,
                              string a_base_path)
  : SElement<STypeImgs>("imgs"),
    m_stype("imgs", p_state_count),
    m_imgs(p_state_count, Glib::RefPtr<Pixbuf> pix),
    m_base_path(a_base_path)
{
  build_imgs();
}

