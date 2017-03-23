#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include "graph.h"

typedef struct vertex_node{
	int vertex;
	int status;
	char code;
	int wormhole_position;
} vertex_node;

//Read input parameters (N, M, T)
void read_input_parameters(int* n, int* m, int* max_keys);

//Used to avoid problems with old input
void clear_stdin();

//Reads input and save to aux matrix (input_matrix)
void read_map(vertex_node** input_matrix, int n, int m, int* source_vertex, int* exit_vertex);

//Create graph from aux matrix (input_matrix)
void create_graph_from_map(graph_t* graph, int n, int m, vertex_node** input_matrix);

#endif
