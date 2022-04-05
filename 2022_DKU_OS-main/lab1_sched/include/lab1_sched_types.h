#pragma once
/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32181827 
*	    Student name : Park jongki
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

#include <stdio.h>

#define QUEUE_SIZE 10
#define RUNTIME 20

typedef enum {
	false, true
}bool;

typedef enum {
	NOT_CREATED_YET = 0,
	PROCESS_NEW = 1,
	PROCESS_RUNNING = 2,
	PROCESS_READY = 3,
	PROCESS_WAITTING = 4,
	PROCESS_TERMINATED = 5
}Process_state;

typedef struct {
	char pid;
	Process_state state;
	int arrival_time;
	int scheduled_time;
	int time_needed;
	int terminated_time;
	int share;
	int queue_level;
}Process;

typedef struct {
	int front;
	int rear;
	Process* cq[QUEUE_SIZE];
	int count;
}Queue;

int is_empty(Queue* q);
int is_full(Queue* q);
void init_queue(Queue* q);
void ADDQ(Queue* q, Process* data);
Process* DEQ(Queue* q);
int qentity_count(Queue* q);

void sys_init();
void arrival_check();

void FIFO_terminated_check(Process* running_process);
void schedule_FIFO();

void RR1_terminated_check(Process* running_process);
void schedule_RR_1();

void RR4_terminated_check(Process* running_process);
void schedule_RR_4();

Process* find_SJ(Process** ready_list, int list_length);
void SJF_terminated_check(Process* running_process);
void schedule_SJF();

Process* find_HRR(Process* ready_list[], int list_length);
void HRRN_terminated_check(Process* running_process);
void schedule_HRRN();

void MLFQ_1_terminated_check(Process* running_process);
void schedule_MLFQ_1();

void MLFQ_2_terminated_check(Process* running_process);
void schedule_MLFQ_2();

#endif /* LAB1_HEADER_H*/