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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "array_list.h"
#include "util.h"

#define _ARRAY_LIST_GROW_FACTOR 2

extern inline size_t array_list_capacity (ArrayList * list);

extern inline void *array_list_get (ArrayList * list, unsigned int pos);

extern inline int array_list_is_empty (ArrayList * list);

extern inline size_t array_list_size (ArrayList * list);

/*
 * Enlarge the backing array of the specified array list.
 *
 * @param alist the array list.
 */
static void array_list_grow (ArrayList * list);

void
array_list_add (ArrayList * list, void *element)
{
  /* Before appending the element to the array list, we ensure it can contain them. If not we let the array grow. */
  if (list->capacity == list->size)
    {
      array_list_grow (list);
    }

  list->elements[list->size++] = element;
}

void
array_list_add_all (ArrayList * list, void **elements, size_t size)
{
  int i;

  for (i = 0; i < size; i++)
    {
      array_list_add (list, elements[i]);
    }
}

void
array_list_clear (ArrayList * list, Destructor destroy)
{
  int i;

  assert (destroy != NULL);

  for (i = 0; i < list->size; i++)
    {
      destroy (list->elements[i]);
    }

  list->size = 0;
}

void
array_list_ensure_capacity (ArrayList * list, size_t capacity)
{
  if (capacity > list->capacity)
    {
      list->elements = realloc (list->elements, capacity * sizeof (void *));
      list->capacity = capacity;
    }
}

void array_list_free (ArrayList * list, Destructor destroy)
{
  free (list->elements);
  free (list);
}

static void
array_list_grow (ArrayList * list)
{
  array_list_ensure_capacity (list, array_list_capacity (list) * _ARRAY_LIST_GROW_FACTOR);
}

ArrayList *
array_list_new (size_t capacity)
{
  ArrayList *list;

  list = malloc (sizeof (ArrayList));

  if (list == NULL)
    {
      return NULL;
    }

  list->elements = malloc (capacity * sizeof (void *));

  if (list->elements == NULL)
    {
      free (list);
      return NULL;
    }

  list->size = 0;
  list->capacity = capacity;

  return list;
}

void *
array_list_remove (ArrayList * list, unsigned int pos)
{
  void *element;

  assert (pos < list->size);
  element = list->elements[pos];
  /* All the elements from the right of the removed element to the end of the array are moved left. */
  memmove (list->elements + pos, list->elements + pos + 1, (list->size - pos) * sizeof (void *));
  list->size--;

  return element;
}

void
array_list_set (ArrayList * list, void *elem, unsigned int pos)
{
  assert (pos < list->size);
  list->elements[pos] = elem;
}

void
array_list_trim_to_size (ArrayList * list)
{
  int capacity;

  if (list->size < list->capacity)
    {
      capacity = list->size > 0 ? list->size : 1;
      list->elements = realloc (list->elements, capacity);
      list->capacity = capacity;
    }
}
