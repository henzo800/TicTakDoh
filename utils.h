#ifndef UTILS_H
#define UTILS_H

void copy2DArray(int size, int (*fromArray)[size][size], int (*toArray)[size][size]);

struct intVector2
{
    int x;
    int y;
};
struct intVector2 intVector2(int x, int y);
char *intVector2String(struct intVector2 vec);
#endif