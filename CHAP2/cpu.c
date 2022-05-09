//cpu.c : printing argv[1] every 1sec
//2022.3.19 PARK JONGKI

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr,"usage: cpu <string>\n");
		exit(1);
	}
	char *str = argv[1];
	printf("%d\n",getpid());
	while(1){
		printf("%s\n",str);
		Spin(1);
	}
	return 0;
}
