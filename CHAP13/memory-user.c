// memory-user.c : allocating memory in MB 
// 2022.9.26 park jong ki

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		printf("Usage : memory-user [memory (MB)] [Number elements]\n");
		printf("argv[1] : Memory allocation unit is MB\n");
		printf("argv[2] : Number of dynamic allocated array elements to print out\n"
				"	default option (0) prints all elements \n");
		exit(0);
	}

	int memory_use = atoi(argv[1]) * 1024 * 1024;
	int array_length = memory_use / (int) sizeof(int);
	int element_num = atoi(argv[2]);
	if (element_num > array_length || element_num < 0) {
		printf("Wrong argument for argv[2] : You cannot read that much elements\n"
				"or the value is less then 0\n");
		exit(0);
	}

	int* array = (int*) malloc(memory_use);
	
	if (element_num == 0) {
		for (int i = 0; i < array_length; i++) {
			if (i % 5 == 0)
				printf("\n");

			printf("%d\t", array[i]);
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < element_num; i++) {
			if (i % 5 == 0)
				printf("\n");

			printf("%d\t", array[i]);
		}
		printf("\n");
	}

	free(array);
	return 0;
}
