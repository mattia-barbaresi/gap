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
#include <unistd.h>

#include "gap.h"
#include "util.h"

#define VERSION "0.1"

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


static void
print_error (char *message)
{
  fprintf (stderr, "Error: %s\n", message);
}

static void
print_short_usage ()
{
  printf ("List of options:\n");
  printf ("  -h         Print this message\n");
  printf ("  -i <file>  Specify the input file\n");
  printf ("  -v         Print program version\n");
  printf ("  -V         Verbose\n");
}

static void
print_usage ()
{
  printf ("gap %s - Generalized Assignment Problem\n", VERSION);
  printf ("Copyright Mattia Barbaresi and Massimo Neri <hello@mneri.me>, all rights\n");
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
  int c;
  char *ifile = NULL;
  extern char *optarg;
  int verbose = FALSE;
  Problem **problems;
  int numProblems = 0;

  while ((c = getopt (argc, argv, "hi:vV")) != -1)
    {
      switch (c)
	{
	case 'h':
	  print_usage ();
	  return EXIT_SUCCESS;
	case 'i':
	  ifile = optarg;
	  break;
	case 'v':
	  print_version ();
	  return EXIT_SUCCESS;
	case 'V':
	  verbose = TRUE;
	  break;
	default:
	  print_error ("invalid option");
	  print_short_usage ();
	  return EXIT_FAILURE;
	}
    }

  if (ifile == NULL)
    {
      print_error ("no input file");
      print_short_usage ();
      return EXIT_FAILURE;
    }

  if ((problems = gap_read_data_from_file (ifile, &numProblems)) == NULL)
    {
      perror ("Error");
      return EXIT_FAILURE;
    }

  for (int i = 0; i < numProblems; ++i)
    {
      /* code */
      int sol = gap_calcuate_lagrangian_function(*(problems[i]));
      printf("valore soluzione lagrnagiana: %d\n",sol );
      gap_calculate_lower_bound ();
    }

    gap_calculate_initial(*(problems[0]));


  return EXIT_SUCCESS;
}
