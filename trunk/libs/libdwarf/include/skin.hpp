#include <map>
//#include <vector>
#include <string>
#include <gdkmm.h>

using namespace Gdk;

class SElement
{
	SElement();
public:
	SElement(Stype *, map<string, string>);

	virtual Glib::RefPtr<Pixmap> render(float *a_states,
										unsigned int a_state_count) = 0;
};
// <-- SERotary

// <-- STypeImgs, STypeVector, STypeBase, STypeComputed
class SType
{
	SType();
	string						m_stype_name;

public:
	SType(string a_name);

};


typedef cmap<char *, SElement *> _SEMap;

/** Represent the skin for a plugin. It allows you to register STypeX objects 
 *  at runtime. It provides access to skin elements to the ui.
 */
class SInstance
{
	/** Skin elements map.
	*/
	_SEMap			m_emap;
	 
public:
	SElement		*get_element(char *);
	void			register_element(SElement *);

};

/* Will be implemented in middle-term; Unique instance which provides access 
 * to all the skins in the process.
 */
class SManager
{
	static SManager		*m_instance;
	SManager();
public:
	static SManager		*get_instance();
};
