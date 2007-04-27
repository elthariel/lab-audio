//
// foncteurs.hpp for zia in /home/elthariel/code/httpd/src
//
// Made by Nahlwe
// Login   <elthariel@epita.fr>
//
// Started on  Fri Feb 23 08:08:39 2007 Nahlwe
// Last update Mon Apr  2 13:26:03 2007 Nahlwe
//

#ifndef FONCTEURS_HPP
# define FONCTEURS_HPP

template <class return_type>
class iFoncteur0
{
public:
  virtual return_type   operator()() = 0;
  virtual ~iFoncteur0(){}
};

#endif
