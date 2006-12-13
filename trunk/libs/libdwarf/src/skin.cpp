
#include "skin.hpp"

SElement::SElement(SType &a_type)
  : m_stype(&a_type)
{
}

SType::SType()
{
}

SType::SType(string a_name)
  :m_stype_name(a_name)
{
}

const string            &SType::get_name()
{
  return m_stype_name;
}

bool                    Stype::operator==(SType &that)
{
  return this->m_stype_name == that.m_stype_name;
}

bool                    Stype::operator==(string &that)
{
  return this->m_stype_name == that;
}
