#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t *queue_create() {
	
	queue_t *queue = malloc(sizeof(queue_t));
	if(!queue){
		return NULL;
	}
	
	queue->head = NULL; 
	
	return queue;
}

void queue_destroy(queue_t *queue) {
	
	if(!queue){
		return;
	}
	
	queue_make_empty(queue);
	free(queue);
}

static node_t* new_node(data_t data) {

	node_t* node = (node_t*)malloc(sizeof(node_t));
	if(!node){
		return NULL;
	}
	
	node->data = data;
	node->next = NULL;

	return node;
}

node_t *enqueue(queue_t *queue, data_t data){

	node_t* new;

	if(!queue){
		return NULL;
	}
	
	new = new_node(data); 
	if(!new){
		return NULL;
	}
	
	node_t *current = queue->head;
	if(current){
		while(current->next != NULL){ 
			current = current->next;
		}
		current->next = new;
		new->next = NULL;
	} else {
		queue->head = new;
		new->next = NULL;
	  }

	return new;
}

void queue_remove(queue_t *queue, node_t *node) {
	
	node_t *current;

	if(!queue || !node){
		return;
	}
	
	current = queue->head;
	if(!current){
		return;
	} else if(current == node){
		queue->head = current->next;
		free(node);
		return;
	  }

	while(current->next != node && current->next != NULL){
		current = current->next;
	}

	if(!current->next){
		return;
	}
	
	current->next = node->next;
	free(node);
}

void dequeue(queue_t *queue) {

	if(!queue){
		return;
	}
	
	queue_remove(queue, queue->head);
}

void queue_make_empty(queue_t *queue) {
	
	if(!queue){
		return;
	}
	while(queue->head){
		dequeue(queue);
	}
}

int queue_front(queue_t *queue){

	if(!queue){
		exit(EXIT_FAILURE);
	}

	return queue->head->data.vertex;
}

int queue_empty(queue_t *queue){

	if(!queue){
		exit(EXIT_FAILURE);
	}

	if(queue->head == NULL){
		return 1;
	}
	else return 0;
}
