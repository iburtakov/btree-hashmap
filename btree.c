#include "btree.h"
#include <stdio.h>

struct pair
{
    k_type key;
    d_type data;
};

struct btree
{
    struct map m;
    char *name;
    struct pair p;
    struct btree *left;
    struct btree *right;
};

void bt_destroy(struct map * t)
{
    struct btree bt = *(struct btree *)t;
    printf("%s destroyed\n", bt.name);
    free(t);
}

int cmp(struct btree *lhs, struct btree *rhs)
{

}

char * check_type(struct map *m)
{
    struct btree bt = *(struct btree *)m;
    return bt.name;
}

struct map * add(struct map *m, k_type key, d_type data)
{
    struct btree *bt = (struct btree *)m;
    struct btree *node = bt;
    
}

struct map * btree_create(k_type key, d_type data)
{
    struct btree * bt = calloc(1, sizeof(struct btree));
    bt->name = "btree";
    bt->right = NULL;
    bt->left = NULL;
    bt->p.key = key;
    bt->p.data = data;
    bt->m.destroy = bt_destroy;
    bt->m.check_type = check_type;
    bt->m.cmp = cmp;
    return (struct map *)bt;
}
