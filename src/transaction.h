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

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stddef.h>

struct Transaction
{
  char id[7];
  char date[10 + 1];
  char category[64];
  double amount;
  char description[256];
};

struct AccountStatement
{
  struct Transaction **transactions;
  size_t length;
  size_t capacity;
};

/* Convert transcation data (of a specific style) into an array of tokens */
char **tokenize_transaction (char line[]);

/* Appends a transaction into the dynamic array struct AccountStatement */
void append_transaction (struct AccountStatement *as, struct Transaction *t);

/* Prints the given transaction struct in object notation */
void print_transaction (const struct Transaction t);

/* Prints account statement i.e., list of transactions in tabular form */
void print_acstatement (const struct AccountStatement as);

#endif /* TRANSACTION_H */
