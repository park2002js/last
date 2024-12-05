#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "misc.h"

void kruskal(graph *g, int V, int E)
{
	FILE *kruskal_fp = fopen("kruskal_dump.txt", "w");

	int edge_ptr = 0;
	triple *edges = malloc(E * sizeof(triple));

	// edge extraction from graph.
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < g->degree[i]; j++) {
			if (g->conn[i][j].x > i)
				edges[edge_ptr++] = (triple) {i, g->conn[i][j].x, g->conn[i][j].y};
		}
	}

	qsort(edges, E, sizeof(triple), triple_cmp);

	graph mst;
	graph_init(&mst, V);

	edge_ptr = 0;
	while (edge_ptr < E) {
		// vertex 1, vertex 2, weight;
		int v1 = edges[edge_ptr].x;
		int v2 = edges[edge_ptr].y;
		int w = edges[edge_ptr].z;

		mst.conn[v1][mst.degree[v1]++] = (pair) {v2, w};
		mst.conn[v2][mst.degree[v2]++] = (pair) {v1, w};
		edge_ptr++;

		if (!graph_check_cycle(&mst, V))
			continue;
		else {
			mst.degree[v1]--;
			mst.degree[v2]--;
		}
	}

	graph_fprint(kruskal_fp, &mst, V);
	graph_destroy(&mst, V);
	free(edges);
	fclose(kruskal_fp);
}
