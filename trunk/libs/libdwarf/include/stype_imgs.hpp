#include "skin.hpp"

class STypeImgs : public SType
{
	int						m_state_count;
public:
	STypeImgs(string a_name, int a_state_count);

	Glib::RefPtr<Pixmap>	make_pixmap(string a_img_base_path, unsigned int a_state);
};