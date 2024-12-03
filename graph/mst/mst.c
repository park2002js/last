#include <stdio.h>
#include <stdlib.h>

struct pair
{
	int x, y;
};

struct triple
{
	int x, y, z;
};

struct graph
{
	struct pair **conn;
	int *degree;
};

typedef struct pair pair;
typedef struct triple triple;
typedef struct graph graph;

int triple_cmp(const void *a, const void *b)
{
	return ((const triple*) a)->z - ((const triple*) b)->z;
}

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
}


int __graph_check_cycle(graph *g, int cur, int prev, int *vis)
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

		if (cycle)
			return 1;
	}

	free(vis);
	return 0;
}

void prim(graph *g, int V, int E)
{
	graph mst;
	graph_init(&mst, V);
	graph_destroy(&mst, V);
}

void kruskal(graph *g, int V, int E)
{
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

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < mst.degree[i]; j++) {
			if (i < mst.conn[i][j].x)
				printf("%d-%d (weight: %d)\n", i, mst.conn[i][j].x, mst.conn[i][j].y);
		}
	}

	graph_destroy(&mst, V);
}

int main()
{
	int V, E;
	scanf("%d %d", &V, &E);

	graph g;
	graph_init(&g, V);

	for (int i = 0; i < E; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		g.conn[a][g.degree[a]++] = (pair) {b, c};
		g.conn[b][g.degree[b]++] = (pair) {a, c};
	}

	prim(&g, V, E);
	kruskal(&g, V, E);

	return 0;
}
