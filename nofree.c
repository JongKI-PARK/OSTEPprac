//nofree.c : forget free after using malloc()
//2022.8.16 park jong ki
//
#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int* p = (int*)malloc(sizeof(int));
	return 0;
}
