#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process_input.h"

#define LINE_SIZE 128

void read_input_parameters(int* n, int* m, int* max_keys){

	if(scanf("%d %d %d", n, m, max_keys) != 3){
		exit(EXIT_FAILURE);
	}
}

void clear_stdin(){

	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void read_map(vertex_node** input_matrix, int n, int m, int* source_vertex, int* exit_vertex){

	clear_stdin();

	char line[LINE_SIZE];
	char* pch;
	int temp_wormhole;
	int wormhole_position_x;
	int wormhole_position_y;

	int num_linhas = n-1;

	int current_vertex;
	for(int i = 0; i < n; ++i){
		if(fgets(line, LINE_SIZE, stdin) != NULL){
			current_vertex = m * (num_linhas);
			pch = strtok(line, " ");
			for(int j = 0; j < m; ++j){
				// Free space
				if(pch[0] == '.'){ 
					input_matrix[i][j].vertex = current_vertex;
					input_matrix[i][j].status = 0;
					input_matrix[i][j].code = '-';
					input_matrix[i][j].wormhole_position = -1;
				}
				// Wall
				else if(pch[0] == '#'){ 
					input_matrix[i][j].vertex = current_vertex;
					input_matrix[i][j].status = 4;
					input_matrix[i][j].code = '-';
					input_matrix[i][j].wormhole_position = -1;
				}
				// Key
				else if(pch[0] == 'c' || pch[0] == 'd' || pch[0] == 'h' || pch[0] == 's'){ 
					input_matrix[i][j].vertex = current_vertex;
					input_matrix[i][j].status = 1;
					input_matrix[i][j].code = pch[0];
					input_matrix[i][j].wormhole_position = -1;
				}
				// Door
				else if(pch[0] == 'C' || pch[0] == 'D' || pch[0] == 'H' || pch[0] == 'S'){ 
					input_matrix[i][j].vertex = current_vertex;
					input_matrix[i][j].status = 2;
					input_matrix[i][j].code = pch[0];
					input_matrix[i][j].wormhole_position = -1;
				}
				// Wormhole
				else if(pch[0] >= 48 && pch[0] <= 57){ 
					input_matrix[i][j].vertex = current_vertex;
					temp_wormhole = atoi(pch);
					wormhole_position_y = temp_wormhole % 10;
					temp_wormhole /= 10;
					wormhole_position_x = temp_wormhole % 10;
					input_matrix[i][j].status = 3;
					input_matrix[i][j].code = '-';
					if(wormhole_position_x == 0){
						input_matrix[i][j].wormhole_position = (wormhole_position_x * n) + wormhole_position_y;
					}
					else if(wormhole_position_y == 0){
						input_matrix[i][j].wormhole_position = wormhole_position_x * m;
					}
					else{
						input_matrix[i][j].wormhole_position = wormhole_position_x  + (wormhole_position_y * n);
					}
				}
				// Source
				else if(pch[0] == 'V'){ 
					*source_vertex = current_vertex;
					input_matrix[i][j].vertex = current_vertex;
					input_matrix[i][j].status = 0;
					input_matrix[i][j].code = '-';
					input_matrix[i][j].wormhole_position = -1;
				}
				// Exit
				else if(pch[0] == 'E'){ 
					*exit_vertex = current_vertex;
					input_matrix[i][j].vertex = current_vertex;
					input_matrix[i][j].status = 0;
					input_matrix[i][j].code = '-';
					input_matrix[i][j].wormhole_position = -1;
				}
				pch = strtok(NULL, " ");
				++current_vertex;
			}
			--num_linhas;
		}
	}
}

void create_graph_from_map(graph_t* graph, int n, int m, vertex_node** input_matrix){

	int num_linhas = n-1;
	for(int i = 0; i < n; ++i){
		int current_vertex = m * (num_linhas);
		for(int j = 0; j < m; ++j){
			graph->array[current_vertex].status = input_matrix[i][j].status;
			graph->array[current_vertex].code = input_matrix[i][j].code;
			graph->array[current_vertex].wormhole_position = input_matrix[i][j].wormhole_position;

			if(n == 1){
				if(j == 0){
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
				}
				else if(j == m-1){
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
				}
				else{
					add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
				}
			}
			else if(m == 1){
				if(i == 0){
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
				}
				else if(i == n-1){
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
				}
				else{
					add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
				}
			}
			else{
				if(i == 0 && j == 0){
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
				}
				else if(i == 0 && j == m-1){
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
				}
				else if(i == n-1 && j == 0){
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
				}
				else if(i == n-1 && j == m-1){
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
				}
				else if(i == 0){
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
				}
				else if(i == n-1){
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
				}
				else if(j == 0){
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
				}
				else if(j == m-1){
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
				}
				else{
					if(input_matrix[i-1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i-1][j].vertex);
					}
					if(input_matrix[i+1][j].status != 4){
						add_edge(graph, current_vertex, input_matrix[i+1][j].vertex);
					}
					if(input_matrix[i][j-1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j-1].vertex);
					}
					if(input_matrix[i][j+1].status != 4){
						add_edge(graph, current_vertex, input_matrix[i][j+1].vertex);
					}
				}				
			}
			++current_vertex;
		}
		--num_linhas;
	}
}
