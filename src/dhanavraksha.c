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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"

#include "io.h"
#include "tdlib.h"
#include "transaction.h"

/* Prints program usage. Use for bad arguments */
static void
usage (const char *progname)
{
  fprintf (stderr,
	   "Usage: %s [OPTION] COMMAND\n"
	   "\n"
	   "Personal transaction tracker.\n"
	   "\n"
	   "Options:\n"
	   "  -h, --help        Show this help message and exit\n"
	   "  -v, --version     Show version information and exit\n"
	   "\n"
	   "Commands:\n"
	   "  view              View transaction records\n"
	   "  entry             Enter a new transaction record\n"
	   "\n"
	   "Example:\n"
	   "  %s entry\n" "  %s view\n", progname, progname, progname);
  exit (EXIT_FAILURE);
}

/* Generates an hex_id of given length using rand. Writes to buf. */
static void
idgen (char *buf, size_t len)
{
  const char *hex = "0123456789abcdef";
  for (size_t i = 0; i < len - 1; ++i)
    buf[i] = hex[rand () % 16];
  buf[len - 1] = '\0';
}

static void
get_today (char *buf, size_t bufsz)
{
  time_t t;
  struct tm *tm_info;

  trap (bufsz < 11, "get_today needs more buffer space");

  t = time (NULL);
  tm_info = localtime (&t);

  trap (tm_info == NULL, "failed to get time");

  strftime (buf, bufsz, "%Y-%m-%d", tm_info);
}

static void
ensure_file_exists (const char *filename) {
    FILE *f = fopen (filename, "a");

    if (!f)
      {
	fprintf (stderr, "fopen(%s): %s\n", RECORD_FILE, strerror (errno));
	exit (EXIT_FAILURE);
      }

    fclose (f);
}

static bool
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

int
main (int argc, char **argv)
{
  struct AccountStatement as;

  srand (time (NULL));

  if (argc < 2)
    usage (argv[0]);

  if (strcmp (argv[1], "-h") == 0 || strcmp (argv[1], "--help") == 0)
    usage (argv[0]);

  if (strcmp (argv[1], "-v") == 0 || strcmp (argv[1], "--version") == 0)
    {
      fprintf (stdout, DHANAVRAKSHA_VERSION);
      exit (EXIT_SUCCESS);
    }

  {
    FILE *fp;
    char line[MAX_LINE_SIZE];

    if (!file_exists (RECORD_FILE))
      ensure_file_exists (RECORD_FILE);

    fp = fopen (RECORD_FILE, "r");
    if (fp == NULL)
      {
	fprintf (stderr, "fopen(%s): %s\n", RECORD_FILE, strerror (errno));
	exit (EXIT_FAILURE);
      }

    as.length = 0;
    as.capacity = 0;
    while (fgets (line, MAX_LINE_SIZE, fp) != NULL)
      {
	struct Transaction *t;
	size_t sz;
	char **tokens = tokenize_transaction (line);

	sz = sizeof (struct Transaction);
	t = (struct Transaction *) malloc (sz);
	if (t == NULL)
	  {
	    fprintf (stderr, "main: memory allocation failed (size: %zu)\n",
		     sz);
	    exit (EXIT_FAILURE);
	  }

	strcpy (t->id, tokens[0]);
	strcpy (t->date, tokens[1]);
	strcpy (t->category, tokens[2]);
	t->amount = strtod (tokens[3], NULL);
	strcpy (t->description, tokens[4]);

	append_transaction (&as, t);
      }

    fclose (fp);
  }

  if (strcmp (argv[1], "view") == 0)
    print_acstatement (as);

  /* Entry is relatively unsafe since it doesn't check for user balance. In
     later versions, other functions will be introduced for ease-of-use. */
  if (strcmp (argv[1], "entry") == 0)
    {
      struct Transaction t;

      idgen (t.id, 7);
      get_today (t.date, 11);
      t.amount = strtod (prompt ("Amount"), NULL);
      strcpy (t.category, prompt ("Category"));
      strcpy (t.description, prompt ("Description"));

      print_transaction (t);

      char *confirm = prompt ("save record? (y/n)");    /* @Improve confirmation */
      if (strcmp (confirm, "y") == 0)
	{
	  FILE *fp;
	  fp = fopen (RECORD_FILE, "a");
	  if (fp == NULL)
	    {
	      fprintf (stderr, "fopen(%s): %s\n", RECORD_FILE,
		       strerror (errno));
	      exit (EXIT_FAILURE);
	    }

	  fprintf (fp, "%s\t%s\t%s\t%lf\t%s\n",
		   t.id, t.date, t.category, t.amount, t.description);
	  fclose (fp);
	}
    }
}
