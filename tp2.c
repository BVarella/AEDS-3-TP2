#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "process_input.h"

int main() {
	
	int n, m, max_keys, source_vertex, exit_vertex;

	read_input_parameters(&n, &m, &max_keys);

	vertex_node** input_matrix = (vertex_node** ) malloc(n * sizeof(vertex_node* ));
	for(int i = 0; i < n; ++i){
		input_matrix[i] = (vertex_node* ) malloc(m * sizeof(vertex_node));
	}

	read_map(input_matrix, n, m, &source_vertex, &exit_vertex);

	graph_t* graph = graph_create(n*m, source_vertex, exit_vertex);

	create_graph_from_map(graph, n, m, input_matrix);

	for(int i = 0; i < n; ++i){
		free(input_matrix[i]);
	}
	free(input_matrix);

	start_bfs(graph, max_keys);

	print_shortest_distance(graph);

	graph_destroy(graph);

	return 0;
}
