#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "array_list.h"
#include "array_stack.h"
#include "subgradient.h"
#include "problem.h"
#include "util.h"
#include "gap.h"

// a: calculates cost * x + u
double
gap_calcuate_lagrangian_function_a (Problem * problem)
{
  double cost = 0;
  int i;
  int j;

  for (j = 0; j < problem->n; j++)
  {
    for (i = 0; i < problem->m; i++)
    {
      cost += problem->costs[i][j] * problem->x[i][j];
    }
    cost += problem->u[j];
  }

  return cost;
}

// b: calculates cost * x + u
double
gap_calcuate_lagrangian_function_b (Problem * problem)
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

  return cost;
}

// a: calculates optimal for L(u)
// dinamica per gli m knapsack
// ricursione forward
void
gap_calculate_lagrangian_a (Problem * problem)
{
  int k,val;

  // init f(k,q)
  int** f = malloc ((problem->n + 1) * sizeof (int *)); //k

  //ciclo sui contenitori
  for (int knap = 0; knap < problem->m; ++knap)
  {
    // allocazione dinamica per f(k,q) dove q = 1,2,..,b
    for (int ii = 0; ii <= problem->n; ii++)
    {
      f[ii] = malloc ((problem->b[knap]+1) * sizeof (int)); //q
    }

    // init f(0,q)
    f[0][0] = 0;
    for (int z = 1; z <= problem->b[knap]; ++z)
    {
      f[0][z] = -9999; // -inf
    }

    k = 0;

    // ciclo su k
    while(k != problem->n)
    {
      // init f(k+1,q)
      for (int z = 0; z <= problem->b[knap]; ++z)
      {
        f[k+1][z] = -9999; // -inf
      }

      for (int q = 0; q <= problem->b[knap]; ++q)
      {
        if(f[k][q] >= 0)
        {
          f[k+1][q] = f[k+1][q] > f[k][q] ? f[k+1][q] : f[k][q];

          val = q + problem->a[knap][k];

          if(val <= problem->b[knap])
          {
            f[k+1][val] = f[k+1][val] > f[k][q] + problem->c[knap][k] ? f[k+1][val] : f[k][q] + problem->c[knap][k];
          }
        }
      }
      k++;
    }

    int b = problem->b[knap];

    // calculate solution
    for (k = problem->n; k > 0; --k)
    {
      if( f[k][b] > f[k-1][b] )
      {
        problem->x[knap][k-1] = 1;
        b -= problem->a[knap][k-1];
      }
      else
      {
        problem->x[knap][k-1] = 0;
      }
    }
  }
}

// b: calculates optimal for L(u)
// soluzione per gli n item
// minimum
void
gap_calculate_lagrangian_b (Problem * problem)
{
  int i;
  int j;
  int minIndex;
  double minValue;

  // set to 1 variables that have min cost
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
}

// a: calculates costs = c - u
void
gap_get_costs_with_relaxiation_a(Problem * problem)
{
  for (int j = 0; j < problem->n; ++j)
  {
    for (int i = 0; i < problem->m; ++i)
    {
      problem->costs[i][j] = problem->c[i][j] - problem->u[j];
    }
  }
}

// b: calculates costs = c - (u * a)
void
gap_get_costs_with_relaxiation_b (Problem * problem)
{
  for (int i = 0; i < problem->m; ++i)
  {
    for (int j = 0; j < problem->n; ++j)
    {
      problem->costs[i][j] = problem->c[i][j] - ( problem->u[i] * problem->a[i][j] );
    }
  }
}

// a: checks if relaxed constraints are satisfied
int
gap_are_constraints_satisfied_a (Problem * problem)
{
   int i,j,sum;

    for (j = 0; j < problem->n; j++)
    {
      sum = 0;
      for (i = 0; i < problem->m; i++)
      {
        sum += problem->x[i][j];
      }
      if(sum != 1)
      {
        // constraints not satisfied
        // printf("constraints not satisfied: %d\n", i);
        return 0;
      }
    }
    // constraints satisfied
    return 1;
}

// b: checks if relaxed constraints are satisfied
int
gap_are_constraints_satisfied_b (Problem * problem)
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
        // constraints not satisfied
        // printf("constraints not satisfied: %d\n", i);
        return 0;
      }
    }
    // constraints satisfied
    return 1;
}

// a: checks if lagrangian constraints are satisfied
int
gap_are_lagrangian_constraints_satisfied_a (Problem * problem)
{
   int i,j,sum;

    for (j = 0; j < problem->n; j++)
    {
      sum = 0;
      for (i = 0; i < problem->m; i++)
      {
        sum += problem->x[i][j];
      }
      if( problem->u[j] * (sum - 1) != 0.0)
      {
        // lagrangian constraints not satisfied
        // printf("lagrangian constraints not satisfied: %d\n", i);
        return 0;
      }
    }
    // lagrangian constraints satisfied
    return 1;
}

// b: checks if lagrangian constraints are satisfied
int
gap_are_lagrangian_constraints_satisfied_b (Problem * problem)
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
        // lagrangian constraints not satisfied
        // printf("lagrangian constraints not satisfied: %d\n", i);
        return 0;
      }
    }
    // lagrangian constraints satisfied
    return 1;
}

