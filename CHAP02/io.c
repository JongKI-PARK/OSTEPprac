//io.c :open file , write a short message in it and print the message in STDOUT check for persistence
//2022.3.22 PARK JONGKI

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#define MAX_BUF 13

char fname[]= "hello.txt";

int main(int argc, char *argv[]){
	int fd=open(fname,O_RDWR | O_CREAT | O_EXCL,0664);
	char buf[MAX_BUF];

	assert(fd>-1);
	int read_size = write(fd,"hello world\n",MAX_BUF);
	assert(read_size ==13);
	close(fd);

	fd = open(fname,O_RDONLY);
	read_size=read(fd,buf,MAX_BUF);
	assert(read_size==13);
	write(1,buf,read_size);
	close(fd);
	return 0;
}
