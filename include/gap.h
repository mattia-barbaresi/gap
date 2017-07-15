#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef char* str;

typedef struct 
{
    int** a;
    int* b;
    int** c;
    int n,m;
} Problem;


Problem** readDataFromFile(str filePath){

	FILE *pFile = fopen(filePath,"r");


	if(pFile!=NULL)
	{
		Problem** problems;
		int numProblems = 0;
		int n,m,q;

		fscanf(pFile,"%d",&numProblems);

		problems = malloc(numProblems * sizeof(Problem *));

		for (int p = 0; p < numProblems; ++p)
		{
			printf("read problem %d...\n", p);
			problems[p] = (Problem *) malloc(sizeof(Problem));
			//read problem instance

			//read # containers
			fscanf(pFile,"%d", &m);
			//read # itemsw
			fscanf(pFile,"%d", &n);

			problems[p]->m = m;
			problems[p]->n = n;

			//init a
			problems[p]->a = malloc(m * sizeof(int*));
			problems[p]->a[0] =  malloc(m * n * sizeof(int));
			for(q = 1; q < m; q++)
				problems[p]->a[q] = problems[p]->a[0] + q * n;

			//init b
			problems[p]->b = malloc(m * sizeof(int));

			//init c
			problems[p]->c = malloc(m * sizeof(int*));
			problems[p]->c[0] =  malloc(m * n * sizeof(int));
			for(q = 1; q < m; q++)
				problems[p]->c[q] = problems[p]->c[0] + q * n;

			int i, j;
			
			//read c[m][n]
			//foreach container
			for (i = 0; i < m; ++i)
				for (j = 0; j < n; ++j){
					//read cost of assign item j to container i
					fscanf(pFile,"%d",&(problems[p]->c[i][j]));
				}

			//read a[m][n]
			//foreach container
			for (i = 0; i < m; ++i)
				for (j = 0; j < n; ++j)
					//read space of item j in container i
					fscanf(pFile,"%d",&(problems[p]->a[i][j]));

			//read b
			//foreach container
			for (i = 0; i < m; ++i)
				//read total space of container i
				fscanf(pFile,"%d",&(problems[p]->b[i]));

		}
		fclose (pFile);
		printf("Data readed from file %s.\n", filePath);
		return problems;
	}
	else
		printf("ERROR: file %s! not found! \n", filePath);
	
	return NULL;
};