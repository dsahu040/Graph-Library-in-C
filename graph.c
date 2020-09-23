/* Fill in your Name and GNumber in the following two comment fields
 * Name: Deep Kumar
 * GNumber: G01215145
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

void find_path(int origin, Graph *graph);

/* Function to initialize the graph
 * sets all elements in adjacency matrix to -1
 * sets all values in visited array to 0
 * return pointer to graph
 * return NULL on error
 */
Graph *graph_initialize() {

    Graph *graph = malloc(sizeof(Graph));
    if(graph == NULL) {
        return NULL;
    }

    // set all edges and vertices values as -1
    if(graph->adj_matrix != NULL) {
        int r;
        int c;
        for(r = 0; r < MAX_VERTICES; r++) {
            for(c = 0; c < MAX_VERTICES; c++) {
                graph->adj_matrix[r][c] = -1;
            }
            graph->visited[r] = 0;
        }
        return graph;
    }
    return NULL;
}

/* Function to add a new vertex in graph
 * return 0 on success
 * return -1 on error
 */
int graph_add_vertex(Graph *graph, int v1) {
    if(v1 >= 0 && v1 < MAX_VERTICES && graph != NULL && graph->adj_matrix != NULL)  {
        if(graph->adj_matrix[v1][v1] != -1) {
            return 0;
        } else {
            graph->adj_matrix[v1][v1] = 0;
            return 0;
        }
    }
    return -1;
}

/* Function to check if given vertex is already existing in the graph
 * return 1 on success
 * return 0 in error
 */
int graph_contains_vertex(Graph *graph, int v1) {
    if(graph != NULL && graph->adj_matrix != NULL && graph->adj_matrix[v1][v1] != -1) {
        return 1;
    }
    return 0;
}

/* Function to remove requested vertex from graph
 * also removes all the edges related to that vertex
 * return 0 on success
 * return -4 on error
 */
int graph_remove_vertex(Graph *graph, int v1) {
    if(graph != NULL && graph->adj_matrix != NULL && v1 >= 0 && v1 < MAX_VERTICES)  {
        if(graph->adj_matrix[v1][v1] == -1) {
            return 0;
        } else {
            int i;
            // set all edges related to the vertex as -1
            for(i = 0; i < MAX_VERTICES; i++) {
                graph->adj_matrix[v1][i] = -1;
                graph->adj_matrix[i][v1] = -1;
            }
            return 0;
        }
    }
    return -1;
}

/* Function to add new edge between two given vertices
 * return 0 on successfully adding the vertex
 * return -1 on error
 */
int graph_add_edge(Graph *graph, int v1, int v2, int wt) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1) && (graph_contains_vertex(graph, v2) == 1) && wt > 0) {
        graph->adj_matrix[v1][v2] = wt;
        return 0;
    }
    return -1;
}

/* Function to check if an edge exists between given vertices
 * return 1 if edge is present
 * return 0 if there is any error
 */
int graph_contains_edge(Graph *graph, int v1, int v2) {
    if(graph != NULL && graph->adj_matrix != NULL && v1 >= 0 && v1 < MAX_VERTICES && v2 >= 0 && v1 < MAX_VERTICES) {
        if(graph->adj_matrix[v1][v2] > 0) {
            return 1;
        }
    }
    return 0;
}

/* Function to remove an edge between given vertices
 * return 0 on successful removal
 * return -1 on any error
 */
int graph_remove_edge(Graph *graph, int v1, int v2) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1) && (graph_contains_vertex(graph, v2) == 1)) {
        // for self loop
        if(v1 == v2) {
            graph->adj_matrix[v1][v2] = 0;
        } else {
            // for other edges
            graph->adj_matrix[v1][v2] = -1;
        }
        return 0;
    }
    return -1;
}

/* Function to count total number of vertices in graph
 * return number of vertices
 */
int graph_num_vertices(Graph *graph) {
    if(graph != NULL && graph->adj_matrix != NULL) {
        int i;
        int count = 0;
        for(i = 0; i < MAX_VERTICES; i++) {
            if(graph->adj_matrix[i][i] != -1) {
                count += 1;
            }
        }
        return count;
    }
    return -1;
}

/* Function to count total edges in the graph
 * return count of edges in the graph
 */
