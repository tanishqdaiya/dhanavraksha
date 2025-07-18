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

#ifndef IO_H
#define IO_H

/* User-defined prompt-style. Use-carefully */
#ifndef PROMPT_STYLE
#define PROMPT_STYLE(label)			\
  do						\
    {						\
      printf ("%s> ", label);			\
    }						\
  while (0)
#endif /* PROMPT_STYLE */

/* Custom prompt function to take input by line into a buffer */
char *prompt (const char *label);

#endif /* IO_H */
