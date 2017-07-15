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
