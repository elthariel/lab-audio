//
// wef.cpp for libwef-cpp in /home/elthariel/code/lab-audio/libs/libwef
//
// Made by Nahlwe
// Login   <elthariel@epita.fr>
//
// Started on  Fri Feb  9 15:52:18 2007 Nahlwe
// Last update Mon May 28 18:26:23 2007 Elthariel
//

#include "wef.hh"
#include <cstdlib>
#include <cstring>

using namespace std;

Wef::Wef()
  : m_ro(false)
{
  m_wef_mem = (wfm *)malloc(sizeof(wfm));
  m_wef_mem->wf_version = 1;
  m_wef_mem->wf_magic = (char *)malloc(WEF_MAGIC_LEN);
  strcpy(m_wef_mem->wf_magic, "Wef-0");
  m_wef_mem->wf_name = (char *)malloc(WEF_NAME_LEN);
  m_wef_mem->wf_author = (char *)malloc(WEF_AUTHOR_LEN);
  memset((void *)m_wef_mem->wf_name, 0, WEF_NAME_LEN);
  memset((void *)m_wef_mem->wf_author, 0, WEF_AUTHOR_LEN);
  m_wef_mem->wf_grain_count = 0;
  m_wef_mem->wf_size = 0;
  m_wef_mem->wf_file = 0;
  m_wef_mem->wf_grain_index = 0;
  m_wef_mem->wf_wave = 0;
}

Wef::Wef(std::string path)
  : m_path(path),
    m_ro(true)
{
  m_wef_mem = wef_open(m_path.c_str());
}

Wef::~Wef()
{
  if (m_ro)
    wef_close(m_wef_mem);
  else
    {
      free(m_wef_mem->wf_magic);
      free(m_wef_mem->wf_name);
      free(m_wef_mem->wf_author);
      free(m_wef_mem->wf_grain_index);
      free(m_wef_mem->wf_wave);
      if (m_wef_mem->wf_file)
        free(m_wef_mem->wf_file);
      free(m_wef_mem);
    }
}

bool            Wef::is_readonly()
{
  return m_ro;
}

void            Wef::make_writable()
{
  // FIXME malloc & copy wef data, free wef_file.
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
  else
    return 0;
}

unsigned int    Wef::get_grain_pos(unsigned int grain) const
{
  if (grain < m_wef_mem->wf_grain_count)
    return m_wef_mem->wf_grain_index[grain].grain_pos;
  else
    return 0;
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

double          &Wef::operator[](unsigned int index) const
{
  return m_wef_mem->wf_wave[index % m_wef_mem->wf_size];
}

double          &Wef::operator()(unsigned int index,
                                 unsigned int grain) const
{
  unsigned int pos;

  grain = grain % m_wef_mem->wf_grain_count;
  pos = m_wef_mem->wf_grain_index[grain].grain_pos;
  pos = pos + index % (m_wef_mem->wf_grain_index[grain].grain_size);
  return m_wef_mem->wf_wave[pos];
}


/*
 * Mutators
 */
void            Wef::set_grain_count(unsigned int count)
{
  if (!m_ro)
    {
      m_wef_mem->wf_grain_count = count;
      m_wef_mem->wf_grain_index = (grain *)realloc(m_wef_mem->wf_grain_index,
                                                   count * sizeof(grain));
    }
}

void            Wef::set_grain_size(unsigned int index,
                                    unsigned int size)
{
  if (!m_ro)
    {
      index %= m_wef_mem->wf_grain_count;
      m_wef_mem->wf_grain_index[index].grain_size = size;
    }
}

void            Wef::set_grain_pos(unsigned int index,
                                   unsigned int pos)
{
  if (!m_ro)
    {
      index %= m_wef_mem->wf_grain_count;
      m_wef_mem->wf_grain_index[index].grain_pos = pos;
    }
}

void            Wef::set_name(const char *name)
{
  if (!m_ro)
    {
      free (m_wef_mem->wf_name);
      m_wef_mem->wf_name = strndup(name, WEF_NAME_LEN - 1);
    }
}

void            Wef::set_author(const char *author)
{
  if (!m_ro)
    {
      free (m_wef_mem->wf_author);
      m_wef_mem->wf_author = strndup(author, WEF_NAME_LEN - 1);
    }
}

void            Wef::set_wave(double *wave, unsigned int size)
{
  if (!m_ro)
    {
      if (m_wef_mem->wf_wave)
        free(m_wef_mem->wf_wave);
      m_wef_mem->wf_wave = wave;
      m_wef_mem->wf_size = size;
    }
}

bool            Wef::write_wef(std::string a_path)
{
  return true;
}

void            Wef::build_wef_file()
{
}
