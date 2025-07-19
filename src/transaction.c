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

#include "config.h"
#include "transaction.h"
#include "tdlib.h"

/* Slices a string from start (incl.) to end (excl.) without modification. */
static char *
strslice (const char *str, int start, int end)
{
  size_t i, sz;
  char *sb;

  trap (start < 0 && end < 0, "negative indexing not supported");

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

char **
tokenize_transaction (char line[])
{
  size_t i = 0, start = 0, end = 0;
  char *buf;

  size_t token_array_sz;
  char **tokens;

  token_array_sz = sizeof (char *) * 5;
  tokens = (char **) malloc (token_array_sz);
  if (tokens == NULL)
    {
      fprintf (stderr,
               "tokenize_transaction: memory allocation failed (size: %zu)\n",
               token_array_sz);
      exit (EXIT_FAILURE);
    }

  buf = line;
  while (*buf != '\0')
    {
      if (*buf == '\t')
        {
          char *slice = strslice (line, start, end);
          tokens[i++] = slice;

          start = end + 1;
        }

      end++;
      buf++;
    }

  if (start < end)
    {
      char *slice = strslice (line, start, end);
      tokens[i++] = slice;
    }

  return tokens;
}

void
append_transaction (struct AccountStatement *as, struct Transaction *t)
{
  if (as->capacity == 0)
    {
      /* Create new, append, return */
      size_t sz;

      as->capacity = 10;
      sz = sizeof (struct Transaction *) * as->capacity;
      as->transactions = (struct Transaction **) malloc (sz);
      if (!as->transactions)
        {
          fprintf (stderr,
                   "append_transaction: memory allocation failed (size: %zu)\n",
                   sz);
          exit (EXIT_FAILURE);
        }

      as->transactions[as->length++] = t;
      return;
    }
  else
    {
      if (as->length >= as->capacity)
        {
          /* Reallocate, append and return */
          size_t sz;

          as->capacity *= 2;
          sz = sizeof (struct Transaction *) * as->capacity;
          struct Transaction **new_array = realloc (as->transactions, sz);
          if (new_array == NULL)
            {
              fprintf (stderr,
                       "append_transaction: memory reallocation failed (size: %zu)\n",
                       sz);
              exit (EXIT_FAILURE);
            }

          as->transactions = new_array;
          as->transactions[as->length++] = t;
          return;
        }

      /* Append and return */
      as->transactions[as->length++] = t;
      return;
    }
}

void
print_transaction (const struct Transaction t)
{
  printf ("Transaction {\n");
  printf ("\tid: %s\n", t.id);
  printf ("\tdate: %s\n", t.date);
  printf ("\tamount: %lf\n", t.amount);
  printf ("\tcategory: %s\n", t.category);
  printf ("\tdescription: %s\n", t.description);
  printf ("}\n");
}

void
print_acstatement (const struct AccountStatement as)
{
  size_t i;
  int deposits = 0, withdrawals = 0;
  double s_deposits = 0.0f, s_withdrawals = 0.0f;
  
  
  printf("%-7s | %-10s | %-15s | %10s | %s\n",
	 "ID", "Date", "Category", "Amount", "Description");
  printf("--------+------------+-----------------+------------+---------------------------\n");

  for (i = 0; i < as.length; ++i)
    {
      struct Transaction *t;
      t = as.transactions[i];

      if (t->amount > 0)
	{
	  s_deposits += t->amount;
	  deposits++;
	}
      else
	{
	  s_withdrawals += t->amount;
	  withdrawals++;
	}
      
      printf("%-7s | %-10s | %-15.15s | %10.2f | %s\n",
	     t->id, t->date, t->category, t->amount, t->description);
    }

  printf("--------+------------+-----------------+------------+---------------------------\n\n");
  printf("Account Summary:\n");
  printf("  Total transactions  : %zu\n", as.length);
  printf("  Deposits (CR)       : %d (Total: %s%.2f)\n",
	 deposits, CURRENCY_SYMBOL, s_deposits);
  printf("  Withdrawals (DR)    : %d (Total: %s%.2f)\n",
	 withdrawals, CURRENCY_SYMBOL, -s_withdrawals);
  printf("  Net balance change  : %s%.2f\n",
	 CURRENCY_SYMBOL, s_deposits + s_withdrawals);
}
