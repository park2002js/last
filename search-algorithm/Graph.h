#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void freeGraph(Graph* graph);

#endif // GRAPH_H
