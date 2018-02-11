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
 * @file main.c
 * @brief Entry point of the program and command line arguments parsing.
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bab.h"
#include "gap.h"
#include "opt.h"
#include "problem.h"
#include "subgradient.h"
#include "util.h"

#define ERROR_PREFIX "Error"
#define VERSION "0.1"

static Options *parse (int argc, char **argv);

/**
 * @brief Print an error message.
 */
static void print_error (char *message);

/**
 * @brief Print short usage message.
 */
static void print_short_usage ();

/**
 * @brief Print usage message.
 */
static void print_usage ();

/**
 * @brief Print the version
 */
static void print_version ();

static Options *
parse (int argc, char **argv)
{
  double alpha;
  int c;
  Options *opt = opt_new ();
  extern char *optarg;

  while ((c = getopt (argc, argv, "a:hi:r:vV")) != -1)
    {
      switch (c)
	{
	case 'a':
	  alpha = strtod (optarg, NULL);

	  if (alpha == 0.0)
	    {
	      print_error ("invalid alpha value");
	      print_short_usage ();
	      exit (EXIT_FAILURE);
	    }

	  opt_set_alpha (opt, alpha);
	  break;
	case 'h':
	  print_usage ();
	  exit (EXIT_SUCCESS);
	case 'i':
	  opt_set_file (opt, optarg);
	  break;
	case 'r':
	  if (strcmp (optarg, OPT_RELAX_CAPACITY_NAME) == 0)
	    {
	      opt_set_relax (opt, OPT_RELAX_CAPACITY);
	    }
	  else if (strcmp (optarg, OPT_RELAX_QUANTITY_NAME) == 0)
	    {
	      opt_set_relax (opt, OPT_RELAX_QUANTITY);
	    }
	  else
	    {
	      print_error ("invalid relax value");
	      print_short_usage ();
	      exit (EXIT_FAILURE);
	    }
	  break;
	case 'v':
	  print_version ();
	  exit (EXIT_SUCCESS);
	case 'V':
	  opt_set_verbose (opt, TRUE);
	  break;
	default:
	  print_error ("invalid option");
	  print_short_usage ();
	  exit (EXIT_FAILURE);
	}
    }

  return opt;
}

static void
print_error (char *message)
{
  fprintf (stderr, "%s: %s\n", ERROR_PREFIX, message);
}

static void
print_short_usage ()
{
  printf ("List of options:\n");
  printf ("  -a <double>            Alpha parameter initial value\n");
  printf ("  -h                     Print this message\n");
  printf ("  -i <file>              Specify the input file\n");
  printf ("  -r <capacity|quantity> Relaxation type\n");
  printf ("  -v                     Print program version\n");
  printf ("  -V                     Verbose\n");
}

static void
print_usage ()
{
  printf ("gap %s - Generalized Assignment Problem\n", VERSION);
  printf ("Copyright Mattia Barbaresi <mattia.barbaresi@gmail.com> and Massimo Neri <hello@mneri.me>, all rights\n");
  printf ("reserved. Licensed under the GNU GPLv3.0.\n");
  printf ("\n");
  print_short_usage ();
  printf ("\n");
  printf ("Examples:\n");
  printf ("  gap -i dataset.txt\n");
  printf ("  gap -i dataset.txt -V\n");
}

static void
print_version ()
{
  printf ("%s\n", VERSION);
}

int
main (int argc, char **argv)
{
  int i;
  Options *opt;
  ArrayList *problems;
  opt = parse (argc, argv);

  if (opt_get_file (opt) == NULL)
    {
      print_error ("no input file");
      print_short_usage ();
      return EXIT_FAILURE;
    }

  if ((problems = gap_problems_from_file (opt_get_file (opt))) == NULL)
    {
      perror (ERROR_PREFIX);
      return EXIT_FAILURE;
    }

  for (i = 0; i < array_list_size (problems); i++)
    {
      printf ("\n PROBLEM %d   ===================================\n\n", i);

      if (gap_subgradient (array_list_get (problems, i), opt->relax) == 0)
	{
	  // We found the optimal solution
	  printf ("Exit subgradient with optimal solution!\n");
	}
      else
	{
	  // Branch and bound
	  gap_bab (array_list_get (problems, i));
	}

      //print solution
      gap_calculate_solution (array_list_get (problems, i));
      // gap_problem_print (array_list_get (problems, i));
    }

  array_list_clear (problems, (Destructor) gap_problem_free);
  array_list_free (problems);
  opt_free (opt);

  return EXIT_SUCCESS;
}
