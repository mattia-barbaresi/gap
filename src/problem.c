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

#include "array_list.h"
#include "problem.h"
#include "util.h"

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
      free (problem->costs[i]);
    }

  free (problem->c);
  free (problem->costs);
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
  problem->costs = malloc (m * sizeof (double *));

  for (i = 0; i < m; i++)
    {
      problem->c[i] = malloc (n * sizeof (int));
      problem->costs[i] = malloc (n * sizeof (double));
    }

  problem->m = m;
  problem->n = n;
  problem->u = calloc (m, sizeof (float));
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
      printf ("%f%s", problem->u[i], (i < problem->m ? " " : ""));
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

  printf ("\n\n");
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

  if((fname[11]=='c' || fname[11]=='d' || fname[11]=='e') && fname[12]=='/'){
    n_problems=1;
  }
  else
  {
    if (fscanf (fp, "%d", &n_problems) == EOF) goto io_exception;
  }

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

  if((fname[11]=='c' || fname[11]=='d' || fname[11]=='e') && fname[12]=='/'){
    if (fscanf (fp, "%d", &(problem->lb)) == EOF) goto io_exception;
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
