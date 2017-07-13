#include <gap.h>

int main (int argc, char** argv) {
	int b = readDataFromFile("README.md");
	printf("b: %d\n", b);
	return 0;
}
