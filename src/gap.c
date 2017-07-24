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

  return result;
}

int **
gap_calculate_initial (Problem * problem)
{
  int i;
  int j;
  int minIndex;
  int minValue;
  int q;
  int **res;

  res = malloc (problem->m * sizeof (int *));
  res[0] = calloc (problem->n * problem->m, sizeof (int));

  for (q = 1; q < problem->m; q++)
    res[q] = res[0] + q * problem->n;

  //set to 1 variables that have min cost
  for (i = 0; i < problem->m; i++)
    {
      minIndex = 0;
      minValue = problem->c[i][0];

      for (j = 0; j < problem->n; j++)
	{
	  if (problem->c[i][j] < minValue)
	    {
	      minIndex = j;
	      minValue = problem->c[i][j];
	    }
	}

      res[i][minIndex] = 1;
    }

  for (i = 0; i < problem->m; i++)
    {
      printf ("\n");

      for (j = 0; j < problem->n; j++)
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
  int k;
  int m;
  int n;
  int n_problems;
  Problem *problem;
  ArrayList *problems = NULL;

  /* *INDENT-OFF* */
  if ((fp = fopen (fname, "r")) == NULL) goto io_exception;
  if (fscanf (fp, "%d", &n_problems) == EOF) goto io_exception;
  if ((problems = array_list_new (n_problems)) == NULL) goto memory_exception;

  for (k = 0; k < n_problems; k++)
    {
      if (fscanf (fp, "%d", &m) == EOF) goto io_exception;
      if (fscanf (fp, "%d", &n) == EOF) goto io_exception;
      if ((problem = gap_problem_new (m, n)) == NULL) goto memory_exception;

      for (i = 0; i < m; i++)
	{
	  for (j = 0; j < n; j++)
	    {
	      if (fscanf (fp, "%d", &(problem->c[i][j])) == EOF) goto io_exception;
	    }
	}

      for (i = 0; i < m; i++)
	{
	  for (j = 0; j < n; j++)
	    {
	      if (fscanf (fp, "%d", &(problem->a[i][j])) == EOF) goto io_exception;
	    }
	}

      for (i = 0; i < m; i++)
	{
	  if (fscanf (fp, "%d", &(problem->b[i])) == EOF) goto io_exception;
	}

      if (!array_list_add (problems, problem)) goto memory_exception;
    }

  if (fclose (fp) == EOF) goto io_exception;
  /* *INDENT-ON* */

  return problems;

memory_exception:
io_exception:
  if (fp != NULL)
    {
      fclose (fp);
    }

  if (problems != NULL)
    {
      array_list_clear (problems, (Destructor) gap_problem_free);
      array_list_free (problems);
    }

  return NULL;
}
