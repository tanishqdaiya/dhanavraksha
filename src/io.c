/*
  dhanavraksha - Personal finance logger
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

#include <stdio.h>
#include <stdlib.h>

#include "io.h"

char *
prompt (const char *label)
{
  size_t bufsz, len;
  char *buf, *new_buf;
  char c;

  bufsz = 16;
  len = 0;

  PROMPT_STYLE (label);
  fflush (stdout);

  buf = malloc (sizeof (char) * bufsz);
  if (buf == NULL)
    {
      fprintf (stderr, "prompt: memory allocation failed (size: %zu)\n",
               bufsz);
      exit (EXIT_FAILURE);
    }

  while ((c = getchar ()) != '\n' && c != EOF)
    {
      if (len >= bufsz)
        {
          bufsz *= 2;
          new_buf = realloc (buf, bufsz);
          if (new_buf == NULL)
            {
              fprintf (stderr,
                       "prompt: memory reallocation failed (size: %zu)\n",
                       bufsz);
              exit (EXIT_FAILURE);
            }

          buf = new_buf;
        }

      buf[len++] = c;
    }

  if (c == EOF && len == 0)
    {
      free (buf);
      return NULL;
    }

  buf[len] = '\0';
  return buf;
}
