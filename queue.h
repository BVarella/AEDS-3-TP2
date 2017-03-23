#ifndef LIST_H
#define LIST_H

typedef struct data_t {
	int vertex;
} data_t; 

typedef struct node_t {
	data_t data;
	struct node_t *next;
} node_t; 

typedef struct queue_t {
	node_t *head;
} queue_t; 

//Allocate queue
queue_t *queue_create(); 

//Free queue
void queue_destroy(queue_t *queue); 

//Enqueue
node_t *enqueue(queue_t *queue, data_t data); 

//Remove element (used to destroy queue)
void queue_remove(queue_t *queue, node_t *node);

//Dequeue
void dequeue(queue_t *queue); 

//Returns the element to be dequeued
int queue_front(queue_t *queue);

//Used to destroy queue
void queue_make_empty(queue_t *queue); 

//Check if queue is empty
int queue_empty(queue_t *queue);

#endif
