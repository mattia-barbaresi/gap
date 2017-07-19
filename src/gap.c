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

#include "array_stack.h"
#include "gap.h"
#include "util.h"

//calculate a lower bound for the problem with Lagrangian relaxiation.
int
calculateLowerBound ()
{
  clock_t t;

  printf ("Calculating lower bound....\n");
  t = clock ();

  //calcolo L(u) : rilassamento lagrangiano
  //il duale di L(u) definito come Max [ L(u)], u >= 0 -> LOWER BOUND
  //per risolvere il duale lagrangiano posso usare metodo del subgradiente

  t = clock () - t;

  printf ("Calculated lower bound in %f seconds.\n", ((double) t) / CLOCKS_PER_SEC);

  return 0;
}

//calculate a lower bound for the problem with Lagrangian relaxiation.
int
branchAndBound ()
{
  clock_t t;
  printf ("Executing branch-and-bound....\n");
  //init time
  t = clock ();

  //end time
  t = clock () - t;

  printf ("Branch-and-bound executed in %f seconds.\n", ((double) t) / CLOCKS_PER_SEC);
  return 0;
}

Problem **
readDataFromFile (str filePath)
{
  FILE *pFile = fopen (filePath, "r");

  if (pFile == NULL)
    return NULL;

  Problem **problems;
  int numProblems = 0;
  int n, m, q;

  fscanf (pFile, "%d", &numProblems);

  problems = malloc (numProblems * sizeof (Problem *));

  for (int p = 0; p < numProblems; ++p)
    {
      printf ("read problem %d...\n", p);
      problems[p] = (Problem *) malloc (sizeof (Problem));
      //read problem instance

      //read # containers
      fscanf (pFile, "%d", &m);
      //read # itemsw
      fscanf (pFile, "%d", &n);

      problems[p]->m = m;
      problems[p]->n = n;

      //init a
      problems[p]->a = malloc (m * sizeof (int *));
      problems[p]->a[0] = malloc (m * n * sizeof (int));
      for (q = 1; q < m; q++)
        problems[p]->a[q] = problems[p]->a[0] + q * n;

      //init b
      problems[p]->b = malloc (m * sizeof (int));

      //init c
      problems[p]->c = malloc (m * sizeof (int *));
      problems[p]->c[0] = malloc (m * n * sizeof (int));
      for (q = 1; q < m; q++)
        problems[p]->c[q] = problems[p]->c[0] + q * n;

      int i, j;

      //read c[m][n]
      //foreach container
      for (i = 0; i < m; ++i)
        for (j = 0; j < n; ++j)
          {
            //read cost of assign item j to container i
            fscanf (pFile, "%d", &(problems[p]->c[i][j]));
          }

      //read a[m][n]
      //foreach container
      for (i = 0; i < m; ++i)
        for (j = 0; j < n; ++j)
          //read space of item j in container i
          fscanf (pFile, "%d", &(problems[p]->a[i][j]));

      //read b
      //foreach container
      for (i = 0; i < m; ++i)
        //read total space of container i
        fscanf (pFile, "%d", &(problems[p]->b[i]));

    }

  fclose (pFile);
  printf ("Data readed from file %s.\n", filePath);

  return problems;
}
