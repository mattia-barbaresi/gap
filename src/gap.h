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

//calculates the value of the objective function
int gap_calculate_solution (Problem * problem);

//run subgradient with constraints on item relaxed
int gap_subgradient_a(Problem * problem);

//run subgradient with constraints on capacities relaxed
int gap_subgradient_b(Problem * problem);

#endif
