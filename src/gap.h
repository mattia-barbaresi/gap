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

#include "problem.h"

int gap_branch_and_bound ();

int gap_lower_bound ();

//calculates the value of the lagrangian function
double gap_calcuate_lagrangian_function (Problem * problem);

//calculates initial solution for first relaxation
void gap_calculate_initial_lagrangian (Problem * problem);

//calculates the value of the objective function
int gap_calculate_solution (Problem * problem);

//checks if constraint are satisfied
int gap_are_constraints_satisfied (Problem * problem);

int gap_are_lagrangian_constraints_satisfied (Problem * problem);

int* gap_calculate_subgradient_stepsize_vector(Problem * problem);

int gap_calculate_subgradient_stepsize(int* y, int m);

int gap_subgradient(Problem * problem);

void gap_get_costs_with_relaxiation(Problem * problem);

#endif
