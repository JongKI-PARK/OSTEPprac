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

/*
 * TODO
 *  Implement function which init queue nodes for front and rear
 *  ( refer to the ./include/lab2_sync_types.h for front and rear nodes)
 
void init_queue(queue_struct *q) {
	q->front = q->rear = NULL;
	pthread_mutex_init(&q->cg_lock, NULL);
	pthread_mutex_init(&q->fg_lock, NULL);
}
*/

void init_queue() {
	front = rear = NULL;
	pthread_mutex_init(&cg_lock, NULL);
	pthread_mutex_init(&fg_lock, NULL);
}

/*
 * TODO
 *  Implement function which add new_node at next rear node
 *
 *  @param queue_node *new_node		: Node which you need to insert at queue.
 */
void enqueue(queue_struct *q, int data) {
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
	assert(new_node !=NULL);
	new_node->data = data;
	
	if(q->front == NULL){
		new_node->next = new_node;
		new_node->prev = new_node;
		q->front = new_node;
		q->rear = new_node;
	}
	else {
		new_node->next = q->rear->next;
		q->front->prev = new_node;

		q->rear->next = new_node;
		new_node->prev = q->rear;

		q->rear = new_node;
	}
}
//********************2nd version
void enqueue(int data) {
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
	assert(new_node != NULL);
	new_node->data = data;

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
}

/*
 * TODO
 *  Implement function which add new_node at next rear node
 *
 *  @param queue_node *new_node		: Node which you need to insert at queue in coarse-grained manner.
 */
void enqueue_cg(queue_struct *q, int data) {
	pthread_mutex_lock(&q->cg_lock);
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));

	if(new_node == NULL){
		perror("malloc");
		pthread_mutex_unlock(&q->cg_lock);
		exit(1);
	}
	new_node->data = data;

	if(q->front == NULL) {
		new_node->next = new_node;
		new_node->prev = new_node;
		q->front = q->rear = new_node;
	}
	else {
	
		new_node->next = q->rear->next;
		q->front->prev = new_node;

		q->rear->next = new_node;
		new_node->prev = q->rear;

		q->rear = new_node;
	}
	pthread_mutex_unlock(&q->cg_lock);
}

/*
 * TODO
 *  Implement function which add new_node at next rear node
 *
 *  @param queue_node *new_node		: Node which you need to insert at queue in fine-grained manner.
 */
void enqueue_fg(queue_struct *q, int data) {
	queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
	if(new_node == NULL) { 
		perror("malloc");
		exit(1);
	}

	new_node->data = data;
	
	pthread_mutex_lock(&q->fg_lock, NULL);
	if(q->front == NULL) {
		new_node->next = new_node->prev = new_node;
		q->front = q->rear = new_node;
	}
	else {
		new_node->next = q->rear->next;
		q->front->prev = new_node;

		q->rear->next = new_node;
		new_node->prev = q->rear;

		q->rear = new_node;
	}
	pthread_mutex_unlock(&q->fg_lock);
}

/*
 * TODO
 *  Implement function which delete del_node at location that contains target key
 *
 *  @param queue_node *del_node		: Node which you need to delete at queue.
 */
int dequeue(queue_struct *q) {
	if(q->front == NULL)
		return -1;
	
	queue_node *delete = q->front;
	int data = delete->data;
	if(q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		q->rear->next = new_head;
	}
	free(delete);
	return data;
}

int dequeue() {
	if(front == NULL)
		return -1;
	
	queue_node *delete = front;
	int data = delete->data;
	if(front = rear) {
		front = rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->next;
		new_head->prev = delete->prev;
		rear->next = new_head;
	}
	free(delete);
	return data;
}

/*
 * TODO
 *  Implement function which delete del_node at location that contains target key
 *
 *  @param queue_node *del_node		: Node which you need to delete at queue in coarse-grained manner.
 */
int dequeue_cg(queue_struct *q) {
	pthread_mutex_lock(&q->cg_lock, NULL);
	if(q->front == q->rear) {
		pthread_mutex_unlock(&q->cg_lock);
		return -1;
	}

	queue_node *delete = q->front;
	int data = delete->data;
	if(q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		q->rear->next = new_head;
	}
	free(delete);
	pthread_mutex_unlock(&q->cg_lock);
	return data;
}

/*
 * TODO
 *  Implement function which delete del_node at location that contains target key
 *
 *  @param queue_node *del_node		: Node which you need to delete at queue in fine-grained manner.
 */
int dequeue_fg(queue_struct *q) {
	if(q->front == q->rear) {
		return -1;
	}

	queue_node *delete = q->front;
	int data = delete->data;

	pthread_mutex_lock(&q->fg_lock, NULL);

	if(q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		q->rear->next = new_head;
	}
	pthread_mutex_unlock(&q->fg_lock);
	free(delete);
	return data;
}

/*
 * TODO
 *  Implement function which init hashlist(same as hashtable) node.
 */
void init_hlist_node(hlist_node *hashlist[]) {
	hlist_node *null_node[HASH_SIZE];
	for(int i = 0 ; i < HASH_SIZE ; i++) {
		null_node[i]->q_loc = NULL;
		null_node[i]->next = NULL;
		hashlist[i] = null_node[i];
	}
}

int hash(int val) {
	return val % HASH_SIZE;
}

