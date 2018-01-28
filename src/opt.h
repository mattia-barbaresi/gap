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

#ifndef _OPT_H
#define _OPT_H

#include <assert.h>

#define OPT_RELAX_CAPACITY 0
#define OPT_RELAX_CAPACITY_NAME "capacity"
#define OPT_RELAX_QUANTITY 1
#define OPT_RELAX_QUANTITY_NAME "quantity"

typedef struct
{
  double alpha;
  char *file;
  int relax;
  int verbose;
} Options;

void opt_free (Options * opt);

static inline double
opt_get_alpha (Options * opt)
{
  return opt->alpha;
}

static inline char *
opt_get_file (Options * opt)
{
  return opt->file;
}

static inline int
opt_get_relax (Options * opt)
{
  return opt->relax;
}

static inline int
opt_get_verbose (Options * opt)
{
  return opt->verbose;
}

Options *opt_new ();

static inline void
opt_set_alpha (Options * opt, double alpha)
{
  opt->alpha = alpha;
}

static inline void
opt_set_file (Options * opt, char *file)
{
  opt->file = file;
}

static inline void
opt_set_relax (Options * opt, int relax)
{
  opt->relax = relax;
}

static inline void
opt_set_verbose (Options * opt, int verbose)
{
  opt->verbose = verbose;
}

#endif
