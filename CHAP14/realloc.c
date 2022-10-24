// realloc.c : use realloc() and see how it works
// 2022.10.24 park jong ki

#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int* dynamic_array = (int*) malloc(10 * sizeof(int));
	int* new_pointer;
	
	for (int i = 0; i < 10; i++) {
		dynamic_array[i] = i;
	}

	printf("Array's Address before calling relloc() : %p\n", dynamic_array);

	new_pointer = (int*)realloc(dynamic_array, 1000 * sizeof(int));

	for (int i = 10; i < 1000; i++) {
		new_pointer[i] = 1000 - i;
	}
	
	printf(" Content of the newly allocated array\n");
	for (int i = 0; i < 11; i++) {
		printf("new_pointer[%d] = %d\n", i, new_pointer[i]);
	}

	printf(" Existing memory address : %p\n", dynamic_array);
	printf(" New memory address \t: %p\n", new_pointer);
	
	//free(dynamic_array);
	free(new_pointer);
	return 0;
}
