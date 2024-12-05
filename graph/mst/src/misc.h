#ifndef __MISC_H
#define __MISC_H

struct pair
{
	int x, y;
};

struct triple
{
	int x, y, z;
};

typedef struct pair pair;
typedef struct triple triple;

int triple_cmp(const void*, const void*);

#endif