int value_exist(hlist_node *hashlist[], queue_struct *q, int val) {
	int index = hash(val);
	hlist_node *correspond = hashlist[index];
	while(correspond->q_loc->data != val) {
		if(correspond == NULL)
			return 0;
		correspond = correspond->next;
	}
	return 1;
}

void hash_queue_insert_by_target(hlist_node *hashlist[], queue_struct *q, int val) {
	if(value_exist(&hashlist[], &q, val) == 1)
		exit(0);

	hlist_node *new_hnode = (hlist_node*)malloc(sizeof(hlist_node));
	if(new_hnode == NULL) {
		perror("malloc");
		exit(1);
	}

	enqueue(&q, val);
	new_hnode->q_loc = q->rear;
	new_hnode->next = NULL;

	int index = hash(val);
	hlist_node *last_node = hashlist[index];
	while(last_node->next != NULL)
		last_node = last_node->next;
	
	last_node->next = new_hnode;
}

void hash_queue_insert_by_target_cg(hlist_node *hashlist[], queue_struct *q, int val) {
	if(value_exist(&hashlist[], &q, val) == 1)
		exit(0);

	pthread_mutex_lock(&hcg_lock, NULL);

	hlist_node *new_hnode = (hlist_node*)malloc(sizeof(hlist_node));
	if(new_hnode == NULL) {
		perror("malloc");
		pthread_mutex_unlock(&hcg_lock);
		exit(1);
	}

	enqueue(&q, val);
	new_hnode->q_loc = q->rear;
	new_hnode->next = NULL;

	int index = hash(val);
	hlist_node *last_node = hashlist[index];
	while(last_node->next != NULL)
		last_node = last_node->next;

	last_node->next = new_hnode;

	pthread_mutex_unlock(&hcg_lock);
}

void hash_queue_insert_by_target_fg(hlist_node *hashlist[], queue_struct *q, int val) {
	if(value_exist(&hashlist[], &q, val) == 1)
		exit(0);

	hlist_node *new_hnode = (hlist_node*)malloc(sizeof(hlist_node));
	if(new_hnode == NULL) {
		perror("malloc");
		exit(1);
	}
	
	int index = hash(val);
	hlist_node *last_node = hashlist[index];
	new_hnode->next = NULL;

	pthread_mutex_lock(&hfg_lock, NULL);
	enqueue(&q, val);
	new_hnode->q->loc = q->rear;
	
	while(last_node->next != NULL) 
		last_node = last_node->next;

	last_node->next = new_hnode;
	pthread_mutex_unlock(&hfg_lock);
}

void hash_queue_delete_by_target(hlist_node *hashlist[], queue_struct *q, int val) {
	int status = value_exist(&hashlist[], &q, val);
	if(status == 0)
		exit(0);
	
	int index = hash(val);
	hlist_node *target = hashlist[index];
	while(target->q_loc->data != val)
		target = target->next;

	hlist_node *target_front = hashlist[index];
	while(target_front->next != target)
		target_front = target_front->next;

	target_front->next = target->next;

	if(q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		if(target->q_loc == q->front)
			dequeue(&q);
		else {
			queue_struct *prev_node, *next_node;
			prev_node = target->prev;
			next_node = target->next;

			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	free(target);
}

void hash_queue_delete_by_target_cg(hlist_node *hashlist[], queue_struct *q, int val) {
	pthread_mutex_lock(&hcg_lock, NULL);
	pthread_mutex_lock(&q->cg_lock, NULL);

	int status = value_exist(&hashlist[], &q, val);
	if(status == 0) {
		pthread_mutex_unlock(&hcg_lock);
		pthread_mutex_unlock(&q->cg_lock);
		exit(0);
	}
	int index = hash(val);
	hlist_node *target = hashlist[index];
	while(target->q_loc->data != val)
		target = target->next;

	hlist_node *target_front = hashlist[index];
	while(target_front->next = target)
		target_front = target_front->next;
	
	target_front->next = target->next;
	if(q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		if(target == q->front)
			dequeue(&q);
		else {
			queue_struct *prev_node = target->prev;
			queue_struct *next_node = target->next;
			
			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	free(target);
	pthread_mutex_unlock(&hcg_lock);
	pthread_mutex_unlock(&q->cg_lock);
}

void hash_queue_delete_by_target_fg(hlist_node *hashlist[], queue_struct *q, int val) {
	pthread_mutex_lock(&hfg_lock, NULL);

	int status = value_exist(&hashlist[], &q, val);
	if(status == 0) {
		pthread_mutex_unlock(&hfg_lock);
		exit(0);
	}
	int index = hash(val);
	hlist_node *target = hashlist[index];
	while(target->q_loc->data != val)
		target = target->next;

	hlist_node *target_front = hashlist[index];
	while(target_front->next = target)
		target_front = target_front->next;

	target_front->next = target->next;

	pthread_mutex_unlock(&hfg_lock);
	pthread_mutex_lock(&q->fg_lock, NULL);
	if(q->front == q->rear) {
		q->front = q->rear = NULL;
	}
	else {
		if(target == q->front)
			dequeue(&q);
		else {

			queue_struct *prev_node = target->prev;
			queue_struct *next_node = target->next;
	
			prev_node->next = next_node;
			next_node->prev = prev_node;
		}
	}
	pthread_mutex_unlock(&q->fg_lock);
	free(target);
}

