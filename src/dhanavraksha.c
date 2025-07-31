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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"

#include "io.h"
#include "tdlib.h"
#include "transaction.h"
#include "tui.h"

struct cmd_args
{
  uint8_t help;
  uint8_t version;
  const char *command;
};
struct cmd_args args;

struct v_transaction vector_transaction;

static void
usage (const char *progname, FILE *stream, int code)
{
  fprintf (stream,
           "Usage: %s [OPTION] COMMAND\n"
           "\n"
           "Personal finance logger.\n"
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
  exit (code);
}

/* Gets the current date in YYYY-MM-DD */
static void
get_today (char *buf, size_t bufsz)
{
  time_t t;
  struct tm *tm_info;

  TRAP (bufsz < 11, "get_today needs more buffer space");

  t = time (NULL);
  tm_info = localtime (&t);

  TRAP (tm_info == NULL, "failed to get time");

  strftime (buf, bufsz, "%Y-%m-%d", tm_info);
}

int
main (int argc, char **argv)
{
  srand (time (NULL));

  if (argc < 2)
    usage (argv[0], stderr, EXIT_FAILURE);

  {
    int i;
    const char *arg;

    for (i = 1; i < argc; ++i)
      {
        arg = argv[i];

        if (STRCMP_LIT (arg, "-h") == 0 || STRCMP_LIT (arg, "--help") == 0)
          args.help = 1;
        else if (STRCMP_LIT (arg, "-v") == 0
                 || STRCMP_LIT (arg, "--version") == 0)
          args.version = 1;
        else if (arg[0] != '-' && args.command == NULL)
          args.command = arg;
        else
          {
            fprintf (stderr, "Unknown argument: %s\n", arg);
            usage (argv[0], stderr, EXIT_FAILURE);
          }
      }
  }

  if (args.help)
    usage (argv[0], stdout, EXIT_SUCCESS);

  if (args.version)
    {
      fprintf (stdout, "Dhanavraksha %s \n", DHANAVRAKSHA_VERSION);
      exit (EXIT_SUCCESS);
    }

  if (STRCMP_LIT (args.command, "view") == 0)
    {
      clock_t begin;
      double time_spent;

      begin = clock ();
      load_transactions (&vector_transaction, WFILE);
      print_transactions (vector_transaction);
      time_spent = (double) (clock () - begin) / CLOCKS_PER_SEC;

      printf ("Indexed %zu Transaction(s) in %fs!\n",
              vector_transaction.length, time_spent);
    }
  else if (STRCMP_LIT (args.command, "entry") == 0)
    {
      struct transaction t;
      struct buffer *amount, *category, *description;

      amount = prompt ("Enter amount");
      category = prompt ("Enter category");
      description = prompt ("Enter description");

      idgen (t.id, 7);
      get_today (t.date, sizeof (t.date));
      t.amount = strtod (amount->data, NULL);
      strncpy (t.category, category->data, category->length);
      strncpy (t.description, description->data, description->length);

      print_transaction (t);

      if (confirm_yn ("Save record (Y/n)?", 'y') == 0)
        {
          FILE *fp;
          const char *filename;

          filename = WFILE;
          fp = fopen (WFILE, "a");
          if (fp == NULL)
            {
              fprintf (stderr, "fopen(%s): %s\n", filename, strerror (errno));
              exit (EXIT_FAILURE);
            }

          fprintf (fp, "%s\t%s\t%s\t%lf\t%s\n",
                   t.id, t.date, t.category, t.amount, t.description);
          fclose (fp);

          printf ("Record saved successfully!\n");
        }
    }
  else
    {
      fprintf (stderr, "Unknown argument: %s\n", args.command);
      usage (argv[0], stderr, EXIT_FAILURE);
    }
}
