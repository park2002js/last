#ifndef SEARCH_H
#define SEARCH_H
#include "Graph.h"

void BFS(Graph* graph, int startVertex);
void DFS(Graph* graph, int startVertex);
void connectedComponents(Graph* graph);
bool isSpanningTree(Graph* graph);

#endif // SEARCH_H
