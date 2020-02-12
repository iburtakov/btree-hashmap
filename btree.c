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

int cmp(struct map *lhs, struct map *rhs)
{

}

char * check_type_tree(struct map *m)
{
    struct btree bt = *(struct btree *)m;
    return bt.name;
}


struct map * add_node(struct map *m, k_type key, d_type data)
{
    struct btree *bt = (struct btree *)m;
    struct btree *node = bt;
    if (cmp((struct map *)node->left, (struct map *)node->right)) // идем в левый
        node = node->left;
    else                                                          // идем в правый
        node = node->right;
    if (node == NULL)
    {
        node = (struct btree *)btree_create(key, data);
        return (struct map *)bt;
    }
    node = (struct btree *)add_node((struct map *)node, key, data);
    return (struct map *)bt;
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
    bt->m.check_type = check_type_tree;
    bt->m.insert = add_node;
    bt->m.cmp = cmp;
    return (struct map *)bt;
}