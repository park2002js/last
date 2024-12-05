#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Graph.h"
#include "Search.h"

#define MAX_NODES 50
#define EDGE_DENSITY 0.6

int main() {
    int vertices = MAX_NODES;
    int edges = (int)(vertices * (vertices - 1) * EDGE_DENSITY / 2);
    Graph* graph = createGraph(vertices);

    srand(time(NULL));
    for (int i = 0; i < edges; i++) {
        int src = rand() % vertices;
        int dest = rand() % vertices;
        addEdge(graph, src, dest);
    }

    BFS(graph, 0);
    DFS(graph, 0);
    connectedComponents(graph);

    if (isSpanningTree(graph)) {
        printf("Spanning tree.\n");
    } else {
        printf("Not a spanning tree.\n");
    }

    freeGraph(graph);
    return 0;
}
