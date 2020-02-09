#pragma once
#include <stdlib.h>
struct map
{
    void (*cmp)(struct map *a, struct map *b);
    void (*destroy)(struct map *m);
};