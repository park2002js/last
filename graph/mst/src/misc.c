#include "misc.h"

int triple_cmp(const void *a, const void *b)
{
	return ((const triple*) a)->z - ((const triple*) b)->z;
}
