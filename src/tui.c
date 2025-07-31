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

#include "config.h"
#include "tui.h"

void
print_transactions (const struct v_transaction vt)
{
  size_t i;
  int deposits = 0, withdrawals = 0;
  double s_deposits = 0.0f, s_withdrawals = 0.0f;
  
  
  printf("%-7s | %-10s | %-15s | %10s | %s\n",
	 "ID", "Date", "Category", "Amount", "Description");
  printf("--------+------------+-----------------+------------+---------------------------\n");

  for (i = 0; i < vt.length; ++i)
    {
      struct transaction *t;
      t = vt.transactions[i];

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
  printf("  Total transactions  : %zu\n", vt.length);
  printf("  Deposits (CR)       : %d (Total: %s%.2f)\n",
	 deposits, CURRENCY_SYMBOL, s_deposits);
  printf("  Withdrawals (DR)    : %d (Total: %s%.2f)\n",
	 withdrawals, CURRENCY_SYMBOL, -s_withdrawals);
  printf("  Net balance change  : %s%.2f\n",
	 CURRENCY_SYMBOL, s_deposits + s_withdrawals);
}
