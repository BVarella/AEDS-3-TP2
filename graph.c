#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "graph.h"
#include "queue.h"

graph_t* graph_create(int vertices, int source_vertex, int exit_vertex){
	
	graph_t* graph = (graph_t *) malloc(sizeof(graph_t));
	graph->vertices = vertices;
	graph->source_vertex = source_vertex;
	graph->exit_vertex = exit_vertex;

	graph->array = (adj_list_t *) malloc(vertices * sizeof(adj_list_t));

	for(int i = 0; i < vertices; ++i){
		graph->array[i].head = NULL;
		graph->array[i].level = INT_MAX;
		graph->array[i].color = 0;
		graph->array[i].status = -1;
		graph->array[i].code = '-';
		graph->array[i].wormhole_position = -1;
	}

	return graph;
}

void graph_destroy(graph_t* graph){
	
	if(graph){
		if(graph->array){
			for (int i = 0; i < graph->vertices; ++i){
				adj_list_node_t* current = graph->array[i].head;
				while(current){
					adj_list_node_t* tmp = current;
					current = current->next;
					free(tmp);
				}
			}
			free(graph->array);
		}
		free(graph);
	}
}

static adj_list_node_t* new_adj_list_node(int destination){

	adj_list_node_t* new_node = (adj_list_node_t *) malloc(sizeof(adj_list_node_t));
	new_node->destination = destination;
	new_node->next = NULL;

	return new_node;
}

void add_edge(graph_t* graph, int source, int destination){

	adj_list_node_t* new_node = new_adj_list_node(destination);
	new_node->next = graph->array[source].head;
	graph->array[source].head = new_node;
}

static void bfs(graph_t* graph, int source_vertex, char* keys, int max_keys){
	
	for(int i = 0; i < graph->vertices; ++i){
		graph->array[i].color = 0;
	}

	graph->array[source_vertex].color = 1;

	queue_t* queue = queue_create();
	data_t vertex_to_enqueue;
	vertex_to_enqueue.vertex = source_vertex;
	enqueue(queue, vertex_to_enqueue);

	while(!queue_empty(queue)){
		int u = queue_front(queue);
		dequeue(queue);

		adj_list_node_t* u_vertex;
		u_vertex = graph->array[u].head;

		while(u_vertex){
			if(graph->array[u_vertex->destination].color == 0){
				//Key
				if(graph->array[u_vertex->destination].status == 1){
					char key = toupper(graph->array[u_vertex->destination].code);
					for(int i = 0; i < max_keys; ++i){
						if(keys[i] == '\0'){
							keys[i] = key;
							break;
						}
					}
					graph->array[u_vertex->destination].level = graph->array[u].level + 1;
					bfs(graph, u_vertex->destination, keys, max_keys);
					for(int i = 0; i < max_keys; ++i){
						if(keys[i] == key){
							keys[i] = '\0';
							break;
						}
					}
				}
				//Door
				if(graph->array[u_vertex->destination].status == 2){
					for(int i = 0; i < max_keys; ++i){
						if(keys[i] == graph->array[u_vertex->destination].code){
							if((graph->array[u].level + 1) < graph->array[u_vertex->destination].level){
								graph->array[u_vertex->destination].level = graph->array[u].level + 1;
								vertex_to_enqueue.vertex = u_vertex->destination;
								enqueue(queue, vertex_to_enqueue);
							}
							break;
						}
					}
				}
				//Wormhole
				if(graph->array[u_vertex->destination].status == 3){
					graph->array[u_vertex->destination].status = 0;
					if (graph->array[u].level+1 < graph->array[graph->array[u_vertex->destination].wormhole_position].level){
						graph->array[graph->array[u_vertex->destination].wormhole_position].level = graph->array[u].level+1;
					}
					if (graph->array[u_vertex->destination].wormhole_position != graph->exit_vertex){
						bfs(graph, graph->array[u_vertex->destination].wormhole_position, keys, max_keys);
					}
					graph->array[u_vertex->destination].status = 3;	
				}
				//Free space
				if(graph->array[u_vertex->destination].status == 0){
					graph->array[u_vertex->destination].color = 1;
					if((graph->array[u].level + 1) < graph->array[u_vertex->destination].level){
						graph->array[u_vertex->destination].level = graph->array[u].level + 1;
						vertex_to_enqueue.vertex = u_vertex->destination;
						enqueue(queue, vertex_to_enqueue);
					}
				}
				//Wall
				if(graph->array[u_vertex->destination].status == 4){
					continue;
				}
			}
			u_vertex = u_vertex->next;
		}
		graph->array[u].color = 2;
	}
	queue_destroy(queue);
}

void start_bfs(graph_t* graph, int max_keys){

	graph->array[graph->source_vertex].level = 0;
	graph->array[graph->source_vertex].color = 1; 

	char* keys = (char* ) calloc(max_keys, sizeof(char));

	bfs(graph, graph->source_vertex, keys, max_keys);

	free(keys);
}

void print_shortest_distance(graph_t* graph){
	
	if (graph->array[graph->exit_vertex].level != INT_MAX){
		printf("%d\n", graph->array[graph->exit_vertex].level);
	}
	else{
		printf("-1\n");
	}
}
