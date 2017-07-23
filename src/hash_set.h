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
 * @file set.h
 * @brief A set ADT.
 */

#ifndef _HASH_SET_H
#define _HASH_SET_H

#include <stdlib.h>

#include "util.h"

#define SET_DEFAULT_CAPACITY 16
#define SET_DEFAULT_LOAD_FACTOR 0.75f

typedef struct hash_set_entry
{
  void *element;
  struct hash_set_entry *next;
} HashSetEntry;

typedef struct
{
  size_t capacity;
  Comparator compare;
  HashSetEntry **entries;
  HashFunction hashf;
  float load_factor;
  size_t size;
  size_t threshold;
} HashSet;

int hash_set_add (HashSet * set, void *element);

inline size_t
hash_set_capacity (HashSet * set)
{
  return set->capacity;
}

void hash_set_clear (HashSet * set, Destructor destroy);

int hash_set_contains (HashSet * set, void *element);

void hash_set_ensure_capacity (HashSet * set, size_t capacity);

void hash_set_free (HashSet * set);

HashSet *hash_set_new (size_t capacity, float load_factor, HashFunction hashf, Comparator compare);

void hash_set_remove (HashSet * set, void *element);

inline size_t
hash_set_size (HashSet * set)
{
  return set->size;
}

#endif
