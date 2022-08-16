//null.c : creates a pointer to an integer
//and sets it to NULL and it will try to dereference it
//2022.8.16 park jong ki
//
#include <stdio.h>

int main() {
	
	int* pointer = NULL;
	int i = *pointer;

	return 0;
}
