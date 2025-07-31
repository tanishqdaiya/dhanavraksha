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

#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include <stddef.h>

struct transaction
{
  char id[7];                   /* hex id of six characters */
  char date[11];                /* YYYY-MM-DD format */
  char category[64];
  double amount;
  char description[256];
};

struct v_transaction
{
  struct transaction **transactions;
  size_t length;
  size_t capacity;
};

void append_transaction (struct v_transaction *vec_txn,
                         struct transaction *txn);

void load_transactions (struct v_transaction *to, const char *filename);

void print_transaction (const struct transaction t);

#endif /* _TRANSACTION_H */