int graph_num_edges(Graph *graph) {
    if(graph != NULL && graph->adj_matrix != NULL) {
        int count = 0;
        int i;
        int j;
        for(i = 0; i < MAX_VERTICES; i++) {
            for(j = 0; j < MAX_VERTICES; j++) {
                if(graph->adj_matrix[i][j] > 0) {
                    count += 1;
                }
            }
        }
        return count;
    }
    return -1;
}

/* Function to find out total edge weight
 * return total edge weight
 * return -1 on error
 */
int graph_total_weight(Graph *graph) {
    if(graph != NULL && graph->adj_matrix != NULL) {
        int weight = 0;
        int i;
        int j;
        for(i = 0; i < MAX_VERTICES; i++) {
            for(j = 0; j < MAX_VERTICES; j++) {
                if(graph->adj_matrix[i][j] > 0) {
                    weight += graph->adj_matrix[i][j];
                }
            }
        }
        return weight;
    }
    return -1;
}

/* Function to get total degree of a given vertex
 * return degree of vertex
 */
int graph_get_degree(Graph *graph, int v1) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1)) {
        int degree = 0;
        int i;
        for(i = 0; i < MAX_VERTICES; i++) {
            // out degree
            if(graph->adj_matrix[v1][i] > 0) {
                degree += 1;
            }
            // In degree
            if(graph->adj_matrix[i][v1] > 0) {
                degree += 1;
            }
        }
        return degree;
    }
    return -1;
}

/* Function to get edge weight for the edge between given vertices
 * return edge weight
 */
int graph_get_edge_weight(Graph *graph, int v1, int v2) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1) && (graph_contains_vertex(graph, v2) == 1)) {
        return graph->adj_matrix[v1][v2];
    }
    return -1;
}

/* Function to check if given vertices are neighbors
 * return 1 if neighbors
 * return 0 on any error or if not neighbors
 */
int graph_is_neighbor(Graph *graph, int v1, int v2) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1) && (graph_contains_vertex(graph, v2) == 1)) {
        if((graph->adj_matrix[v1][v2] > 0) || (graph->adj_matrix[v2][v1] > 0)) {
            return 1;
        }
    }
    return 0;
}

/* Function to get all the predecessors of given vertex
 * return list of vertices which are predecessors
 */
int *graph_get_predecessors(Graph *graph, int v1) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1)) {
        // array to store all predecessors
        int *pred = malloc(sizeof(int) * MAX_VERTICES);
        if (pred == NULL) {
            return NULL;
        }
        int i;
        for(i = 0; i < MAX_VERTICES; i++) {
            pred[i] = -1;
        }

        int count = 0;
        // get all predecessors
        for(i = 0; i < MAX_VERTICES; i++) {
            if(graph->adj_matrix[i][v1] > 0) {
                pred[count] = i;
                count ++;
            }
        }
        return pred;
    }
    return NULL;
}

/* Function to get all the successors of given vertex
 * return list of vertices which are successors
 */
int *graph_get_successors(Graph *graph, int v1) {
    if(graph != NULL && graph->adj_matrix != NULL && (graph_contains_vertex(graph, v1) == 1)) {
        // array to store all successors
        int *successors = malloc(sizeof(int) * MAX_VERTICES);
        if (successors == NULL) {
            return NULL;
        }
        int i;
        for(i = 0; i < MAX_VERTICES; i++) {
            successors[i] = -1;
        }

        int count = 0;
        // get all successors
        for(i = 0; i < MAX_VERTICES; i++) {
            if(graph->adj_matrix[v1][i] > 0) {
                successors[count] = i;
                count ++;
            }
        }
        return successors;
    }
    return NULL;
}

/* Function to check if there is a path possible from vertex v1 to vertex v2
 * return 1 if there is path possible from v1 to v2
 */
int graph_has_path(Graph *graph, int v1, int v2) {
    if(graph != NULL && graph->adj_matrix != NULL && graph->visited != NULL && (graph_contains_vertex(graph, v1) == 1) && (graph_contains_vertex(graph, v2) == 1)) {

        if(v1 == v2) {
            return 1;
        }

        graph->visited[v1] = 1;
        find_path(v1, graph);
        return (graph->visited[v2] == 1) ? 1 : 0;
    }
    return 0;
}

/* Helper method to find path recursively
 */
void find_path(int origin, Graph *graph) {

    int i;
    for(i = 0; i < MAX_VERTICES; i++) {
        if(graph->adj_matrix[origin][i]>0 && graph->visited[i] == 0) {
            graph->visited[i] = 1;
            find_path(i, graph);
        }
    }
}

