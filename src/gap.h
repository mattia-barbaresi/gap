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
  int *b;
  int **c;
  int n, m;
} Problem;

int calculateLowerBound ();

int branchAndBound ();

Problem **readDataFromFile (str filePath);

#endif
