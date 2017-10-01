/*
 * This file is part of gap.
 *
 * gap is free software: you can redistribute it and/or modify
 * under the terms of the GNU General Public License as published by
 * Free Software Foundation, either version 3 of the License, or
 * your option) any later version.
 *
 * gap is distributed in the hope that it will be useful,
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * CHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gap.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "problem.h"
#include "gap.h"

// calculates c * x
int
gap_calculate_solution (Problem * problem)
{
  int cost = 0;
  int i;
  int j;

  for (i = 0; i < problem->m; i++)
  {
    for (j = 0; j < problem->n; j++)
  	{
  	  cost += problem->c[i][j] * problem->x[i][j];
  	}
  }
  printf ("valore soluzione gap: %d\n", cost);
  return cost;
}

// inverts costs of problem:
//  Max = - Min
void
invert_for_max_problem (Problem * problem)
{
  for (int i = 0; i < problem->m; ++i)
    for (int j = 0; j < problem->n; ++j)
      problem->c[i][j] = -(problem->c[i][j]);
}