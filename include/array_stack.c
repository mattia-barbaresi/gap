#include <stdlib.h>

#include "array_stack.h"
#include "util.h"

#define ARRAY_STACK_DEFAULT_CAPACITY 16
#define _ARRAY_STACK_GROW_FACTOR 2

/*
 * Enlarge the backing array of the specified array stack.
 *
 * @param stack the array stack.
 */
static void
array_stack_grow (ArrayStack *stack);

size_t
array_stack_capacity (ArrayStack *stack)
{
  return stack->capacity;
}

void
array_stack_clear (ArrayStack *stack, Destructor destroy)
{
  int i;

  for (i = 0; i < stack->size; i++)
    {
      destroy (stack->elements[i]);
    }

  alist->size = 0;
}

void
array_stack_ensure_capacity (ArrayStack *stack, size_t capacity)
{
  if (capacity > stack->capacity)
    {
      stack->elements = realloc (stack->elements, capacity * sizeof (void *));
      stack->capacity = capacity;
    }
}

void
array_stack_free (ArrayStack *stack, Destructor destroy)
{
  array_stack_clear (stack, destroy);
  free (stack->elems);
  free (stack);
}

static void
array_stack_grow (ArrayStack *stack)
{
  array_stack_ensure_capacity (stack, array_stack_capacity (stack) * ARRAY_STACK_GROW_FACTOR);
}

int
array_stack_is_empty (ArrayStack *stack)
{
  return stack->size == 0;
}

ArrayStack *
alist_new (size_t capacity)
{
  ArrayStack *stack;

  stack = malloc (sizeof (ArrayStack))
    stack->elements = malloc (capacity * sizeof (void *));
  stack->size = 0;
  stack->capacity = capacity;

  return stack;
}

void *
array_stack_pop (ArrayStack *stack)
{
  return stack->elements[stack->size--];
}

void
array_stack_push (ArrayStack *stack, void *element)
{
  /* Before appending the element to the stack, we ensure it can contain them. If not we let the array grow. */
  if (stack->capacity == stack->size)
    {
      array_stack_grow (stack);
    }

  stack->elements[stack->size++] = elem;
}

size_t
array_stack_size (ArrayStack *stack)
{
  return stack->size;
}
