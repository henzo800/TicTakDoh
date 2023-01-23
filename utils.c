#include <string.h>
#include <stdio.h>
#include "utils.h"

void copy2DArray(int size, int (*fromArray)[size][size], int (*toArray)[size][size])
{
    memcpy(toArray, fromArray, size * sizeof(int) * sizeof(int));
}

struct intVector2 intVector2(int x, int y)
{
    struct intVector2 s;
    s.x = x;
    s.y = y;
    return s;
}
