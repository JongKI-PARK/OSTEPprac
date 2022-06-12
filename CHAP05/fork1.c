//fork.c : exercise about fork() system call 
//2022.3.26 PARK JONGKI

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int x=100;
	int return_value = fork();
	if(return_value <0){
		printf("fork() error \n");
		exit(1);
	}
	else if(return_value ==0){
		x+=10000;
		printf("Child process with pid :%d\n",getpid());
		printf("x = %d\n",x);
	}
	else{
		int wait_val = wait(NULL);
		x+=return_value;
		printf("wait value : %d\n",wait_val);
		printf("Parent process with pid :%d\n",getpid());
		printf("x = %d\n",x);
	}
	return 0;
}
