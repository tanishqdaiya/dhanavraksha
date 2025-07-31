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

#ifndef _IO_H
#define _IO_H

#include <stdint.h>

#define MAX_LINE_SIZE 4096

/* General definition of a buffer */
struct buffer
{
  char *data;
  size_t length, capacity;
};

/* User-defined prompt-style. Use-carefully */
#ifndef PROMPT_STYLE
#define PROMPT_STYLE(label)			\
  do						\
    {						\
      printf ("%s> ", label);			\
    }						\
  while (0)
#endif /* PROMPT_STYLE */

/* Creates a file with given filename, generally used with file_exists fn */
void ensure_file_exists (const char *filename);

/* Checks if a given file with filename exists */
bool file_exists (const char *filename);

/* Custom prompt function to take input by line into a buffer */
struct buffer *prompt (const char *label);

/* Yes and No prompt, based on the prompt function */
uint8_t confirm_yn (const char *label, char def);

#endif /* _IO_H */
