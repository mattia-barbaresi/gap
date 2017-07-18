#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "gap.h"

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

//calculate a lower bound for the problem with Lagrangian relaxiation.
int
calculateLowerBound ()
{
  clock_t t;

  printf ("Calculating lower bound....\n");
  t = clock ();

  //calcolo L(u) : rilassamento lagrangiano
  //il duale di L(u) definito come Max [ L(u)], u >= 0 -> LOWER BOUND
  //per risolvere il duale lagrangiano posso usare metodo del subgradiente

  t = clock () - t;

  printf ("Calculated lower bound in %f seconds.\n", ((double) t) / CLOCKS_PER_SEC);

  return 0;
}

//calculate a lower bound for the problem with Lagrangian relaxiation.
int
branchAndBound ()
{
  clock_t t;
  printf ("Executing branch-and-bound....\n");
  //init time
  t = clock ();

  //end time
  t = clock () - t;

  printf ("Branch-and-bound executed in %f seconds.\n", ((double) t) / CLOCKS_PER_SEC);
  return 0;
}

int
main (int argc, char **argv)
{
  int c;
  char *ifile = NULL;
  extern char *optarg;
  extern int optopt;
  Problem **problems;

  while ((c = getopt (argc, argv, "hi:v")) != -1)
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

  problems = readDataFromFile (ifile);

  int m = problems[0]->m;
  int n = problems[0]->n;
  printf ("prova elemento prob(0)->m: %d\n", m);
  printf ("prova elemento prob(0)->n: %d\n", problems[0]->n);
  printf ("prova elemento prob(0)->a[m][n]: %d\n", problems[0]->a[m - 1][n - 1]);
  printf ("prova elemento prob(0)->b[m]: %d\n", problems[0]->b[m - 1]);
  printf ("prova elemento prob(0)->c[m][n]: %d\n", problems[0]->c[m - 1][n - 1]);

  calculateLowerBound ();

  return EXIT_SUCCESS;
}

void
print_error (char *message)
{
  fprintf (stderr, "Warning: %s.\n", message);
}

void
print_short_usage ()
{
  printf ("List of options:\n");
  printf ("  -h         Print this message\n");
  printf ("  -i <file>  Specify the input file\n");
  printf ("  -v         Print program version\n");
}

void
print_usage ()
{
  printf ("gap %s - Generalized Assignment Problem\n", VERSION);
  printf ("Copyright Mattia Barbaresi and Massimo Neri <hello@mneri.me>, all rights\n");
  printf ("reserved. Licensed under the GNU GPLv3.0.\n");
  printf ("\n");
  print_short_usage ();
  printf ("\n");
  printf ("Examples:\n");
  printf ("  gap -f dataset.txt\n");
}

void
print_version ()
{
  printf ("%s\n", VERSION);
}
