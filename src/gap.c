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
#include <time.h>

#include "array_list.h"
#include "array_stack.h"
#include "gap.h"
#include "util.h"

//calculate a lower bound for the problem with Lagrangian relaxiation.
int
gap_lower_bound ()
{
  //calcolo L(u) : rilassamento lagrangiano
  //il duale di L(u) definito come Max [ L(u)], u >= 0 -> LOWER BOUND
  //per risolvere il duale lagrangiano posso usare metodo del subgradiente
  return 0;
}

//calculate a lower bound for the problem with Lagrangian relaxiation.
int
gap_branch_and_bound ()
{
  return 0;
}

//calculates total cost
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

  return cost;
}

int
gap_calcuate_lagrangian_function (Problem * problem)
{
  int i;
  int j;
  int result;
  int sum;
  int *u;

  //init result matrix
  result = gap_calculate_solution (problem);
  u = calloc (problem->m, sizeof (int));

  for (i = 0; i < problem->m; i++)
    {
      sum = 0;

      for (j = 0; j < problem->n; j++)
	{
	  sum += problem->c[i][j];
	}

      sum -= problem->b[i];
      result -= sum * u[i];
    }

  free (u);
  printf ("valore soluzione lagrnagiana: %d\n", result);
  return result;
}

void
gap_calculate_initial (Problem * problem)
{
  int i;
  int j;
  int minIndex;
  int minValue;

  //set to 1 variables that have min cost
  for (j = 0; j < problem->n; j++)
    {
      minIndex = 0;
      minValue = problem->c[0][j];

      for (i = 0; i < problem->m; i++)
	{
	  if (problem->c[i][j] < minValue)
	    {
	      minIndex = i;
	      minValue = problem->c[i][j];
	    }
	}

     problem->x[minIndex][j] = 1;
    }

  for (i = 0; i < problem->m; i++)
    {
      printf ("\n");

      for (j = 0; j < problem->n; j++)
	{
	  printf ("%d ", problem->x[i][j]);
	}
    }

  printf ("\n");
}

int
gap_are_constraints_satisfied (Problem * problem)
{
   int i,j,sum;

   for (i = 0; i < problem->m; i++)
    {
      sum = 0;

      for (j = 0; j < problem->n; j++)
        {
          sum += problem->a[i][j] * problem->x[i][j];
        }

      if(sum > problem->b[i])
      {
        printf("Constraints not satisifed!\n");
        return 0;
      }
    }

    printf("Constraints satisifed!\n");
    return 1;
}