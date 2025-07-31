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

#include <stdlib.h>

#include "tdlib.h"
#include "transaction.h"

char **
tokenize_transaction (char line[])
{
  size_t i = 0;
  size_t start = 0, end = 0;
  char *buf;

  size_t size;
  char **tokens;

  size = 5 * sizeof (char *);
  tokens = (char **) malloc (size);
  if (tokens == NULL)
    PANIC ("tokenize_transaction: memory allocation failed (size: %zu)\n",
           size);

  buf = line;
  while (*buf != '\0')
    {
      if (*buf == '\t')
        {
          char *slice;

          slice = strslice (line, start, end);
          tokens[i++] = slice;
          start = end + 1;
        }

      end++;
      buf++;
    }

  if (start < end)
    {
      char *slice;
      slice = strslice (line, start, end);
      tokens[i++] = slice;
    }

  return tokens;
}
