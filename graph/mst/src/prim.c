#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "misc.h"

void prim(graph *g, int V, int E)
{
	FILE *prim_fp = fopen("prim_dump.txt", "w");

	// vertex set.
	int *vset = malloc(V * sizeof(int));
	int vcnt = 0;
	vset[vcnt++] = 0;

	graph mst;
	graph_init(&mst, V);
	int *vis = calloc(V, sizeof(int));
	vis[0] = 1;

	while (vcnt < V) {
		int v1, v2;
		int weight = INT_MAX;

		for (int i = 0; i < vcnt; i++) {
			int cur = vset[i];

			for (int j = 0; j < g->degree[cur]; j++) {
				int next = g->conn[cur][j].x;
				int w = g->conn[cur][j].y;

				if (vis[next] || w >= weight)
					continue;
				
				v1 = cur;
				v2 = next;
				weight = w;
			}
		}

		vset[vcnt++] = v2;
		vis[v2] = 1;
		mst.conn[v1][mst.degree[v1]++] = (pair) {v2, weight};
		mst.conn[v2][mst.degree[v2]++] = (pair) {v1, weight};
	}

	graph_fprint(prim_fp, &mst, V);
	graph_destroy(&mst, V);
	free(vis);
	free(vset);
	fclose(prim_fp);
}
