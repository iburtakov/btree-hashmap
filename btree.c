#include "btree.h"
#include <stdio.h>

struct btree
{
    struct map m;
    char *name;
};

void bt_destroy(struct map * t)
{
    struct btree bt = *(struct btree *)t;
    printf("%s destroyed\n", bt.name);
    free(t);
}

struct map * btree_create()
{
    struct btree * bt = calloc(1, sizeof(struct btree));
    bt->name = "btree";
    bt->m.destroy = bt_destroy;
    return (struct map *)bt;
}
