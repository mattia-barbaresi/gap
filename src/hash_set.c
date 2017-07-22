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

#include "hash_set.h"
#include "util.h"

#define _HASH_SET_GROW_FACTOR 2

extern inline size_t hash_set_capacity (HashSet *set);

static void hash_set_entry_free (HashSetEntry *entry);

static HashSetEntry *hash_set_entry_new (void *element);

static void hash_set_grow (HashSet *set);

static int hash_set_guard (int hash);

static size_t hash_set_index (HashSet *set, void *element);

static inline void hash_set_relocate_entries (HashSet *set, HashSetEntry **old_entries, size_t old_capacity);

extern inline size_t hash_set_size (HashSet *set);

static inline size_t hash_set_threshold (size_t capacity, float load_factor);

int
hash_set_add (HashSet *set, void *element)
{
  Comparator compare;
  int comparison;
  HashSetEntry *curr;
  HashSetEntry *entry;
  int index;
  HashSetEntry *prev;

  if (set->size == set->threshold)
    {
      hash_set_grow (set);
    }

  index = hash_set_index (set, element);
  curr = set->entries[index];

  if (curr == NULL)
    {
      entry = hash_set_entry_new (element);
      entry->next = NULL;
      set->entries[index] = entry;

      return TRUE;
    }

  compare = set->compare;
  prev = NULL;

  while ((comparison = compare (element, curr->element)) < 0)
    {
      prev = curr;
      curr = curr->next;
    }

  if (comparison == 0)
    {
      return FALSE;
    }

  entry = hash_set_entry_new (element);
  entry->next = curr;

  if (prev == NULL)
    {
      set->entries[index] = entry;
    }
  else
    {
      prev->next = entry;
    }

  set->size++;

  return TRUE;
}

void
hash_set_clear (HashSet *set, Destructor destroy)
{
  HashSetEntry *curr;
  int i;
  HashSetEntry *prev;

  for (i = 0; i < set->capacity; i++)
    {
      curr = set->entries[i];

      while (curr != NULL)
        {
          prev = curr;
          curr = curr->next;

          destroy (prev->element);
          hash_set_entry_free (prev);
        }
    }

  set->size = 0;
}

int
hash_set_contains (HashSet *set, void *element)
{
  Comparator compare;
  int comparison;
  HashSetEntry *curr;
  int index;

  compare = set->compare;
  index = hash_set_index (set, element);
  curr = set->entries[index];

  while (curr != NULL && (comparison = compare (element, curr->element)) < 0)
    {
      curr = curr->next;
    }

  if (comparison == 0)
    {
      return TRUE;
    }

  return FALSE;
}

void hash_set_ensure_capacity (HashSet *set, size_t capacity)
{
  size_t old_capacity;
  HashSetEntry **old_entries;

  old_capacity = set->capacity;
  old_entries = set->entries;

  set->capacity = capacity;
  set->entries = calloc (set->capacity, sizeof (HashSetEntry *));
  set->threshold = hash_set_threshold (set->capacity, set->load_factor);

  hash_set_relocate_entries (set, old_entries, old_capacity);

  free (old_entries);
}

static void
hash_set_entry_free (HashSetEntry *entry)
{
  free (entry);
}

static HashSetEntry *
hash_set_entry_new (void *element)
{
  HashSetEntry *entry = malloc (sizeof (HashSetEntry));
  entry->element = element;
  return entry;
}

void
hash_set_free (HashSet *set)
{
  free (set->entries);
  free (set);
}

static void
hash_set_grow (HashSet *set)
{
  hash_set_ensure_capacity (set, set->capacity * _HASH_SET_GROW_FACTOR);
}

static int
hash_set_guard (int hash)
{
  hash ^= (hash >> 20) ^ (hash >> 12);
  return hash ^ (hash >> 7) ^ (hash >> 4);
}

static size_t
hash_set_index (HashSet *set, void *element)
{
  int hash = hash_set_guard (set->hashf (element));
  return hash & (set->capacity - 1);
}

HashSet *
hash_set_new (size_t capacity, float load_factor, HashFunction hashf, Comparator compare)
{
  HashSet *set;

  assert (capacity > 0);
  assert (load_factor > 0);

  set = malloc (sizeof (HashSet));

  if (set == NULL)
    {
      return NULL;
    }

  set->capacity = 1;

  // Find the first power of 2 that is greater or equal the initial wanted capacity.
  while (set->capacity < capacity)
    set->capacity <<= 1;

  set->compare = compare;
  set->entries = calloc (capacity, sizeof (HashSetEntry *));

  if (set->entries == NULL)
    {
      free (set);
      return NULL;
    }

  set->hashf = hashf;
  set->load_factor = load_factor;
  set->size = 0;
  set->threshold = hash_set_threshold (capacity, load_factor);

  return set;
}

static inline void
hash_set_relocate_entries (HashSet *set, HashSetEntry **old_entries, size_t old_capacity)
{
  Comparator compare;
  HashSetEntry *curr;
  int i;
  int index;
  HashSetEntry *new_entry;
  HashSetEntry *old_entry;
  HashSetEntry *prev;

  compare = set->compare;

  for (i = 0; i < old_capacity; i++)
    {
      old_entry = old_entries[i];

      while (old_entry != NULL)
        {
          new_entry = old_entry;
          old_entry = old_entry->next;

          index = hash_set_index (set, new_entry->element);
          prev = NULL;
          curr = set->entries[index];

          while (curr != NULL && compare (new_entry->element, curr->element) < 0)
            {
              prev = curr;
              curr = curr->next;
            }

          if (prev == NULL)
            {
              set->entries[index] = new_entry;
            }
          else
            {
              prev->next = new_entry;
            }

          new_entry->next = curr;
        }
    }
}

void
hash_set_remove (HashSet *set, void *element)
{
  Comparator compare;
  int comparison;
  HashSetEntry *curr;
  int index;
  HashSetEntry *prev;

  compare = set->compare;
  index = hash_set_index (set, element);
  prev = NULL;
  curr = set->entries[index];

  assert (curr != NULL);

  while ((comparison = compare (element, curr->element)) < 0)
    {
      prev = curr;
      curr = curr->next;
    }

  assert (comparison == 0);

  if (prev == NULL)
    {
      set->entries[index] = curr->next;
    }
  else
    {
      prev->next = curr->next;
    }

  hash_set_entry_free (curr);
  set->size--;
}

static inline size_t
hash_set_threshold (size_t capacity, float load_factor)
{
  return (size_t) (capacity * load_factor);
}
