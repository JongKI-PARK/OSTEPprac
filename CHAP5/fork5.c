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
		int wc = wait(NULL);
		printf("wait return value is %d in Child process\n",wc);
	}
	else{
		printf("parant process\n");
	}
	return 0;
}
