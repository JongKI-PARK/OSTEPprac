//time2.c : measure the time when call system call read() with gettimeofday()
//2022.3.29 PARK JONGKI

#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define READSIZE 0
#define MAX_READ 32

int main(){
	struct timeval starttime,endtime;
	char fname[20] = "hello.txt";
	char buf[MAX_READ];
	int fd = open(fname,O_RDONLY);
	assert(fd>-1);
	gettimeofday(&starttime,NULL);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE);
	read(fd,buf,READSIZE); //10times
	gettimeofday(&endtime,NULL);
	close(fd);
	printf("10 times read() system call takes %ld : %ld sec reading 0bytes\n",(endtime.tv_sec-starttime.tv_sec),(endtime.tv_usec-starttime.tv_usec));
	return 0;
}
