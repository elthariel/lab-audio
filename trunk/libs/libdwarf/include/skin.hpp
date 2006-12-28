#include <hash_map>
#include <string>
#include <gdkmm.h>

using namespace Gdk;
using namespace std;

template <class ST>
class SElement
{
	SElement();

  ST                    m_stype;
  string                m_name;

public:
  SElement(string a_name);

	virtual Glib::RefPtr<Pixbuf>  render(float *a_states,
                                      unsigned int a_state_count) = 0;
  virtual void                  get_name();
  // Need to add xml conf members.
};


// <-- STypeImgs, STypeVector, STypeBase, STypeComputed
class SType
{
	SType();
	string                m_stype_name;

public:
	SType(string a_name);

  const string          &get_name();
  bool                  operator==(SType &);
  bool                  operator==(string &);
};


typedef hash_map<string, SElement &> _SEMap;

/** Represent the skin for a plugin. It allows you to register STypeX objects
 *  at runtime. It provides access to skin elements to the ui.
 */
class Skin : public SType
{
	/** Skin elements map. */
	_SEMap        m_emap;

public:
	SElement      &get_element(string);
	void          register_element(SElement &);

};


typedef hash_map<string, Skin &> _SMap;

class SManager
{
	static SManager		*m_instance;
	SManager();

protected:
  _SMap         *m_smap;

public:
	static SManager		*get_instance();

	Skin          &get_element(string);
	void          register_element(string , Skin &);

  //Xml.
  Skin          *create_from_file(string path)y;
};
