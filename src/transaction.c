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
#include "parser.h"
#include "tdlib.h"
#include "transaction.h"

#define DA_INITIALIZER_VALUE 10

void
load_transactions (struct v_transaction *to, const char *from_file)
{
  FILE *fp;
  char line[MAX_LINE_SIZE];

  if (!file_exists (from_file))
    ensure_file_exists (from_file);

  fp = fopen (from_file, "r");
  if (fp == NULL)
    {
      fprintf (stderr, "fopen(%s): %s\n", from_file, strerror (errno));
      exit (EXIT_FAILURE);
    }

  to->length = 0;
  to->capacity = 0;
  while (fgets (line, MAX_LINE_SIZE, fp) != NULL)
    {
      struct transaction *t;
      size_t sz;
      char **tokens = tokenize_transaction (line);

      sz = sizeof (struct transaction);
      t = (struct transaction *) malloc (sz);
      if (t == NULL)
        PANIC ("main: memory allocation failed (size: %zu)\n", sz);

      strcpy (t->id, tokens[0]);
      strcpy (t->date, tokens[1]);
      strcpy (t->category, tokens[2]);
      t->amount = strtod (tokens[3], NULL);
      strcpy (t->description, tokens[4]);

      append_transaction (to, t);
    }

  fclose (fp);
}

void
append_transaction (struct v_transaction *vec_txn, struct transaction *txn)
{
  if (vec_txn->capacity == 0)
    {
      /* Create new array; append and return. */
      size_t size;

      size = sizeof (struct transaction *) * DA_INITIALIZER_VALUE;

      vec_txn->capacity = DA_INITIALIZER_VALUE;
      vec_txn->transactions = (struct transaction **) malloc (size);
      if (vec_txn->transactions == NULL)
        PANIC ("append_transaction: memory allocation failed (size: %zu)\n",
               size);

      vec_txn->transactions[vec_txn->length++] = txn;
      return;
    }
  else
    {
      if (vec_txn->length >= vec_txn->capacity)
        {
          /* Reallocate; append and return. */
          size_t size;

          vec_txn->capacity *= 2;
          size = sizeof (struct transaction *) * vec_txn->capacity;

          struct transaction **new_array =
            realloc (vec_txn->transactions, size);
          if (new_array == NULL)
            PANIC ("append_transaction: memory reallocation failed"
                   "(size: %zu)\n", size);

          vec_txn->transactions = new_array;
          vec_txn->transactions[vec_txn->length++] = txn;
          return;
        }

      /* Append and return. */
      vec_txn->transactions[vec_txn->length++] = txn;
      return;
    }
}

void
print_transaction (const struct transaction t)
{
  printf ("Transaction {\n");
  printf ("\tid: %s\n", t.id);
  printf ("\tdate: %s\n", t.date);
  printf ("\tamount: %lf\n", t.amount);
  printf ("\tcategory: %s\n", t.category);
  printf ("\tdescription: %s\n", t.description);
  printf ("}\n");
}
