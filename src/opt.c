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

#include <stdlib.h>

#include "opt.h"

#define OPT_ALPHA_DEFAULT 2.0
#define OPT_RELAX_DEFAULT 0
#define OPT_VERBOSE_DEFAULT 0

void
opt_free (Options * opt)
{
  free (opt);
}

Options *
opt_new ()
{
  Options *opt;

  opt = malloc (sizeof (Options));

  if (opt == NULL)
    {
      return NULL;
    }

  opt->alpha = OPT_ALPHA_DEFAULT;
  opt->relax = OPT_RELAX_DEFAULT;
  opt->verbose = OPT_VERBOSE_DEFAULT;

  return opt;
}
