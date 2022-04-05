/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32181827
*	    Student name : Park jongki
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scheduler algorithm function'definition.
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

#define QUEUE_SIZE 10
#define RUNTIME 20

struct Process Process;
struct Queue Queue;

extern int current_time = 0;
extern Process* lp_table = NULL;
extern Process* process_list[QUEUE_SIZE];

extern int resched_flag = 0;
extern int preempt_counter = 0;

extern bool CPU_busyRunning = false;
extern Process* running_process = NULL;


int is_empty(Queue* q) {
	if (q->count == 0)
		return 1;
	else
		return 0;
}

int is_full(Queue* q) {
	if (q->count == QUEUE_SIZE)
		return 1;
	else
		return 0;
}

void init_queue(Queue* q) {
	q->front = q->rear = 0;
	q->count = 0;
}

void ADDQ(Queue* q, Process* data) {
	if (is_full(q) != 1) {
		q->rear = (q->rear + 1) % QUEUE_SIZE;
		q->cq[q->rear] = data;
		q->count++;
	}
}

Process* DEQ(Queue* q) {
	Process* data;
	if (is_empty(q) == 0) {
		q->front = (q->front + 1) % QUEUE_SIZE;
		data = q->cq[q->front];
		q->count--;
		return data;
	}
	else
		return 0;
}
int qentity_count(Queue* q) {
	return q->count;
}

void sys_init() {
	current_time = 0;
	CPU_busyRunning = false;
	running_process = NULL;
	resched_flag = 0;
	preempt_counter = 0;
	running_process = NULL;
	process_list[QUEUE_SIZE] = { NULL, };
	preempt_counterA[3] = { 0, 0, 0 };
}

void arrival_check() {
	for (int i = 0; i < 5; i++) {
		if ((lp_table + i)->arrival_time == current_time) {
			(lp_table + i)->state = PROCESS_NEW;
		}
	}
}

void FIFO_terminated_check(Process* running_process) {
	if (running_process != NULL) {
		if (running_process->time_needed > running_process->scheduled_time) {
			CPU_busyRunning = true;
		}
		else if (running_process->time_needed == running_process->scheduled_time) {
			running_process->terminated_time = current_time;
			running_process->state = PROCESS_TERMINATED;
			CPU_busyRunning = false;
		}
		else
			CPU_busyRunning = false;
	}
	else
		CPU_busyRunning = false;
}

void schedule_FIFO() {
	Queue q0;
	init_queue(&q0);

	while (current_time <= RUNTIME) {
		arrival_check();

		for (int i = 0; i < 5; i++) {
			if ((lp_table + i)->state == PROCESS_NEW) {
				ADDQ(&q0, &lp_table[i]);
				lp_table[i].state = PROCESS_READY;
			}
		}
		if (CPU_busyRunning == false) {
			running_process = DEQ(&q0);
			if (running_process == NULL)
				break;
			CPU_busyRunning = true;
			running_process->state = PROCESS_RUNNING;
		}
		running_process->scheduled_time++;
		current_time++;
		FIFO_terminated_check(running_process);
	}
}

void RR1_terminated_check(Process* running_process) {
	if (running_process->time_needed > running_process->scheduled_time) {
		resched_flag = 1;
		running_process->state = PROCESS_READY;
	}
	else if (running_process->time_needed == running_process->scheduled_time) {
		resched_flag = 0;
		running_process->state = PROCESS_TERMINATED;
		running_process->terminated_time = current_time;
	}
}

void schedule_RR_1() {
	Queue q0;
	init_queue(&q0);
	resched_flag = 0;
	while (current_time <= RUNTIME) {
		arrival_check();
		for (int i = 0; i < 5; i++) {
			if (lp_table[i].state == PROCESS_NEW) {
				ADDQ(&q0, &lp_table[i]);
				lp_table[i].state = PROCESS_READY;
			}
		}
		if (resched_flag == 1) {
			ADDQ(&q0, running_process);
			running_process = NULL;
			CPU_busyRunning = false;
			resched_flag = 0;
		}
		running_process = DEQ(&q0);
		if (running_process == NULL)
			break;
		CPU_busyRunning = true;
		running_process->state = PROCESS_RUNNING;

		running_process->scheduled_time++;
		current_time++;
		RR1_terminated_check(running_process);
	}
}

void RR4_terminated_check(Process* running_process) {
	if (preempt_counter < 4) {
		if (running_process->time_needed > running_process->scheduled_time) {
			CPU_busyRunning = true;
			running_process->state = PROCESS_RUNNING;
		}
		else if (running_process->time_needed == running_process->scheduled_time) {
			CPU_busyRunning = false;
			running_process->state = PROCESS_TERMINATED;
			running_process->terminated_time = current_time;
		}
	}
	else {
		CPU_busyRunning = false;
		if (running_process->time_needed > running_process->scheduled_time) {
			resched_flag = 1;
			running_process->state = PROCESS_READY;
		}
		if (running_process->time_needed == running_process->scheduled_time) {
			resched_flag = 0;
			running_process->state = PROCESS_TERMINATED;
			running_process->terminated_time = current_time;
		}
	}
}

