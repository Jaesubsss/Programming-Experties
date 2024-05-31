#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the structure of a tree node
struct Graph {
    int n_vertices;
    int **adjlist;
};

struct Graph* createGraph(int vertices) {
    struct Graph *newGraph = (struct Graph*)malloc(sizeof(struct Graph)); // Allocate memory for the graph
    
    newGraph -> n_vertices = vertices; // Set the number of vertices
    newGraph -> adjlist = (int**)malloc(sizeof(int*) * vertices); // for pointer to the adjacency list

    for (int i = 0; i < vertices; i++) {
        newGraph -> adjlist[i] = (int*)malloc(sizeof(int) * vertices); // for real list
        for (int j = 0; j < vertices; j++) {
            newGraph->adjlist[i][j] = 0; // Initialize the adjacency list
        }
    }
    return newGraph;
}

double average_neighbors(struct Graph* graph) {
    int neighbors = 0; // initialize total count of neighbors
    for (int i = 0; i < graph->n_vertices; i++) {
        int count = 0; // for counting neighbors
        for (int j = 0; j < graph->n_vertices; j++) {
            if(graph -> adjlist[i][j]){
                count++;
            }
        }
        neighbors += count;
    }
    return (double)neighbors / graph->n_vertices;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph -> adjlist[src][dest] = 1;
    graph -> adjlist[dest][src] = 1;
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->n_vertices; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->n_vertices; j++) {
            if (graph->adjlist[i][j] == 1) {
                printf("%d -> ", j);
            }
        }
        printf("\n");
    }
}


int main() {
    struct Graph* graph = createGraph(9);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);
    addEdge(graph, 3, 7);
    addEdge(graph, 4, 8);

    printGraph(graph);

    printf("\n average number of neighbors: %.2f\n", average_neighbors(graph));
    return 0;
}