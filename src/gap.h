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

#ifndef _GAP_H
#define _GAP_H

#include <stdio.h>
#include <stdlib.h>

typedef char *str;

typedef struct
{
  int **a;
  int **c;
  int **x;
  int *b;
  int *u;
  int n, m;
} Problem;

//calculates the value of the lagrangian function
int gap_calcuate_lagrangian_function (Problem problem);

int gap_calculate_lower_bound ();

int gap_branch_and_bound ();

//calculates the value of the objective function
int gap_calculate_solution (Problem problem);

//reads data from file and inits structures
Problem **gap_read_data_from_file (str filePath, int *numP);

//calculates initial solution for first relaxation
int** gap_calculate_initial (Problem problem);

#endif
