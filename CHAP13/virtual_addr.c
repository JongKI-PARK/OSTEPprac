//virtual_addr.c : what user see is virtual address
//you can see where the segment of code, data, heap, stack located
//2022.8.16 park jong ki

#include <stdio.h>
#include <stdlib.h>

int global_init = 1;
int global_noinit = 10;

int main(int argc, char* argv[]) {
	int local = 100;

	printf("Location of the code :\t%p\n", main);
	printf("Location of the data :\t%p (initialized)\n", &global_init);
	printf("Location of the data :\t%p (not initialized)\n", &global_noinit);
	printf("Location of the heap :\t%p\n", malloc(100e3));
	printf("Location of the stack :\t%p\n", &local);
	return 0;
}
