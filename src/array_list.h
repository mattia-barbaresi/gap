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
 * @file array_list.h
 * @brief An array list is a list ADT backed by an auto-resizing array.
 *
 * Each array list instance has a capacity. The capacity is the size of the array used to store the elements in the
 * list. It is always at least as large as the list size. As elements are added to an array list, its capacity grows
 * automatically.
 *
 * An application can increase the capacity of an array list instance before adding a large number of elements using the
 * alist_ensure_capacity() operation. This may reduce the amount of incremental reallocation.
 */

#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#include <assert.h>
#include <stdlib.h>

#include "util.h"

#define ARRAY_LIST_DEFAULT_CAPACITY 16

/**
 * ArrayList ADT. All the fields are private. You should access them with the proper function.
 */
typedef struct
{
  void **elements;
  size_t size;
  size_t capacity;
} ArrayList;

/**
 * @brief Append the specified element to the end of the array list.
 *
 * @param list the array list.
 * @param elem the element to append to the array list.
 */
void array_list_add (ArrayList * list, void *elem);

/**
 * @brief Append all the elements of the specified array to the end of the array list.
 *
 * @param list the array list.
 * @param elems the array of elements to append to the array list.
 * @param size the size of the array.
 */
void array_list_add_all (ArrayList * list, void **elems, size_t size);

/**
 * @brief Return the capacity of the specified array list.
 *
 * Each array list instance has a capacity. The capacity is the size of the array used to store the elements in the
 * list. It is always at least as large as the list size. As elements are added to an array list, its capacity grows
 * automatically.
 *
 * @param list the array list.
 * @return the capacity of the specified array list.
 */
inline size_t
array_list_capacity (ArrayList * list)
{
  return list->capacity;
}

/**
 * @brief Remove and return all the elements of the list.
 *
 * The client is responsible to free the elements as well as the returned array.
 *
 * @param list the array list.
 */
void array_list_clear (ArrayList * list, Destructor destroy);

/**
 * @brief Increase the capacity of an array list instance, if necessary, to ensure that it can hold at least the number
 * of elements specified.
 *
 * An application can increase the capacity of an array list instance before adding a large number of elements. This may
 * reduce the amount of incremental reallocation.
 *
 * @param list the array list.
 * @param capacity the desired minimum capacity.
 */
void array_list_ensure_capacity (ArrayList * list, size_t capacity);

/**
 * @brief Free the specified array list instance.
 *
 * @param list the array list.
 */
void array_list_free (ArrayList * list);

/**
 * @brief Return the element at the specified position in the array list.
 *
 * @param list the array list.
 * @param pos the position of the element.
 * @return the element at the specified position in the array list.
 */
inline void *
array_list_get (ArrayList * list, unsigned int pos)
{
  assert (pos < list->size);
  return list->elements[pos];
}

/**
 * @brief Returns TRUE if the array list is empty (i.e. does not contain any element).
 *
 * @param list the array list.
 * @return TRUE if the array list is empty, FALSE otherwise.
 */
inline int
array_list_is_empty (ArrayList * list)
{
  return list->size == 0;
}

/**
 * @brief Create a new array list with default capacity.
 *
 * @return The new array list.
 */
ArrayList *array_list_new (size_t capacity);

/**
 * @brief Remove the element at the specified position in the list and shift the subsequent elements to the left.
 *
 * The client is responsible to free the elements. The capacity of the array list is left unalterated.
 *
 * @param list the array list.
 * @param pos the index of the element to be removed.
 */
void *array_list_remove (ArrayList * list, unsigned int pos);

/**
 * @brief Replace the element at the specified position in the list.
 *
 * This operation differs from array_list_set_element_at() in the fact that if the specified position is greater than the
 * size of the array list an error will be thrown.
 *
 * @param list the array list.
 * @param elem the element to be stored at the specified position.
 * @param pos index of the element to replace.
 */
void array_list_set (ArrayList * list, void *elem, unsigned int pos);

/**
 * @brief Return the number of elements of the specified array list.
 *
 * Each array list instance has a size. The size is the number of the elements currently in the list.
 *
 * @param list the array list.
 * @return the number of elements in the specified array list.
 */
inline size_t
array_list_size (ArrayList * list)
{
  return list->size;
}

/**
 * @brief Trim the capacity of the array list to its current size.
 *
 * An application can use this operation to minimize the storage of an array list instance. If the array list is empty
 * the capacity is set to 1.
 *
 * @param list the array list.
 */
void array_list_trim_to_size (ArrayList * list);

#endif
