#pragma once
#include <stdlib.h>
struct map
{
    int (*cmp)(struct map *, struct map *);
    void (*destroy)(struct map *);
    char *(*check_type)(struct map *);
    struct map *(*insert)(struct map *);
    void (*pop)(struct map *);

};

