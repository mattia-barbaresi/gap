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
gap_calculate_lower_bound ()
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
gap_branch_and_bound ()
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
gap_read_data_from_file (str filePath, int* numProblems)
{
  FILE *pFile = fopen (filePath, "r");

  if (pFile == NULL)
    return NULL;

  Problem **problems;
  int n, m, q;

  fscanf (pFile, "%d", numProblems);

  problems = malloc (*numProblems * sizeof (Problem *));

  for (int p = 0; p < *numProblems; ++p)
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

      //init b
      problems[p]->u = calloc (sizeof (int), m);

      //init c
      problems[p]->c = malloc (m * sizeof (int *));
      problems[p]->c[0] = malloc (m * n * sizeof (int));
      for (q = 1; q < m; q++)
        problems[p]->c[q] = problems[p]->c[0] + q * n;

      //init x
      problems[p]->x = malloc (m * sizeof (int *));
      problems[p]->x[0] = calloc (sizeof (int), m * n);
      for (q = 1; q < m; q++)
        problems[p]->x[q] = problems[p]->x[0] + q * n;

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

//calculates total cost
int gap_calculate_solution(Problem problem)
{

  int cost=0;

  for (int i = 0; i < problem.m; ++i)
  {
    for (int j = 0; j < problem.n; ++j)
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
  int result =  gap_calculate_solution(problem);

  int* u = calloc (sizeof(int), m);
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

int**
gap_calculate_initial (Problem problem)
{
  int** res = malloc (problem.m * sizeof (int *));
  int q;
  res[0] = calloc(sizeof(int), problem.n * problem.m);
  for (q = 1; q < problem.m; q++)
    res[q] = res[0] + q * problem.n;

  int minIndex;
  int minValue;

  //set to 1 variables that have min cost
  for (int i = 0; i < problem.m; ++i)
  {
    minIndex = 0;
    minValue = problem.c[i][0];

    for (int j = 0; j< problem.n; ++j)
    {
      if(problem.c[i][j] < minValue)
      {
        minIndex = j;
        minValue = problem.c[i][j];
      }
    }

    res[i][minIndex] = 1;
  }

  for (int i = 0; i < problem.m; ++i)
  {
    printf("\n");
    for (int j = 0; j < problem.n; ++j)
    {
      printf("%d ", res[i][j]);
    }
  }
  return res;
}