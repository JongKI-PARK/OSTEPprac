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

/*
 * TODO
 *  Implement function which init queue nodes for front and rear
 *  ( refer to the ./include/lab2_sync_types.h for front and rear nodes)
 */
void init_queue(queue_struct *q) {
	q->front = q->rear = NULL;
	pthread_mutex_init(&q->cg_lock, NULL);
	pthread_mutex_init(&q->fg_lock, NULL);
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
	
	queue_node *delete = q->head;
	int data = delete->data;
	if(q->front == q->rear) {
		q->front = q->rear = NULL;
		free(delete);
		return data;
	}
	else {
		queue_node *new_head = delete->next;

		new_head->prev = delete->prev;
		q->rear->next = new_head;

		free(delete);
		return data;
	}
}

/*
 * TODO
 *  Implement function which delete del_node at location that contains target key
 *
 *  @param queue_node *del_node		: Node which you need to delete at queue in coarse-grained manner.
 */
int dequeue_cg(queue_struct *q) {
	pthread_mutex_lock(&q->cg_lock, NULL);
	if(q->head == q->rear)
		return -1;

	queue_node *delete = q->head;
	queue_node *new_head = delete->next;
	int data = delete->data;

	new_head->prev = delete->data;
	q->rear->next = new_head;
	
	pthread_mutex_unlock(&q->cg_lock, NULL);
	free(delete);
}

/*
 * TODO
 *  Implement function which delete del_node at location that contains target key
 *
 *  @param queue_node *del_node		: Node which you need to delete at queue in fine-grained manner.
 */
int dequeue_fg(queue_struct *q) {

	queue_node *delete = q->head;
	int data = delete->head;
	
	pthread_mutex_lock(&q->fg_lock, NULL);
	if(q->head == q->rear)
		return -1;

	queue_node *new_head = delete->next;

	new_head->prev = delete->data;
	q->rear->next = new_head;

	pthread_mutex_unlock(&q->fg_lock);
	free(delete);
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

/*
 * TODO
 *  Implement function which calculate hash value with modulo operation.
 */
int hash(int val) {
	return val % HASH_SIZE;
}

/*
 * TODO
 *  Implement function which insert the resilt of finding the location 
 *  of the bucket using value to the entry and hashtable
 *
 *  @param hlist_node *hashtable		: A pointer variable containing the bucket
 *  @param int val						: Data to be stored in the queue node
 */
void hash_queue_add(hlist_node *hashlist[], queue_struct *q, int val) {
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

/*
 * TODO
 *  Implement function which insert the resilt of finding the location 
 *  of the bucket using value to the entry and hashtable
 *
 *  @param hlist_node *hashtable		: A pointer variable containing the bucket
 *  @param int val						: Data to be stored in the queue node
 */
void hash_queue_add_cg(hlist_node *hashlist[], queue_strut *q, int val) {
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

/*
 * TODO
 *  Implement function which insert the resilt of finding the location 
 *  of the bucket using value to the entry and hashtable
 *
 *  @param hlist_node *hashtable		: A pointer variable containing the bucket
 *  @param int val						: Data to be stored in the queue node
 */
void hash_queue_add_fg(hlist_node *hashlist[], queue_struct *q, int val) {
	hlist_node *new_node = (hlist_node*)malloc(sizeof(hlist_node));
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

/*
 * TODO
 *  Implement function which check if the data(value) to be stored is in the hashtable
 *
 *  @param int val						: variable needed to check if data exists
 *  @return								: status (success or fail)
 */
int value_exist(hlist_node *hashlist[], int val) {
	hlist_node *correspond = (hlist_node*)malloc(sizeof(hlist_node));

	int index = hash(val);
	correspond = hashlist[index];
	while(correspond->q_loc->data != val){
		if(correspond == NULL)
			return -1;
		correspond = correspond->next;
	}
	free(correspond);
	return 0;
}

/*
 * TODO
 *  Implement function which find the bucket location using target
 */
void hash_queue_insert_by_target(int val) {
	
}

/*
 * TODO
 *  Implement function which find the bucket location using target
 */
void hash_queue_insert_by_target_cg() {
	// You need to implement hash_queue_insert_by_target_cg function.
}

/*
 * TODO
 *  Implement function which find the bucket location using target
 */
void hash_queue_insert_by_target_fg() {
	// You need to implement hash_queue_insert_by_target_fg function.
}

/*
 * TODO
 *  Implement function which find the bucket location and stored data
 *  using target and delete node that contains target
 */
void hash_queue_delete_by_target() {
	// You need to implement hash_queue_delete_by_target function.
}

/*
 * TODO
 *  Implement function which find the bucket location and stored data
 *  using target and delete node that contains target
 */
void hash_queue_delete_by_target_cg() {
	// You need to implement hash_queue_delete_by_target_cg function.
}

/*
 * TODO
 *  Implement function which find the bucket location and stored data
 *  using target and delete node that contains target
 */
void hash_queue_delete_by_target_fg() {
	// You need to implement hash_queue_delete_by_target_fg function.
}

