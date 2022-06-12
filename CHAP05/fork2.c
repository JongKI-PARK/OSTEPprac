//fork2.c : file descripter manipulation in child and parant process
//2022.3.27 PARK JONGKI

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_BUF 32

char fname[10]="a.txt";

int main(){
	int fd = open(fname,O_RDWR | O_CREAT | O_EXCL,0664);
	assert(fd>-1);
	char buf[MAX_BUF];
	int read_size, write_size;
	int rc = fork();
	assert(rc>-1);
	if(rc==0){
		printf("Child process\n");
		printf("fd = %d\n",fd);
		write(fd,"child process text\n",20);
	}
	else {
		printf("Parant process\n");
		printf("fd = %d\n",fd);
		write(fd,"parant process text\n",21);
	}
	close(fd);
	fd = open(fname,O_RDONLY);
	while(1){
		read_size = read(fd,buf,MAX_BUF);
		if(read_size == 0)
			break;
		write_size = write(1,buf,read_size);
	}
	close(fd);
	return 0;
}
