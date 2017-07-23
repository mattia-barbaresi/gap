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
gap_calculate_solution (Problem problem)
{
  int cost = 0;
  int i;
  int j;

  for (i = 0; i < problem.m; ++i)
    {
      for (j = 0; j < problem.n; ++j)
	{
	  cost += problem.c[i][j] * problem.x[i][j];
	}
    }

  return cost;
}

int
gap_calcuate_lagrangian_function (Problem problem)
{
  int n = problem.n;
  int m = problem.m;

  //init result matrix
  int result = gap_calculate_solution (problem);

  int *u = calloc (sizeof (int), m);
  int sum;

  for (int i = 0; i < m; ++i)
    {
      sum = 0;

      for (int j = 0; j < n; ++j)
	{
	  sum += problem.c[i][j];
	}

      sum -= problem.b[i];
      result -= sum * u[i];
    }

  return result;
}

int **
gap_calculate_initial (Problem problem)
{
  int **res = malloc (problem.m * sizeof (int *));
  int q;
  res[0] = calloc (sizeof (int), problem.n * problem.m);
  for (q = 1; q < problem.m; q++)
    res[q] = res[0] + q * problem.n;

  int minIndex;
  int minValue;

  //set to 1 variables that have min cost
  for (int i = 0; i < problem.m; ++i)
    {
      minIndex = 0;
      minValue = problem.c[i][0];

      for (int j = 0; j < problem.n; ++j)
	{
	  if (problem.c[i][j] < minValue)
	    {
	      minIndex = j;
	      minValue = problem.c[i][j];
	    }
	}

      res[i][minIndex] = 1;
    }

  for (int i = 0; i < problem.m; ++i)
    {
      printf ("\n");
      for (int j = 0; j < problem.n; ++j)
	{
	  printf ("%d ", res[i][j]);
	}
    }
  return res;
}

void
gap_problem_free (Problem * problem)
{
  int i;

  for (i = 0; i < problem->m; i++)
    {
      free (problem->a[i]);
    }

  free (problem->a);
  free (problem->b);

  for (i = 0; i < problem->m; i++)
    {
      free (problem->c[i]);
    }

  free (problem->c);
  free (problem->u);

  for (i = 0; i < problem->m; i++)
    {
      free (problem->x[i]);
    }

  free (problem->x);
}

Problem *
gap_problem_new (int m, int n)
{
  int i;
  Problem *problem;

  problem = malloc (sizeof (Problem));
  problem->a = malloc (m * sizeof (int *));

  for (i = 0; i < m; i++)
    {
      problem->a[i] = malloc (n * sizeof (int));
    }

  problem->b = malloc (m * sizeof (int));
  problem->c = malloc (m * sizeof (int *));

  for (i = 0; i < m; i++)
    {
      problem->c[i] = malloc (n * sizeof (int));
    }

  problem->m = m;
  problem->n = n;
  problem->u = calloc (m, sizeof (int));
  problem->x = malloc (m * sizeof (int *));

  for (i = 0; i < m; i++)
    {
      problem->x[i] = calloc (n, sizeof (int));
    }

  return problem;
}

void
gap_problem_print (Problem * problem)
{
  int i;
  int j;

  printf ("a:\n");

  for (i = 0; i < problem->m; i++)
    {
      for (j = 0; j < problem->n; j++)
	{
	  printf ("%d%s", problem->a[i][j], (j < (problem->n - 1) ? " " : "\n"));
	}
    }

  printf ("b:\n");

  for (i = 0; i < problem->m; i++)
    {
      printf ("%d%s", problem->b[i], (i < problem->m ? " " : ""));
    }

  printf ("\n");
  printf ("c:\n");

  for (i = 0; i < problem->m; i++)
    {
      for (j = 0; j < problem->n; j++)
	{
	  printf ("%d%s", problem->c[i][j], (j < (problem->n - 1) ? " " : "\n"));
	}
    }

  printf ("u:\n");

  for (i = 0; i < problem->m; i++)
    {
      printf ("%d%s", problem->u[i], (i < problem->m ? " " : ""));
    }

  printf ("\n");
  printf ("x:\n");

  for (i = 0; i < problem->m; i++)
    {
      for (j = 0; j < problem->n; j++)
	{
	  printf ("%d%s", problem->x[i][j], (j < (problem->n - 1) ? " " : "\n"));
	}
    }
}

ArrayList *
gap_problems_from_file (char *fname)
{
  FILE *fp;
  int i;
  int j;
  int m;
  int n;
  int n_problems;
  int p;
  Problem *problem;
  ArrayList *problems;

  fp = fopen (fname, "r");

  if (fp == NULL)
    {
      return NULL;
    }

  fscanf (fp, "%d", &n_problems);
  problems = array_list_new (n_problems);

  for (p = 0; p < n_problems; p++)
    {
      fscanf (fp, "%d", &m);
      fscanf (fp, "%d", &n);
      problem = gap_problem_new (m, n);

      for (i = 0; i < m; i++)
	{
	  for (j = 0; j < n; j++)
	    {
	      fscanf (fp, "%d", &(problem->c[i][j]));
	    }
	}

      for (i = 0; i < m; i++)
	{
	  for (j = 0; j < n; j++)
	    {
	      fscanf (fp, "%d", &(problem->a[i][j]));
	    }
	}

      for (i = 0; i < m; i++)
	{
	  fscanf (fp, "%d", &(problem->b[i]));
	}

      array_list_add (problems, problem);
    }

  fclose (fp);

  return problems;
}
