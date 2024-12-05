#include <stdio.h>
#include <stdlib.h>
#include "Search.h"


//BFS
void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    int queue[graph->numVertices];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("BFS starting from %d: ", startVertex);
    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(visited);
}


void DFSHelper(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex])
            DFSHelper(graph, adjVertex);
        temp = temp->next;
    }
}

// DFS
void DFS(Graph* graph, int startVertex) {
    for (int i = 0; i < graph->numVertices; i++)
        graph->visited[i] = false;

    printf("DFS starting from %d: ", startVertex);
    DFSHelper(graph, startVertex);
    printf("\n");
}

void connectedComponents(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++)
        graph->visited[i] = false;

    int count = 0;
    printf("Connected components:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            printf("Component %d: ", ++count);
            DFSHelper(graph, i);
            printf("\n");
        }
    }
}

bool isSpanningTree(Graph* graph) {
    int edgeCount = 0;
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            edgeCount++;
            temp = temp->next;
        }
    }
    edgeCount /= 2;

    return edgeCount == graph->numVertices - 1;
}
