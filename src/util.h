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
 * @file util.h
 * @brief Utility functions and type definitions.
 */

#ifndef _UTIL_H
#define _UTIL_H

/**
 * @brief True value to be used in boolean conditions.
 */
#ifndef TRUE
#define TRUE 1
#endif

/**
 * @brief False value to be used in boolean conditions.
 */
#ifndef FALSE
#define FALSE 0
#endif

/**
 * @brief A destructor is a function used to free objects.
 *
 * @param element the element to free.
 */
typedef void (*Destructor) (void *element);

#endif