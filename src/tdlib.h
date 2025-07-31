/*
  dhanavraksha - Personal finance logger
  tdlib.h -- This file contains a small part of the tdlib project still in
  development. Please note that the contents do not represent a finalized
  version of tdlib but only a part that is useful to the scope of the current
  project.
  
  Copyright (C) 2025  Tanishq Daiya <tanishqdaiya@yahoo.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _TDLIB_H
#define _TDLIB_H

#include <stdio.h>
#include <stdlib.h>

/* Aborts the program with msg if cond is true. */
#define TRAP(cond, msg)						\
  do								\
    {								\
      if (cond) {						\
	fprintf(stderr, "check failed: (%s)\n\t%s:%d: %s\n",	\
		#cond, __FILE__, __LINE__, msg);		\
	abort();						\
      }								\
    }								\
  while (0)

/* Prints the fmt string and exits the program with EXIT_FAILURE. */
#define PANIC(...)				\
  do						\
    {						\
      fprintf (stderr, __VA_ARGS__);		\
      fputc ('\n', stderr);			\
      exit (EXIT_FAILURE);			\
    }						\
  while (0)

#define STRCMP_LIT(s, literal)				\
  strncmp (s, "" literal "", sizeof (literal) - 1)

/* Slices a string from start (incl.) to end (excl.) without modification. */
char *strslice (const char *str, int start, int end);

/* Modifies the string provided string buffer into lowercase. */
void
str_to_low (char *str);

/* Writes a pseudo-randomly generated id into buffer buf of appropriate
   length. The len parameter defines the required length of the generated id. It
   is advisable to have a buffer of appropriate size since the program doesn't
   yet check for appropriate sizes. */
void idgen (char *buf, size_t len);

#endif /* _TDLIB_H */