/* Function to print the graph in a readable format
 */
void graph_print(Graph *graph) {
    if(graph == NULL || graph->adj_matrix == NULL) {
        return;
    }
    printf("\nAdjacency matrix\n");
    printf("   ");
    int i;
    // print template for adjacency matrix
    for (i = 0; i < MAX_VERTICES; i++) {
        printf("%.2d ", i);
    }
    printf("\n");
    for (i = 0; i < MAX_VERTICES; i++) {
        printf("====");
    }
    printf("\n");

    int r;
    int c;
    // print data for adjacency matrix
    for (r = 0; r < MAX_VERTICES; r++) {
        printf("%.2d|| ", r);
        for (c = 0; c < MAX_VERTICES; c++) {
            if(graph->adj_matrix[r][c] == -1) {
                printf(" .  ");
            } else {
                printf("%.2d  ", graph->adj_matrix[r][c]);
            }
        }
        printf("\n");
    }
}

/* Function to write a file output
 * based on graph data
 * which can be used as graph viz input
 */
void graph_output_dot(Graph *graph, char *filename) {
    if(graph != NULL || graph->adj_matrix != NULL) {
        FILE *fp = NULL;
        // open file for write operation
        fp=fopen(filename,"w");
        if(fp==NULL) {
            return;
        } else {
            // write graph data to file
            fprintf(fp, "digraph {\n");
            int r;
            int c;
            for(r = 0; r < MAX_VERTICES; r++) {
                for(c = 0; c < MAX_VERTICES; c++) {
                    if(r==c && graph->adj_matrix[r][c] == 0) {
                        fprintf(fp, "%d;\n", r);
                    }
                    else if(graph->adj_matrix[r][c] > 0) {
                        fprintf(fp, "%d -> %d [label = %d];\n", r, c, graph->adj_matrix[r][c]);
                    }
                }
            }
            fprintf(fp, "}");
            // close file
            fclose(fp);
        }
    }
}

/* Function to load a file
 * and create a graph based on file data
 * return 0 on successful graph creation
 */
int graph_load_file(Graph *graph, char *filename) {

    if(graph == NULL || graph->adj_matrix == NULL) {
        return -1;
    }

    int i;
    int j;
    for(i = 0; i < MAX_VERTICES; i++) {
        for(j = 0; j < MAX_VERTICES; j++) {
            graph->adj_matrix[i][j] = -1;
        }
        graph->visited[i] = 0;
    }

    FILE *fp = NULL;
    // open file to read
    fp=fopen(filename,"r");
    if(fp==NULL) {
        return -1;
    } else {
       char buffer[FILE_ENTRY_MAX_LEN] = "";
       char *ptr = NULL;
       int v1, v2, wt;

       // loop through each line in file
       while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        v2 = -1;
        ptr = strtok(buffer," ,\n");
        v1 = atoi(ptr);
        graph_add_vertex(graph, v1);

            while(ptr != NULL) {
                ptr = strtok(NULL, " ,\n");
                if(ptr != NULL) {
                    if(v2 != -1) {
                        wt = atoi(ptr);
                        graph_add_edge(graph, v1, v2, wt);
                    } else {
                        v2 = atoi(ptr);
                        graph_add_vertex(graph, v2);
                    }
                }
            }
        }
        if (feof(fp)){
            // close file
            fclose(fp);
            return 0;
        } else {
            return -1;
       }
    }
}

/* Function to write graph data into a file
 */
int graph_save_file(Graph *graph, char *filename) {
    if(graph != NULL || graph->adj_matrix != NULL) {
        FILE *fp = NULL;
        // open file to write data
        fp=fopen(filename,"w");
        if(fp==NULL) {
            return -1;
        } else {
            int r;
            int c;
            // write data to file
            for(r = 0; r < MAX_VERTICES; r++) {
                for(c = 0; c < MAX_VERTICES; c++) {
                    if(r==c && graph->adj_matrix[r][c] == 0) {
                        fprintf(fp, "%d\n", r);
                    }
                    else if(graph->adj_matrix[r][c] > 0) {
                        fprintf(fp, "%d, %d, %d\n", r, c, graph->adj_matrix[r][c]);
                }
            }
        }
        // close file
        fclose(fp);
        }
        return 0;
    }
    return -1;
}