void schedule_RR_4() {
	Queue q0;
	init_queue(&q0);
	resched_flag = 0;
	preempt_counter = 0;
	while (current_time <= RUNTIME) {
		arrival_check();
		for (int i = 0; i < 5; i++) {
			if (lp_table[i].state == PROCESS_NEW) {
				ADDQ(&q0, &lp_table[i]);
				lp_table[i].state = PROCESS_READY;
			}
		}
		if (resched_flag == 1) {
			ADDQ(&q0, running_process);
			running_process = NULL;
			CPU_busyRunning = false;
			resched_flag = 0;
		}

		if (CPU_busyRunning == false) {
			running_process = DEQ(&q0);
			preempt_counter = 0;
			if (running_process == NULL)
				break;
			CPU_busyRunning = true;
			running_process->state = PROCESS_RUNNING;
		}
		running_process->scheduled_time++;
		current_time++;
		preempt_counter++;
		RR4_terminated_check(running_process);
	}
}

Process* find_SJ(Process** ready_list, int list_length) {
	int min = ready_list[0]->time_needed;
	Process* SJ = ready_list[0];

	for (int x = 1; x < list_length; x++) {
		if (SJ->state == PROCESS_TERMINATED) {
			if (ready_list[x]->state != PROCESS_TERMINATED) {
				SJ = ready_list[x];
				min = SJ->time_needed;
			}
		}

		if ((min > ready_list[x]->time_needed) && (ready_list[x]->state != PROCESS_TERMINATED)) {
			SJ = ready_list[x];
			min = SJ->time_needed;
		}
	}
	return SJ;
}

void SJF_terminated_check(Process* running_process) {
	if (running_process->scheduled_time < running_process->time_needed) {
		CPU_busyRunning = true;
	}

	else {
		if (running_process->scheduled_time == running_process->time_needed) {
			running_process->state = PROCESS_TERMINATED;
			running_process->terminated_time = current_time;
			CPU_busyRunning = false;
		}
	}
}

void schedule_SJF() {
	memset(process_list, 0x00, sizeof(process_list));
	int list_index = 0;
	while (current_time <= RUNTIME) {
		arrival_check();
		for (int i = 0; i < 5; i++) {
			if (lp_table[i].state == PROCESS_NEW) {
				lp_table[i].state = PROCESS_READY;
				process_list[list_index] = &lp_table[i];
				list_index++;
			}
		}
		if (!CPU_busyRunning) {
			running_process = find_SP(process_list, list_index);
		}
		running_process->scheduled_time++;
		current_time++;
		SJF_terminated_check(running_process);
	}
}

Process* find_HRR(Process* ready_list[], int list_length) {
	double max = (double)(current_time - ready_list[0]->arrival_time + ready_list[0]->time_needed) /
		ready_list[0]->time_needed;
	Process* HRR = ready_list[0];

	for (int x = 1; x < list_length; x++) {

		if (HRR->state == PROCESS_TERMINATED) {
			if (ready_list[x]->state != PROCESS_TERMINATED) {
				HRR = ready_list[x];
				max = (double)(current_time - HRR->arrival_time + HRR->time_needed) / HRR->time_needed;
			}
		}

		if ((max < (double)((current_time - ready_list[x]->arrival_time + ready_list[x]->time_needed)
			/ ready_list[x]->time_needed)) && (ready_list[x]->state != PROCESS_TERMINATED)) {
			HRR = ready_list[x];
			max = (double)(current_time - HRR->arrival_time + HRR->time_needed) / HRR->time_needed;
		}
	}
	return HRR;
}

void HRRN_terminated_check(Process* running_process) {
	if (running_process->scheduled_time < running_process->time_needed) {
		CPU_busyRunning = true;
	}

	else {
		if (running_process->scheduled_time == running_process->time_needed) {
			running_process->state = PROCESS_TERMINATED;
			running_process->terminated_time = current_time;
			CPU_busyRunning = false;
		}
	}
}

void schedule_HRRN() {
	memset(process_list, 0x00, sizeof(process_list));
	int list_index = 0;
	while (current_time <= RUNTIME) {
		arrival_check();
		for (int i = 0; i < 5; i++) {
			if (lp_table[i].state == PROCESS_NEW) {
				lp_table[i].state = PROCESS_READY;
				process_list[list_index] = &lp_table[i];
				list_index++;
			}
		}
		if (!CPU_busyRunning) {
			running_process = find_HRR(process_list, list_index);
		}
		running_process->scheduled_time++;
		current_time++;
		HRRN_terminated_check(running_process);
	}
}

void MLFQ_1_terminated_check(Process* running_process) {
	if (running_process->scheduled_time < running_process->time_needed) {
		resched_flag = 1;
	}
	else if (running_process->scheduled_time == running_process->time_needed) {
		running_process->state = PROCESS_TERMINATED;
		running_process->terminated_time = current_time;
		CPU_busyRunning = false;
	}
}

