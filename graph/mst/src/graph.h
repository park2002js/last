#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdio.h>

#include "misc.h"

struct graph
{
	struct pair **conn;
	int *degree;
};

typedef struct graph graph;

void graph_init(graph*, int);
void graph_destroy(graph*, int);
int graph_check_cycle(graph*, int);
void graph_fprint(FILE*, graph*, int);

#endif
