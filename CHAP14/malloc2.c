// malloc2.c : after releasing heap allocated memory, it trys to access
// already released memory location which is invalid
//2022.9.25 park jong ki

#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int* pointer = (int*) malloc(sizeof(int) * 100);
	for (int i = 0; i < 100; i++) {
		pointer[i] = 100;
	}

	free(pointer);

	int data = pointer[10];
	printf("The data in pointer[10] is %d\n", data);

	return 0;
}
