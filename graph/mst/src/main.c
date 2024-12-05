#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "misc.h"
extern void prim(graph*, int, int);
extern void kruskal(graph*, int, int);

int main()
{
	FILE *input = fopen("graph.txt", "r");

	int V, E;
	fscanf(input, "%d %d", &V, &E);

	graph g;
	graph_init(&g, V);

	for (int i = 0; i < E; i++) {
		int a, b, c;
		fscanf(input, "%d %d %d", &a, &b, &c);
		g.conn[a][g.degree[a]++] = (pair) {b, c};
		g.conn[b][g.degree[b]++] = (pair) {a, c};
	}

	prim(&g, V, E);
	kruskal(&g, V, E);

	graph_destroy(&g, V);
	fclose(input);
	return 0;
}
