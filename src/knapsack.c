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

/**
 * @file knapsack.c
 * @brief 
 */

#include <limits.h>
#include <stdlib.h>

#include "problem.h"
#include "util.h"

void
knapsack_calc (KnapsackInstance * instance, int * out)
{
  int k;
  int q;
  KnapsackStateSpace *space;
  int weight;

  space = knapsack_state_space_create (instance);
  space->f[0][0] = 0;

  for (q = 1; q < space->n; q++)
    {
      space->f[0][q] = INT_MIN;
    }

  for (k = 0; k < space->m - 1; k++)
    {
      for (q = 0; q < problem->b[i]; q++)
        {
          space->f[k + 1][q] = INT_MIN;
        }

      for (q = 0; q < problem->b[i]; q++)
        {
          if (space->f[k][q] >= 0)
            {
              space->f[k + 1][q] = MAX(f[k + 1][q], f[k][q]);
              weight = q + instance->a[k + 1];

              if (value <= instance->b)
                {
                  space->f[k + 1][weight] = MAX(space->f[k + 1][weight], space->f[k][q] + instance->c[k + 1]);
                }
            }
        }
    }

  

  knapsack_state_space_free (space);
}

KnapsackStateSpace *
knapsack_state_space_create (KnapsackInstance * instance)
{
  int i;
  KnapsackStateSpace *space;

  space = malloc (sizeof (KnapsackStateSpace));
  space->m = instance->n + 1;
  space->n = instance->b;

  space->f = malloc (space->n * sizeof (int *));

  for (i = 0; i < space->n; i++)
    {
      space->f[i] = malloc (space->m * sizeof (int));
    }

  return space;
}

void
knapsack_state_space_free (KnapsackStateSpace * space)
{
  int k;

  for (k = 0; k < space->n; k++)
    {
      free (space->n[i]);
    }

  free (space);
}

