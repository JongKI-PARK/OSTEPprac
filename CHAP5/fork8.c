//fork8.c : IPC between parant and child process with pipe()
//2022.3.27 PARK JONGKI

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1
#define MAX_BUF 32

int main(){
	int fd[2];
	char buf[MAX_BUF];
	pipe(fd);
	int rc = fork();

	assert(rc > -1);
	if(rc==0){
		close(fd[READ]);
		write(fd[WRITE],"message from CHILD",MAX_BUF);
	}
	else{
		wait(NULL);
		close(fd[WRITE]);
		read(fd[READ],buf,MAX_BUF);
		printf("PARANT got message : %s\n",buf);
	}
	printf(" file descriptor [0] : %d\n file descriptor [1] : %d\n",fd[0],fd[1]);
	return 0;
}
