/*
*   DKU Operating System Lab
*           Lab2 (Hash Queue Lock Problem)
*           Student id : 32181827
*           Student name : Park jongki
*
*   lab2_sync.c :
*       - lab2 main file.
*		- Thread-safe Hash Queue Lock code
*		- Coarse-grained, fine-grained lock code
*       - Must contains Hash Queue Problem function's declations.
*
*   Implement thread-safe Hash Queue for coarse-grained verison and fine-grained version.
*/

#include <aio.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab2_sync_types.h"

extern queue_node *front;
extern queue_node *rear;
extern pthread_mutex_t cg_lock, fg_lock;

extern hlist_node *hashlist[HASH_SIZE];
extern pthread_mutex_t hcg_lock, hfg_lock;


void init_queue() {
	front = rear = NULL;
	pthread_mutex_init(&cg_lock, NULL);
	pthread_mutex_init(&fg_lock, NULL);
}

void enqueue(int data) {
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
	assert(new_node != NULL);
	new_node->data = data;

	if(front == NULL) {
		new_node->next = new_node;
		new_node->prev = new_node;
		front = rear = new_node;
	}
	else {
		new_node->next = rear->next;
		front->prev = new_node;

		rear->next = new_node;
		new_node->prev = rear;

		rear = new_node;
	}
}

void enqueue_cg(int data) {
	pthread_mutex_lock(&cg_lock);
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));

	if(new_node == NULL){
		perror("malloc");
		pthread_mutex_unlock(&cg_lock);
		exit(1);
	}
	new_node->data = data;

	if(front == NULL) {
		new_node->next = new_node;
		new_node->prev = new_node;
		front = rear = new_node;
	}
	else {
		new_node->next = rear->next;
		front->prev = new_node;

		rear->next = new_node;
		new_node->prev = rear;

		rear = new_node;
	}
	pthread_mutex_unlock(&cg_lock);
}

void enqueue_fg(int data) {
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
	if(new_node == NULL) { 
		perror("malloc");
		exit(1);
	}

	new_node->data = data;
	
	pthread_mutex_lock(&fg_lock);
	if(front == NULL) {
		new_node->next = new_node->prev = new_node;
		front = rear = new_node;
	}
	else {
		new_node->next = rear->next;
		front->prev = new_node;

		rear->next = new_node;
		new_node->prev = rear;

		rear = new_node;
	}
	pthread_mutex_unlock(&fg_lock);
}

int dequeue() {
	if(front == NULL)
		return -1;
	
	queue_node *delete = front;
	int data = delete->data;
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		rear->next = new_head;
		front = new_head;
	}
	free(delete);
	return data;
}

int dequeue_cg() {
	pthread_mutex_lock(&cg_lock);
	if(front == rear) {
		pthread_mutex_unlock(&cg_lock);
		return -1;
	}

	queue_node *delete = front;
	int data = delete->data;
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		rear->next = new_head;
		front = new_head;
	}
	free(delete);
	pthread_mutex_unlock(&cg_lock);
	return data;
}

int dequeue_fg() {
	if(front == rear) {
		return -1;
	}

	queue_node *delete = front;
	int data = delete->data;

	pthread_mutex_lock(&fg_lock);

	if(front == rear) {
		front = rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		rear->next = new_head;
		front = new_head;
	}
	pthread_mutex_unlock(&fg_lock);
	free(delete);
	return data;
}

void init_hlist_node() {
	for(int i = 0 ; i < HASH_SIZE ; i++) {
		hashlist[i] = (hlist_node*)malloc(sizeof(hlist_node));
		memset(hashlist[i], 0, sizeof(hlist_node));
	}
	pthread_mutex_init(&hcg_lock, NULL);
	pthread_mutex_init(&hfg_lock, NULL);
}

int hash(int val) {
	return val % HASH_SIZE;
}

//if value exsists, return 1
int value_exist(int val) {
	int index = hash(val);
	hlist_node *correspond = hashlist[index];

	while(correspond != NULL) {
		if(correspond->q_loc == NULL || correspond->q_loc->data != val)
			correspond = correspond->next;
		else {
			return 1;
		}
	}
	return 0;
}

