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

#ifndef TDLIB_H
#define TDLIB_H

/* Aborts the program with msg if cond is met. */
#define trap(cond, msg)							\
  do									\
    {									\
      if (cond) {							\
	fprintf(stderr, "check failed: (%s)\n\t%s:%d: %s\n",		\
		#cond, __FILE__, __LINE__, msg);			\
	abort();							\
      }									\
    }									\
  while (0)

#endif /* TDLIB_H */
