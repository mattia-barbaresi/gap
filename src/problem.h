#include "array_list.h"

#ifndef _PROBLEM_H
#define _PROBLEM_H

typedef struct
{
  int **a;
  int **c;
  int **x;
  int *b;
  int *u;
  int m;
  int n;
} Problem;

//reads data from file and inits structures
ArrayList *gap_problems_from_file (char *fname);

void gap_problem_free (Problem * problem);

Problem *gap_problem_new (int m, int n);

void gap_problem_print (Problem * problem);

#endif