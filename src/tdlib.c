/*
  dhanavraksha - Personal finance logger
  tdlib.c -- This file contains a small part of the tdlib project still in
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

#include "tdlib.h"

char *
strslice (const char *str, int start, int end)
{
  size_t i, sz;
  char *sb;

  TRAP (start < 0 && end < 0, "negative indexing not supported");

  sz = sizeof (char) * (end - start);
  sb = (char *) malloc (sz);
  if (sb == NULL)
    {
      fprintf (stderr, "strslice: memory allocation failed (size: %zu)\n",
               sz);
      exit (EXIT_FAILURE);
    }

  for (i = 0; start < end; ++start, ++i)
    {
      sb[i] = str[start];
    }

  return sb;
}

void
str_to_low (char *str)
{
  char *p;

  p = str;

#ifdef DEBUG
  printf ("str_to_low (in): str = \"%s\"\n", str);
#endif /* DEBUG */

  while (*p != '\0')
    {
      if (*p >= 65 && *p <= 90)
        *p += 32;
      p++;
    }

#ifdef DEBUG
  printf ("str_to_low (out): str = \"%s\"\n", str);
#endif /* DEBUG */
}

void
idgen (char *buf, size_t len)
{
  size_t i;
  const char *allowed;

  allowed = "0123456789abcdef";
  for (i = 0; i < len; ++i)
    buf[i] = allowed[rand () % 16];

  buf[len - 1] = '\0';
}
