//
// wef.cpp for libwef-cpp in /home/elthariel/code/lab-audio/libs/libwef
//
// Made by Nahlwe
// Login   <elthariel@epita.fr>
//
// Started on  Fri Feb  9 15:52:18 2007 Nahlwe
// Last update Fri Feb  9 16:17:35 2007 Nahlwe
//

#include "wef.hh"

using namespace std;

Wef::Wef(std::string path)
  : m_path(path)
{
  m_wef_mem = wef_open(m_path.c_str());
}

Wef::~Wef()
{
  wef_close(m_wef_mem);
}

unsigned int    Wef::get_size() const
{
  return m_wef_mem->wf_size;
}

unsigned int    Wef::get_grain_count() const
{
  return m_wef_mem->wf_grain_count;
}

unsigned int    Wef::get_grain_size(unsigned int grain) const
{
  if (grain < m_wef_mem->wf_grain_count)
    return m_wef_mem->wf_grain_index[grain].grain_size;
}

const char      *Wef::get_name() const
{
  return m_wef_mem->wf_name;
}

const char      *Wef::get_author() const
{
  return m_wef_mem->wf_author;
}

unsigned char   Wef::version() const
{
  return m_wef_mem->wf_version;
}

const double    &Wef::operator[](unsigned int index) const
{
  return m_wef_mem->wf_wave[index % m_wef_mem->wf_size];
}

const double    &Wef::operator()(unsigned int index,
                                 unsigned int grain) const
{
  unsigned int pos;

  grain = grain % m_wef_mem->wf_grain_count;
  pos = m_wef_mem->wf_grain_index[grain].grain_pos;
  pos = pos + index % (m_wef_mem->wf_grain_index[grain].grain_size);
  return m_wef_mem->wf_wave[pos];
}
