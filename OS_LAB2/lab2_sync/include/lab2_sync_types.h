/*
*   DKU Operating System Lab
*           Lab2 (Hash Queue Lock Problem)
*           Student id : 32181827 
*           Student name : Park jongki
*
*   lab1_sync_types.h :
*       - Lab2 header file.
*       - It contains Hash Queue structure, timeval functions, ... etc
*
*/

#ifndef _LAB2_HEADER_H
#define _LAB2_HEADER_H

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#define HASH_SIZE		13
#define LAB2_SUCCESS		0
#define LAB2_ERROR		-1

/*
 * If You need to more functions or vaiable
 * Declare functions or struct in lab2_sync_types.h
 */

/* Variable that contains number of data */
int target;

/* Strucuture for thread, hash, queue */
typedef struct threadArg {
	int node_count;
	int thread_num;
	int thread_order;
} thread_arg; 

typedef struct q_node {
	struct q_node *prev;
	int data;
	struct q_node *next;
} queue_node;

queue_node *front;
queue_node *rear;

typedef struct hash_list {
	struct hash_list *next;
	struct q_node *q_loc;
} hlist_node;

hlist_node *hashlist[HASH_SIZE];

/* Lab2 Hash and Queue init functions */
void init_queue();
void init_hlist_node();

/* Lab2 Hash function */
int hash(int val);
int value_exist(int val);

/* Lab2 Hash Queue functions for single-thread */
void enqueue(int data);
int dequeue();

/* Lab2 Hash Queue functions for Coarse-grained */
void enqueue_cg(int data);
int dequeue_cg();

/* Lab2 Queue functions for fine-grained */
void enqueue_fg(int data);
int dequeue_fg();

/*Lab2 Hash Queue functions */
void hash_queue_insert_by_target(int val);
void hash_queue_delete_by_target(int val);
void producer_hash_queue_insert_by_target(int val);
int consumer_hash_queue_delete_by_target(int val);

/* Lab2_timeval.c related function */
double get_timeval(struct timeval *tv_start, struct timeval *tv_end);

#endif /* LAB2_HEADER_H*/

