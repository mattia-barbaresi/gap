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
#include <stdio.h>
#include <stdlib.h>

#include "array_stack.h"
#include "util.h"

#define _ARRAY_STACK_GROW_FACTOR 2

extern inline size_t array_stack_capacity (ArrayStack * stack);

extern inline int array_stack_is_empty (ArrayStack * stack);

extern inline size_t array_stack_size (ArrayStack * stack);

/*
 * Enlarge the backing array of the specified array stack.
 *
 * @param stack the array stack.
 */
static void array_stack_grow (ArrayStack * stack);

void
array_stack_clear (ArrayStack * stack, Destructor destroy)
{
  int i;

  assert (destroy != NULL);

  for (i = 0; i < stack->size; i++)
    {
      destroy (stack->elements[i]);
    }

  stack->size = 0;
}

void
array_stack_ensure_capacity (ArrayStack * stack, size_t capacity)
{
  if (capacity > stack->capacity)
    {
      stack->elements = realloc (stack->elements, capacity * sizeof (void *));
      stack->capacity = capacity;
    }
}

void
array_stack_free (ArrayStack * stack)
{
  free (stack->elements);
  free (stack);
}

static void
array_stack_grow (ArrayStack * stack)
{
  array_stack_ensure_capacity (stack, stack->capacity * _ARRAY_STACK_GROW_FACTOR);
}

ArrayStack *
array_stack_new (size_t capacity)
{
  ArrayStack *stack;

  assert (capacity > 0);

  stack = malloc (sizeof (ArrayStack));
  stack->size = 0;
  stack->capacity = capacity;

  if (stack == NULL)
    {
      return NULL;
    }

  stack->elements = malloc (capacity * sizeof (void *));

  if (stack->elements == NULL)
    {
      free (stack);
      return NULL;
    }

  return stack;
}

void *
array_stack_pop (ArrayStack * stack)
{
  assert (stack->size > 0);
  return stack->elements[--stack->size];
}

void
array_stack_push (ArrayStack * stack, void *element)
{
  /* Before appending the element to the stack, we ensure it can contain them. If not we let the array grow. */
  if (stack->capacity == stack->size)
    {
      array_stack_grow (stack);
    }

  stack->elements[stack->size++] = element;
}
