#include <gap.h>

	//to take time
	clock_t t;

	//set of problems per file
	Problem** problems;

//calculate a lower bound for the problem with Lagrangian relaxiation.
int calculateLowerBound () {

	printf("Calculating lower bound....\n");
	//init time
	t = clock();

	//calcolo L(u) : rilassamento lagrangiano

	//il duale di L(u) definito come Max [ L(u)], u >= 0 -> LOWER BOUND

	//per risolvere il duale lagrangiano posso usare metodo del subgradiente

	//end time
    t = clock() - t;

	printf("Calculated lower bound in %f seconds.\n",((double)t)/CLOCKS_PER_SEC);
	return 0;
}

//calculate a lower bound for the problem with Lagrangian relaxiation.
int branchAndBound () {

	printf("Executing branch-and-bound....\n");
	//init time
	t = clock();


	//end time
    t = clock() - t;

	printf("Branch-and-bound executed in %f seconds.\n",((double)t)/CLOCKS_PER_SEC);
	return 0;
}

int main (int argc, char** argv) {


	problems = readDataFromFile("datasets/gap1.txt");

	int m = problems[0]->m;
	int n = problems[0]->n;
	printf("prova elemento prob(0)->m: %d\n", m);
	printf("prova elemento prob(0)->n: %d\n", problems[0]->n);
	printf("prova elemento prob(0)->a[m][n]: %d\n", problems[0]->a[m-1][n-1]);
	printf("prova elemento prob(0)->b[m]: %d\n", problems[0]->b[m-1]);
	printf("prova elemento prob(0)->c[m][n]: %d\n", problems[0]->c[m-1][n-1]);

	calculateLowerBound();
	return 0;
}