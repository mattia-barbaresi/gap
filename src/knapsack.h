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

/**
 * @file knapsack.h
 * @brief 
 */

#include <assert.h>

typedef struct
{
  int *c;
  int *a;
  int b;
  int n;
} KnapsackInstance;

typedef struct
{
  int **f;
  int m;
  int n;
} KnapsackState;

Knapsack * knapsack_create(int nobjects);

void knapsack_free(Knapsack * instance);

inline int
knapsack_get_capacity (KnapsackInstance * instance)
{
  return instance->b;
}

inline int
knapsack_get_cost (KnapsackInstance * instance, int i)
{
  return instance->c[i];
}

inline int
knapsack_get_objects (KnapsackInstance * instance)
{
  return instance->n;
}

inline int
knapsack_get_weight (KnapsackInstance * instance, int i)
{
  return instance->a[i];
}

void knapsack_calc (KnapsackInstance * instance, KnapsackStateSpace * space);

KnapsackStateSpace * knapsack_state_create();

void knapsack_state_free(KnapsackStateSpace * space);

