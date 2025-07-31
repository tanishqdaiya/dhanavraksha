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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "tdlib.h"

void
ensure_file_exists (const char *filename) {
    FILE *f = fopen (filename, "a");

    if (!f)
      {
	fprintf (stderr, "fopen(%s): %s\n", filename, strerror (errno));
	exit (EXIT_FAILURE);
      }

    fclose (f);
}

bool
file_exists (const char *filename)
{
    FILE *file = fopen (filename, "r");

    if (file)
      {
	fclose(file);
	return true;
      }

    return false;
}

struct buffer *
prompt (const char *label)
{
  char c;
  struct buffer *buf;

  PROMPT_STYLE (label);
  fflush (stdout);

  buf = (struct buffer *)malloc (sizeof (struct buffer));
  if (buf == NULL)
    PANIC ("prompt: memory allocation failed (size: %zu)\n",
	   sizeof (struct buffer));

  buf->length = 0;
  buf->capacity = 16;
  buf->data = (char *)malloc (sizeof (char) * buf->capacity);
  if (buf->data == NULL)
    PANIC ("prompt: memory allocation failed (size: %zu)\n", buf->capacity);

#ifdef DEBUG
  printf ("prompt (init): Buffer {\n");
  printf ("\tlength: %zu\n", buf->length);
  printf ("\tcapacity: %zu\n", buf->capacity);
  printf ("\tdata: %s\n", buf->data);
  printf ("}\n");
#endif /* DEBUG */

  while ((c = getchar ()) != '\n' && c != EOF)
    {
      if (buf->length >= buf->capacity)
	{
	  buf->capacity *= 2;
	  buf->data = (char *)realloc (buf->data,
				       sizeof (char) * buf->capacity);
	  if (buf->data == NULL)
	    PANIC ("prompt: memory reallocation failed (size: %zu)\n",
		   buf->capacity);
	}

      buf->data[buf->length++] = c;
    }
  buf->data[buf->length] = '\0';

#ifdef DEBUG
  printf ("prompt (out): Buffer {\n");
  printf ("\tlength: %zu\n", buf->length);
  printf ("\tcapacity: %zu\n", buf->capacity);
  printf ("\tdata: %s\n", buf->data);
  printf ("}\n");
#endif /* DEBUG */

  return buf;
}

uint8_t
confirm_yn (const char *label, char def)
{
  uint8_t confirm, tries;
  struct buffer *buf;

  /* confirm: 0->true; 1->false and 2->for retrial */
  confirm = 2;
  tries = 3;

  while (confirm == 2 && tries != 0)
    {
      buf = prompt (label);
      if (buf->length > 1)
	{
	  printf ("Sorry, please try again!\n");
	  tries--;
	  continue;
	}

      if (buf->length == 0)
	{
	  str_to_low (&def);
	  if (def == 'y') confirm = 0;
	  if (def == 'n') confirm = 1;
	  break;
	}

      str_to_low (buf->data);

      if (strncmp (buf->data, "y", 1) == 0)
	confirm = 0;

      if (strncmp (buf->data, "n", 1) == 0)
	confirm = 1;

      tries--;
    }

  return confirm;
}

#if 0
bool
confirm_yn (const char *label, const char *default_response)
{
  struct buffer *buf;

  TRAP (strlen (default_response) > 1, "confirm_yn: default response should be"
	"a single character\n");

  do {
    buf = prompt (label);
    str_to_low (buf->data);

    if (buf->length == 0)
      strncpy (buf->data, default_response, 2);

    printf ("data: %s\n", buf->data);

    if (buf->data[0] == 'y')
      printf ("%s yes received\n", buf->data);
    else if (buf->data[0] == 'n')
      printf ("%s no received\n", buf->data);
    else
      continue;
  } while (true);
}
#endif
