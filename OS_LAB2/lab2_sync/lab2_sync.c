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

extern int target;
extern queue_node *front;
extern queue_node *rear;
extern pthread_mutex_t cg_lock, fg_lock;

extern hlist_node *hashlist[HASH_SIZE];
extern pthread_mutex_t hash_lock;;


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
		front = NULL;
		rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = rear;
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
	pthread_mutex_init(&hash_lock, NULL);
}

void hash_queue_insert_by_target(int val) {
	
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

void producer_hash_queue_insert_by_target(int val) {
	 
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

void hash_queue_delete_by_target(int val) {

        int index = hash(val);
        hlist_node *target = hashlist[index];
	while(target->q_loc == NULL || target->q_loc->data != val)
        	target = target->next;
	
        hlist_node *target_front = hashlist[index];
	
        while(target->q_loc == NULL || target_front->next != target)
        	target_front = target_front->next;

        target_front->next = target->next;
	
        if(target->q_loc == front)
		dequeue();
        else {
         	queue_node *prev_node = target->q_loc->prev;
                queue_node *next_node = target->q_loc->next;

                prev_node->next = next_node;
                next_node->prev = prev_node;
		
		if(target->q_loc == rear)
			rear = prev_node;
	}
	free(target);
}

int consumer_hash_queue_delete_by_target(int val) {
	
        int index = hash(val);
	if(index == -1) {
		index = hash(front->data);
		val = front->data;
	}

        hlist_node *target = hashlist[index];
        while(target->q_loc == NULL || target->q_loc->data != val) {
		target = target->next;
	}
	
        hlist_node *target_front = hashlist[index];

        while(target->q_loc == NULL || target_front->next != target)
                target_front = target_front->next;

        target_front->next = target->next;
	
        if(target->q_loc == front) {
                return dequeue();
			
	}		
	else {
                queue_node *prev_node = target->q_loc->prev;
                queue_node *next_node = target->q_loc->next;

               	prev_node->next = next_node;
               	next_node->prev = prev_node;
			
		if(target->q_loc == rear) {
			rear = prev_node;
		}
        }
        free(target);
	return 0;

}

