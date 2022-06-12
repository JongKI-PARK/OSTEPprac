//fork7.c : to see what happen when i call printf after child process close STDOUT_FILENO 
//2022.3.27 PARK JONGKI

#include <stdio.h>
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	close(STDOUT_FILENO);
	int rc=fork();
	assert(rc>-1);
	if(rc == 0){
		close(STDOUT_FILENO);
		printf("message from child process\n");
	}
	else{
		wait(NULL);
		printf("message from parant process\n");
	}
	return 0;
}