// a: calculates vector for stepsize
int*
gap_calculate_subgradient_stepsize_vector_a (Problem * problem)
{
  int sum;
  int* y = calloc (problem->n, sizeof (int));

  for (int j = 0; j < problem->n; j++)
  {
    sum = 0;
    for (int i = 0; i < problem->m; i++)
      {
        sum += problem->a[i][j] * problem->x[i][j];
      }
    y[j] = sum - problem->b[j];
  }
  return y;
}

// b: calculates vector for stepsize
int*
gap_calculate_subgradient_stepsize_vector_b (Problem * problem)
{
  int sum;
  int* y = calloc (problem->n, sizeof (int));

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

//calculates step size
int
gap_calculate_subgradient_stepsize(int* y, int m)
{
  int sum = 0;

  for (int i = 0; i < m; i++)
    sum += y[i] * y[i];
  return sum;
}

// a: checks optimality (all constraints satisfied)
int
gap_is_solution_optimal_a (Problem * problem)
{
  if(gap_are_constraints_satisfied_a(problem) == 1 && gap_are_lagrangian_constraints_satisfied_a(problem) == 1)
    return 0;
  return 1;
}

// b: checks optimality (all constraints satisfied)
int
gap_is_solution_optimal_b (Problem * problem)
{
  if(gap_are_constraints_satisfied_b(problem) == 1 && gap_are_lagrangian_constraints_satisfied_b(problem) == 1)
    return 0;
  return 1;
}

// subgradient
//----------------------------------------------------------
//
// NOTA:
//  _a: functions for relaxing constraints on the number of items (1..n)
//  _b: functions for relaxing constraints on the capacity of knapsacks (1..m)
//
//----------------------------------------------------------
int
gap_subgradient (Problem * problem, char relaxType)
{
  int iter = 0;
  int maxIter = 150;
  float alpha = 1;
  int delta = 20;
  int trials = 0;
  int result = 0;
  // invert_for_max_problem(problem);
 
  double lu;
  int* y;
  double step_size;
  float res;

  // UB
  // TODO: calcolarne uno in qualche modo
  // ----------------------------------------------------------
  // for gap of type c, d, e ...and size [5,10,20] X [100,200]:
  // use double lz = problem->lb; 
  // ----------------------------------------------------------
  double lz = 2;

  //init lb
  problem->lb = -999999; 

  int** xOpt = malloc (problem->m * sizeof (int *));

  for (int i = 0; i < problem->m; i++)
    xOpt[i] = calloc (problem->n, sizeof (int));

  while(iter <= maxIter)
  {
    // init costs for relaxing constraint:
    if(relaxType == 'a'){
      problem->u = calloc (problem->n, sizeof (float));
      gap_get_costs_with_relaxiation_a(problem);
    }
    else if(relaxType == 'b'){
      problem->u = calloc (problem->m, sizeof (float));
      gap_get_costs_with_relaxiation_b(problem);
    }

    // calculate optimal solution for L(u):
    if(relaxType == 'a')
      gap_calculate_lagrangian_a(problem);
    else if(relaxType == 'b')
      gap_calculate_lagrangian_b(problem);

    // cost of L(u):
    if(relaxType == 'a')
      lu = gap_calcuate_lagrangian_function_a(problem);
    else if(relaxType == 'b')
      lu = gap_calcuate_lagrangian_function_b(problem);

    if(lu > problem->lb)
    {
      printf("lu: %f\n",lu );
      problem->lb = lu;
      trials = 0;
      copyMatrix(problem->x, xOpt, problem->m, problem->n);

      // solution x is optimal -> STOP:
      if(relaxType == 'a')
        result = gap_is_solution_optimal_a(problem);
      else if(relaxType == 'b')
        result = gap_is_solution_optimal_b(problem);

      if(result == 0)
      {
        printf("Exit subgradient function...optimal solution found! (iter: %d)\n", iter);
        return 0;
      }
    }

    // step size vector:
    if(relaxType == 'a')
      y = gap_calculate_subgradient_stepsize_vector_a(problem);
    else if(relaxType == 'b')
      y = gap_calculate_subgradient_stepsize_vector_b(problem);

    // step size:
    if(relaxType == 'a')
      step_size = (double)gap_calculate_subgradient_stepsize(y, problem->n);
    else if(relaxType == 'b')
      step_size = (double)gap_calculate_subgradient_stepsize(y, problem->m);

    //update u:

    if(relaxType == 'a'){
      for (int j = 0; j < problem->n; ++j)
      {
        res = problem->u[j] - alpha * ((lz - lu)/step_size) * y[j];
        problem->u[j] = res;
      }
    }
    else if(relaxType == 'b'){
      for (int i = 0; i < problem->m; ++i)
      {
        res = problem->u[i] - alpha * (/*(lz - lu)*/(-0.3*lu)/step_size) * y[i];
        problem->u[i] = res < 0.0 ? res : 0.0; //min
      }
    }

    iter++;
    trials++;

    if(trials == delta){
      alpha = alpha * 0.5;
      trials = 0;
    }
  }

  copyMatrix(xOpt, problem->x, problem->m, problem->n);
  return 1;
}