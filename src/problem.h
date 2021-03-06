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

#ifndef _PROBLEM_H
#define _PROBLEM_H

#include "array_list.h"

typedef struct
{
  int **a;
  int **c;
  double **costs;
  int **x;
  int *b;
  float *u;
  int m;
  int n;
  double lb;
} Problem;

void gap_problem_free (Problem * problem);

Problem *gap_problem_new (int m, int n);

void gap_problem_print (Problem * problem);

ArrayList *gap_problems_from_file (char *fname);

#endif
