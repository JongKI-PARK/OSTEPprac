//fork5.c : what happens when wait() in child process
//2022.3.27 PARK JONGKI

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int rc = fork();
	if(rc <-1){
		printf("fork error\n");
		exit(1);
	}
	else if(rc == 0){
		printf("Child process\n");
		printf("Child process pid : %d\n", getpid());
	}
	else{
		int wc = wait(NULL);
		printf("Parent process pid : %d\n", getpid());
		printf("wait() return value in parant process is %d\n", wc);
	}
	return 0;
}
