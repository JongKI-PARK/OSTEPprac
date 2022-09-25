//malloc100.c : a program which creates an array of integers with malloc
// and try to access the memory in an inaccessible location
//2022.9.25 park jong ki

#include <stdio.h>
#include <stdlib.h>

int main() {
	int* data;
	data = (int*) malloc(sizeof(int) * 100);
	
	data[100] = 0;

	return 0;
}
