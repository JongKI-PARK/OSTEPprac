//threads.c : see simple concurrency issue in multi threaded program
//2022.3.22 PARK JONGKI

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include <unistd.h>

volatile int counter =0;
int loops;

void *worker(void *arg){
	int i;
	pthread_t thread_id = pthread_self();
	for(i=0;i<loops;i++){
		counter++;
		printf("pid : %d, thread id : %d\n",getpid(),(int)thread_id);
	}
}

int main(int argc, char *argv[]){
	if(argc !=2){
		fprintf(stderr, "usage: threads <value>\n");
		exit(1);
	}
	loops = atoi(argv[1]);
	pthread_t p1,p2;
	printf("Initial value : %d\n",counter);

	pthread_create(&p1,NULL,worker,NULL);
	pthread_create(&p2,NULL,worker,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printf("Final value : %d\n",counter);
	return 0;
}
