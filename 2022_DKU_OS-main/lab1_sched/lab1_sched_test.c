/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32181827
*	    Student name : Park jongki
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
*
*/

//#include <aio.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <fcntl.h>
//#include <errno.h>
//#include <time.h>
//#include <sys/time.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <assert.h>
//#include <pthread.h>
//#include <asm/unistd.h>

#include "lab1_sched_types.h"

extern int current_time = 0;
extern Process* lp_table = NULL;
extern Process* process_list[QUEUE_SIZE];

extern int resched_flag = 0;
extern int preempt_counter = 0;

extern bool CPU_busyRunning = false;
extern Process* running_process = NULL;

Process table1[5] = {
	{'A',NOT_CREATED_YET,0,0,3,0,0,0},
	{'B',NOT_CREATED_YET,2,0,6,0,0,0},
	{'C',NOT_CREATED_YET,4,0,4,0,0,0},
	{'D',NOT_CREATED_YET,6,0,5,0,0,0},
	{'E',NOT_CREATED_YET,8,0,2,0,0,0}
};
Process table2[5] = {
	{'A',NOT_CREATED_YET,0,0,3,0,0,0},
	{'B',NOT_CREATED_YET,0,0,6,0,0,0},
	{'C',NOT_CREATED_YET,1,0,4,0,0,0},
	{'D',NOT_CREATED_YET,2,0,5,0,0,0},
	{'E',NOT_CREATED_YET,3,0,2,0,0,0}
};

int main(int argc, char *argv[]){

	lp_table = table1;
	sys_init();
	schedule_FIFO();
	printf("terminated time : %d,%d,%d,%d,%d\n",
		lp_table[0].terminated_time,
		lp_table[1].terminated_time,
		lp_table[2].terminated_time,
		lp_table[3].terminated_time,
		lp_table[4].terminated_time
	);
}

