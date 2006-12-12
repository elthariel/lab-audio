#include <map>

class iSType
 {

 };
// <-- STypeImgs, STypeVector, STypeBase, STypeComputed

class SElement
{
	iStype		*m_current_type;
public:

};

template <class StateType>
class SType : public iSType 
{
};
// STypeSlider, STypeRotary, StypeVuMeter, StypeButton, STypeBackground

typedef cmap<char *, Stype *> _STypeMap;

/** Represent the skin for a plugin. It allows you to register STypeX objects 
 *  at runtime. It provides access to skin elements to the ui.
 */
class SInstance
{
	_STypeMap			m_stmap;
	 
public:
};

/* Will be implemented in middle-term; Unique instance which provides access 
 * to all the skins in the process.
 */
class SManager
{
};
