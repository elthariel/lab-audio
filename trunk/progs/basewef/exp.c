/*
** exp.c
** Login : <elthariel@elthariel-desktop>
** Started on  Sat Feb 10 07:40:00 2007 Nahlwe
** $Id$
**
** Copyright (C) 2007 Nahlwe
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <math.h>
#include "trivial_analog.h"

double          *exp_gen(int *wavelen)
{
  int           i;
	double        *table;

	*wavelen = EXP_LEN;
	table = malloc(sizeof(double) * (*wavelen));
	for (i = 0; i < *wavelen; i++)
	{
    table[i] = exp(- (((double)i) / EXP_LEN) * 4);
  }
  return (table);
}

double          *exp10_gen(int *wavelen)
{
  int           i;
	double        *table;

	*wavelen = EXP10_LEN;
	table = malloc(sizeof(double) * (*wavelen));
	for (i = 0; i < *wavelen; i++)
	{
    table[i] = exp10(- (((double)i) / EXP10_LEN) * 3);
  }
  return (table);
}

