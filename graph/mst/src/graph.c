#include <stdio.h>
#include <stdlib.h>

#include "misc.h"
#include "graph.h"

void graph_init(graph *g, int V)
{
	g->conn = malloc(V * sizeof(pair*));
	g->degree = calloc(V, sizeof(int));
	for (int i = 0; i < V; i++)
		g->conn[i] = malloc(V * sizeof(pair));
}

void graph_destroy(graph *g, int V)
{
	for (int i = 0; i < V; i++)
		free(g->conn[i]);
	free(g->conn);
	free(g->degree);
}


static int __graph_check_cycle(graph *g, int cur, int prev, int *vis)
{
	vis[cur] = 1;
	int cycle = 0;

	for (int i = 0; i < g->degree[cur]; i++) {
		int next = g->conn[cur][i].x;

		if (vis[next] && next != prev)
			return 1;

		if (!vis[next])
			cycle |= __graph_check_cycle(g, next, cur, vis);

		if (cycle)
			return 1;
	}

	return 0;
}

int graph_check_cycle(graph *g, int V)
{
	// visited status.
	int *vis = calloc(V, sizeof(int));
	int cycle = 0;

	for (int i = 0; i < V; i++) {
		if (!vis[i])
			cycle |= __graph_check_cycle(g, i, -1, vis);

		if (cycle) {
			free(vis);
			return 1;
		}
	}

	free(vis);
	return 0;
}

int graph_check_spanning_tree(graph *g, int V)
{
	int *vis = calloc(V, sizeof(int));
	int cycle = __graph_check_cycle(g, 0, -1, vis);

	if (cycle)
		return 0;

	for (int i = 0; i < V; i++) {
		if (!vis[i])
			return 0;
	}

	return 1;
}

void graph_fprint(const char *msg, FILE *f, graph *g, int V)
{
	int span = 0;
	int E = 0;

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < g->degree[i]; j++) {
			if (i < g->conn[i][j].x)
			{
				fprintf(f, "%d %d %d\n", i, g->conn[i][j].x, g->conn[i][j].y);
				span += g->conn[i][j].y;
				E++;
			}
		}
	}

	printf("%s results: %d vertices, %d edges, %d span\n", msg, V, E, span);
	if (graph_check_spanning_tree(g, V))
		puts("the resulting graph is a spanning tree");
}
