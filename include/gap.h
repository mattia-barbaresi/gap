#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

typedef char* str;

int readDataFromFile(str filePath){

	FILE *pFile = fopen(filePath,"r");


	if(pFile!=NULL)
	{
		printf("This is the function for reading data from file %s! \n", filePath);

		fclose (pFile);
		return 0;
	}
	else
		printf("ERROR: file %s! not found! \n", filePath);

	
	return 1;
};