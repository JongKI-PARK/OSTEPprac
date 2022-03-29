//time1.c : measure how precise gettimeofday() is
//2022.3.29 PARK JONGKI

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define LOOP 10

int main(){
	/*
	struct timeval mytime;
	for(int i=0;i<LOOP;i++){
		gettimeofday(&mytime,NULL);
		printf("Loop %d ->  %ld : %ld\n",i,mytime.tv_sec,mytime.tv_usec);
	}
	*/
	//for loop time will be added
	
	struct timeval mytime[10];
	gettimeofday(&mytime[0],NULL);
	gettimeofday(&mytime[1],NULL);
	gettimeofday(&mytime[2],NULL);
	gettimeofday(&mytime[3],NULL);
	gettimeofday(&mytime[4],NULL);
	gettimeofday(&mytime[5],NULL);
	gettimeofday(&mytime[6],NULL);
	gettimeofday(&mytime[7],NULL);
	gettimeofday(&mytime[8],NULL);
	gettimeofday(&mytime[9],NULL);
	printf("10 times gettimeofday() takes %ld : %ld sec\n",mytime[9].tv_sec-mytime[0].tv_sec,mytime[9].tv_usec-mytime[0].tv_usec);	
	return 0;
}
