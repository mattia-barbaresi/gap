/**
 * @file array_stack.h
 * @brief An array stack is a stack ADT backed by an auto-resizing array.
 *
 * Each array stack instance has a capacity. The capacity is the size of the array used to store the elements in the
 * stack. It is always at least as large as the stack size. As elements are added to an array stack, its capacity grows
 * automatically.
 *
 * An application can increase the capacity of an array stack instance before adding a large number of elements using the
 * array_stack_ensure_capacity() operation. This may reduce the amount of incremental reallocation.
 */

#ifndef _ARRAY_STACK_H
#define _ARRAY_STACK_H

#include <stdlib.h>

#include "util.h"

#define ARRAY_STACK_DEFAULT_CAPACITY 16

/**
 * ArrayStack ADT. All the fields are private. You should access them with the proper function.
 */
typedef struct {
  void **elements;
  size_t size;
  size_t capacity;
} ArrayStack;

/**
 * @brief Return the capacity of the specified array stack.
 *
 * Each array stack instance has a capacity. The capacity is the size of the array used to store the elements in the
 * stack. It is always at least as large as the stack size. As elements are added to an array stack, its capacity grows
 * automatically.
 *
 * @param stack the array stack.
 * @return the capacity of the specified array stack.
 */
size_t
array_stack_capacity (ArrayStack *stack);

/**
 * @brief Remove all the elements in the stack.
 *
 * @param alist the array list.
 * @param destroy destroyer function.
 */
void
array_stack_clear (ArrayStack *stack, Destructor destroy);

/**
 * @brief Increase the capacity of an array stack instance, if necessary, to ensure that it can hold at least the number
 * of elements specified.
 *
 * An application can increase the capacity of an array stack instance before adding a large number of elements. This may
 * reduce the amount of incremental reallocation.
 *
 * @param stack the array stack.
 * @param capacity the desired minimum capacity.
 */
void
array_stack_ensure_capacity (ArrayStack *stack, size_t capacity);

/**
 * @brief Free the specified array stack instance.
 *
 * @param stack the array stack.
 * @param destroy the destroyer function.
 */
void
array_stack_free (ArrayStack *stack, Destructor destroy);

/**
 * @brief Returns TRUE if the array stack is empty (i.e. does not contain any element).
 *
 * @param stack the array stack.
 * @return TRUE if the array stack is empty, FALSE otherwise.
 */
int
array_stack_is_empty (ArrayStack *stack);

/**
 * @brief Create a new array stack with the specified capacity.
 *
 * @param capacity The capacity of the new array stack.
 * @return The new array stack.
 */
ArrayStack *
array_stack_new (size_t capacity);

/**
 * Pop the top element of the stack.
 * 
 * @param stack the array stack.
 * @return the element popped from the stack.
 */
void *
array_stack_pop (ArrayStack *stack);

/**
 * @brief Push the specified element into the stack.
 *
 * @param stack the array stack.
 * @param element the element to push into the stack.
 */
void
array_stack_push (ArrayStack *stack, void *element);

/**
 * @brief Return the number of elements of the specified array stack.
 *
 * Each array stack instance has a size. The size is the number of the elements currently in the stack.
 *
 * @param stack the array stack.
 * @return the number of elements in the specified array stack.
 */
size_t
array_stack_size (ArrayStack *stack);

#endif
