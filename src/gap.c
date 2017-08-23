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
#include <math.h>

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
    printf ("valore soluzione gap: %d\n", cost);
  return cost;
}

double
gap_calcuate_lagrangian_function (Problem * problem)
{
  double cost = 0;
  int i;
  int j;

  for (i = 0; i < problem->m; i++)
    {
      for (j = 0; j < problem->n; j++)
        {
          cost += problem->costs[i][j] * problem->x[i][j];
        }
        cost += problem->u[i] * problem->b[i];
    }

  printf ("valore soluzione lagrnagiana: %f\n", cost);
  return cost;
}

void
gap_calculate_initial_lagrangian (Problem * problem)
{
  int i;
  int j;
  int minIndex;
  double minValue;

  //set to 1 variables that have min cost
  for (j = 0; j < problem->n; j++)
    {
      minIndex = 0;
      minValue = problem->costs[0][j];

      for (i = 0; i < problem->m; i++)
        {
          problem->x[i][j] = 0;
          if (problem->costs[i][j] < minValue)
            {
              minIndex = i;
              minValue = problem->costs[i][j];
            }
        }

     problem->x[minIndex][j] = 1;
    }

  // for (i = 0; i < problem->m; i++)
  //   {
  //     printf ("\n");

  //     for (j = 0; j < problem->n; j++)
  //   	{
  //   	  printf ("%d ", problem->x[i][j]);
  //   	}
  //   }

  // printf ("\n");
}

void
gap_get_costs_with_relaxiation(Problem * problem)
{
    // printf("-----costs: \n");

    for (int i = 0; i < problem->m; ++i)
    {
        for (int j = 0; j < problem->n; ++j)
        {
          problem->costs[i][j] = problem->c[i][j] - ( problem->u[i] * problem->a[i][j] );
          // printf("%f ", problem->costs[i][j] );
        }
    // printf("\n");
    }
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

      if(sum >= problem->b[i])
      {
        printf("Constraints not satisfied!\n");
        return 0;
      }
    }

    printf("Constraints satisfied!\n");
    return 1;
}

int
gap_are_lagrangian_constraints_satisfied (Problem * problem)
{
   int i,j,sum;

   for (i = 0; i < problem->m; i++)
    {
      sum = 0;

      for (j = 0; j < problem->n; j++)
        {
          sum += problem->a[i][j] * problem->x[i][j];
        }

      if( problem->u[i] * (sum - problem->b[i]) != 0.0)
      {
        printf("Lagrangian constraints not satisfied!\n");
        return 0;
      }
    }

    printf("Lagrangian constraints satisfied!\n");
    return 1;
}

int*
gap_calculate_subgradient_stepsize_vector(Problem * problem)
{
  int sum;
  int* y = calloc (problem->m, sizeof (int));

  for (int i = 0; i < problem->m; i++)
  {
    sum = 0;

    for (int j = 0; j < problem->n; j++)
      {
        sum += problem->a[i][j] * problem->x[i][j];
      }

    y[i] = sum - problem->b[i];
  }
  return y;
}

int
gap_calculate_subgradient_stepsize(int* y, int m)
{
  int sum = 0;

  for (int i = 0; i < m; i++)
    sum += y[i] * y[i];

  return sum;
}

int
gap_subgradient(Problem * problem)
{

  int maxIter = 150;
  float alpha = 1;
  int delta = 20; //after delta iteration alpha = alpha/2
  int trials = 0;
  double lb = -999;
  double lu;
  int iter = 1;
  int* y;
  double step_size;
  float res;
  double lz =  333;
  int** xOpt = malloc (problem->m * sizeof (int *));

  for (int i = 0; i < problem->m; i++)
    {
      xOpt[i] = calloc (problem->n, sizeof (int));
    }

  while(iter <= maxIter)
  {
    // char x = getchar();

    gap_get_costs_with_relaxiation(problem);

    gap_calculate_initial_lagrangian(problem);

    lu = gap_calcuate_lagrangian_function(problem);


    if(lu > lb)
    {
        lb = lu;
        trials = 0;
        lz = lb < 0.0 ? (-lb * 0.3) : lb * 0.3;
        copyMatrix(problem->x, xOpt, problem->m, problem->n);
    }

    //solution x is optimal -> STOP
    if(gap_are_constraints_satisfied(problem) == 1 && gap_are_lagrangian_constraints_satisfied(problem) == 1)
    {
      printf("Exit subgradient function...optimal solution found!\n");
      return 0;
    }

    y = gap_calculate_subgradient_stepsize_vector(problem);
    step_size = sqrt((double)gap_calculate_subgradient_stepsize(y, problem->m));
    
    //definisci nuovi u
    for (int i = 0; i < problem->m; ++i)
    {

      res = problem->u[i] - alpha * (lz /step_size) * y[i];
      // printf("res: %f = %f - (%f * (%f / %f ) * %d \n", res, problem->u[i], alpha ,lz, step_size, y[i]);
      problem->u[i] = res < 0.0 ? res : 0.0;
      // printf("u: %f\n", problem->u[i]);
    }

    iter++;   
    //if L(u) <= lb for trials consecutive iterations then is a good practice to decrement alpha
    trials++;
    if(trials == delta){
      alpha = alpha * 0.75;
      trials = 0;
    }
  }

  copyMatrix(xOpt, problem->x, problem->m, problem->n);

  printf("Exit subgradient function...maxIter limit reached!\n");
  printf("x: \n");

  for (int i = 0; i < problem->m; i++)
    {
      printf ("\n");

      for (int j = 0; j < problem->n; j++)
  {
    printf ("%d ", problem->x[i][j]);
  }
    }

  printf ("\n");

  return 1;
}