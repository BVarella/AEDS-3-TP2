#ifndef GRAPH_H
#define GRAPH_H

typedef struct adj_list_node_t {
	int destination;	
	struct adj_list_node_t* next;
} adj_list_node_t;

typedef struct adj_list_t {
	adj_list_node_t* head;
	int level;
	int color; // 0 = white, 1 = gray, 2 = black
	int status; // 0 = free space, 1 = key, 2 = door, 3 = wormhole, 4 = wall
	char code; // Char that represents key or door
	int wormhole_position;
} adj_list_t;

typedef struct graph_t {
	adj_list_t* array;
	int vertices;
	int source_vertex;
	int exit_vertex;
} graph_t;

//Allocate graph
graph_t* graph_create(int vertices, int source_vertex, int exit_vertex);

//Free graph
void graph_destroy(graph_t* graph);

//Add directed edge to the graph
void add_edge(graph_t* graph, int source, int destination);

//Start BFS
void start_bfs(graph_t* graph, int max_keys);

//Print level.exit_vertex
void print_shortest_distance(graph_t* graph);

#endif