void schedule_MLFQ_1() {
	Queue q0, q1, q2;
	init_queue(&q0);
	init_queue(&q1);
	init_queue(&q2);
	resched_flag = 0;

	while (current_time <= RUNTIME) {
		arrival_check();
		for (int i = 0; i < 5; i++) {
			if (lp_table[i].state == PROCESS_NEW) {
				ADDQ(&q0, &lp_table[i]);
				lp_table[i].state = PROCESS_READY;
				lp_table[i].queue_level = 0;
			}
		}

		if (resched_flag == 1) {
			if ((is_empty(&q0) == false) || (is_empty(&q1) == false) || (is_empty(&q2) == false)) {
				if (running_process->queue_level < 2) {
					running_process->queue_level++;
				}
			}

			switch (running_process->queue_level) {
			case 0:
				ADDQ(&q0, running_process);
				running_process->state = PROCESS_READY;
				break;

			case 1:
				ADDQ(&q1, running_process);
				running_process->state = PROCESS_READY;
				break;

			case 2:
				ADDQ(&q2, running_process);
				running_process->state = PROCESS_READY;
				break;
			}
			running_process = NULL;
			CPU_busyRunning = false;
			resched_flag = 0;
		}

		if (CPU_busyRunning == false) {
			if (is_empty(&q0) == false) {
				running_process = DEQ(&q0);
				running_process->state = PROCESS_RUNNING;
				CPU_busyRunning = true;
			}

			else {
				if (is_empty(&q1) == false) {
					running_process = DEQ(&q1);
					running_process->state = PROCESS_RUNNING;
					CPU_busyRunning = true;
				}
				else {
					if (is_empty(&q2) == false) {
						running_process = DEQ(&q2);
						running_process->state = PROCESS_RUNNING;
						CPU_busyRunning = true;
					}
				}
			}
		}
		if (running_process != NULL) {
			running_process->scheduled_time++;
		}
		current_time++;
		MLFQ_1_terminated_check(running_process);
	}
}

void MLFQ_2_terminated_check(Process* running_process) {
	if (running_process->scheduled_time < running_process->time_needed) {
		switch (running_process->queue_level) {
		case 0:
			if (preempt_counterA[0] < 1) {
				resched_flag = 0;
				CPU_busyRunning = true;
			}
			else if (preempt_counterA[0] == 1) {
				resched_flag = 1;
				CPU_busyRunning = false;
			}
			break;

		case 1:
			if (preempt_counterA[1] < 2) {
				resched_flag = 0;
				CPU_busyRunning = true;
			}
			else if (preempt_counterA[1] == 2) {
				resched_flag = 1;
				CPU_busyRunning = false;
			}
			break;

		case 2:
			if (preempt_counterA[2] < 4) {
				resched_flag = 0;
				CPU_busyRunning = true;
			}
			else if (preempt_counterA[2] == 4) {
				resched_flag = 1;
				CPU_busyRunning = false;
			}
			break;
		}
	}
	else if (running_process->scheduled_time == running_process->time_needed) {
		running_process->state = PROCESS_TERMINATED;
		running_process->terminated_time = current_time;
		CPU_busyRunning = false;
	}
}

void schedule_MLFQ_2() {
	Queue q0, q1, q2;
	init_queue(&q0);
	init_queue(&q1);
	init_queue(&q2);
	resched_flag = 0;

	while (current_time <= RUNTIME) {
		arrival_check();
		for (int i = 0; i < 5; i++) {
			if (lp_table[i].state == PROCESS_NEW) {
				ADDQ(&q0, &lp_table[i]);
				lp_table[i].state = PROCESS_READY;
				lp_table[i].queue_level = 0;
			}
		}

		if (resched_flag == 1) {
			if ((is_empty(&q0) == false) || (is_empty(&q1) == false) || (is_empty(&q2) == false)) {
				if (running_process->queue_level < 2) {
					running_process->queue_level++;
				}
			}

			switch (running_process->queue_level) {
			case 0:
				ADDQ(&q0, running_process);
				running_process->state = PROCESS_READY;
				break;

			case 1:
				ADDQ(&q1, running_process);
				running_process->state = PROCESS_READY;
				break;

			case 2:
				ADDQ(&q2, running_process);
				running_process->state = PROCESS_READY;
				break;
			}
			running_process = NULL;
			CPU_busyRunning = false;
			resched_flag = 0;
		}

		if (CPU_busyRunning == false) {
			if (is_empty(&q0) == false) {
				running_process = DEQ(&q0);
				running_process->state = PROCESS_RUNNING;
				CPU_busyRunning = true;
				preempt_counterA[0] = 0;
			}

			else {
				if (is_empty(&q1) == false) {
					running_process = DEQ(&q1);
					running_process->state = PROCESS_RUNNING;
					CPU_busyRunning = true;
					preempt_counterA[1] = 0;
				}
				else {
					if (is_empty(&q2) == false) {
						running_process = DEQ(&q2);
						running_process->state = PROCESS_RUNNING;
						CPU_busyRunning = true;
						preempt_counterA[2] = 0;
					}
				}
			}
		}
		if (running_process != NULL) {
			running_process->scheduled_time++;
			preempt_counterA[running_process->queue_level]++;
		}
		current_time++;
		MLFQ_2_terminated_check(running_process);
	}
}