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

void prim(graph *g, int V, int E)
{
	graph mst;
	graph_init(&mst, V);
	puts("prim bro");

	graph_destroy(&mst, V);
}

void kruskal(graph *g, int V, int E)
{
	graph mst;
	graph_init(&mst, V);
	puts("kruskal bro");

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