void hash_queue_insert_by_target(int val) {
	if(value_exist(val) == 1)
		exit(0);

	hlist_node *new_hnode = (hlist_node*)malloc(sizeof(hlist_node));
	if(new_hnode == NULL) {
		perror("malloc");
		exit(1);
	}

	enqueue(val);
	new_hnode->q_loc = rear;
	new_hnode->next = NULL;

	int index = hash(val);
	hlist_node *last_node = hashlist[index];
	while(last_node->next != NULL)
		last_node = last_node->next;
	
	last_node->next = new_hnode;
}

void hash_queue_insert_by_target_cg(int val) {
	if(value_exist(val) == 1)
		exit(0);

	pthread_mutex_lock(&hcg_lock);
	hlist_node *new_hnode = (hlist_node*)malloc(sizeof(hlist_node));
	if(new_hnode == NULL) {
		perror("malloc");
		pthread_mutex_unlock(&hcg_lock);
		exit(1);
	}

	enqueue(val);
	new_hnode->q_loc = rear;
	new_hnode->next = NULL;

	int index = hash(val);
	hlist_node *last_node = hashlist[index];
	while(last_node->next != NULL)
		last_node = last_node->next;

	last_node->next = new_hnode;
	
	pthread_mutex_unlock(&hcg_lock);
}

void hash_queue_insert_by_target_fg(int val) {
	if(value_exist(val) == 1)
		exit(0);

	hlist_node *new_hnode = (hlist_node*)malloc(sizeof(hlist_node));
	if(new_hnode == NULL) {
		perror("malloc");
		exit(1);
	}
	
	int index = hash(val);
	hlist_node *last_node = hashlist[index];
	new_hnode->next = NULL;

	pthread_mutex_lock(&hfg_lock);
	enqueue(val);
	new_hnode->q_loc = rear;
	
	while(last_node->next != NULL) 
		last_node = last_node->next;

	last_node->next = new_hnode;
	pthread_mutex_unlock(&hfg_lock);
}

void hash_queue_delete_by_target(int val) {
	int status = value_exist(val);
	if(status == 0)
		exit(0);
	
	int index = hash(val);
	hlist_node *target = hashlist[index];
	while(target->q_loc == NULL || target->q_loc->data != val)
		target = target->next;

	hlist_node *target_front = hashlist[index];
	while(target->q_loc == NULL || target_front->next != target)
		target_front = target_front->next;

	target_front->next = target->next;

	if(front == rear) {
		front = rear = NULL;
	}
	else {
		if(target->q_loc == front)
			dequeue();
		else {
			queue_node *prev_node, *next_node;
			prev_node = target->q_loc->prev;
			next_node = target->q_loc->next;

			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	free(target);
}

void hash_queue_delete_by_target_cg(int val) {
	pthread_mutex_lock(&hcg_lock);

	int status = value_exist(val);
	if(status == 0) {
		pthread_mutex_unlock(&hcg_lock);
		exit(0);
	}
	int index = hash(val);
	hlist_node *target = hashlist[index];
	while(target->q_loc == NULL || target->q_loc->data != val)
		target = target->next;

	hlist_node *target_front = hashlist[index];
	while(target->q_loc == NULL || target_front->next != target)
		target_front = target_front->next;
	
	target_front->next = target->next;
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		if(target->q_loc == front)
			dequeue();
		else {
			queue_node *prev_node = target->q_loc->prev;
			queue_node *next_node = target->q_loc->next;
			
			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	free(target);
	pthread_mutex_unlock(&hcg_lock);
}

void hash_queue_delete_by_target_fg(int val) {
	pthread_mutex_lock(&hfg_lock);

	int status = value_exist(val);
	if(status == 0) {
		pthread_mutex_unlock(&hfg_lock);
		exit(0);
	}
	int index = hash(val);
	hlist_node *target = hashlist[index];
	while(target->q_loc == NULL || target->q_loc->data != val)
		target = target->next;

	hlist_node *target_front = hashlist[index];
	while(target->q_loc == NULL || target_front->next == target)
		target_front = target_front->next;

	target_front->next = target->next;

	pthread_mutex_unlock(&hfg_lock);
	pthread_mutex_lock(&fg_lock);
	if(front == rear) {
		front = rear = NULL;
	}
	else {
		if(target->q_loc == front)
			dequeue();
		else {

			queue_node *prev_node = target->q_loc->prev;
			queue_node *next_node = target->q_loc->next;
	
			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	pthread_mutex_unlock(&fg_lock);
	free(target);
}

