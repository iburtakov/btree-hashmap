#include "btree.h"
#include <stdio.h>

struct pair
{
    void *key;
    void *data;
};

struct btree
{
    Map m;
    char *name;
    struct pair p;
    struct btree *left;
    struct btree *right;
};

void bt_destroy(Map * t)
{
    if (t != NULL)
    {
        struct btree *bt = (struct btree *)t;
        printf("%s destroyed\n", bt->name);
        free(bt);
    }
}

int cmp(void *lhs, void *rhs)
{
    return *(k_type*)lhs > *(k_type*)rhs;
}

Map *add_node(Map *m, void *key, void *data)
{
    struct btree *bt = (struct btree *)m;
    if (bt == NULL)
    {
        bt = (struct btree *)btree_create(key, data);
        return (Map *)bt;
    }
    else if (cmp((Map *)bt->p.key, key))
        bt->left = (struct btree*)add_node((Map *)bt->left, key, data);
    else
        bt->right = (struct btree*)add_node((Map *)bt->right, key, data);
    return (Map *)bt;
}

void *btree_get(Map *m, void *key)
{
    if (m == NULL)
        return "no such key";
    struct btree *bt = (struct btree *)m;
    if (*(k_type *)key == *(k_type*)bt->p.key)
        return bt->p.data;
    else
    {
        if (cmp((Map *)bt->p.key, key)) // идем в левый
            bt = bt->left;
        else                            // идем в правый
            bt = bt->right;
        return btree_get((Map *)bt, key);
    }
}

int btree_delete(Map *m, void *key)
{
    if (m == NULL)
        return -1;
    struct btree *bt = (struct btree *)m;
    if (*(k_type *)key == *(k_type*)bt->p.key)
    {
        printf("btree destroyed\n");
        free(bt);
        return 1;
    }
    if (bt->left)
    {
        if (*(k_type *)key == *(k_type*)bt->left->p.key)
        {
            struct btree *tba = bt->left;
            if (tba->left == NULL && tba->right == NULL)
                bt->left = NULL;
            else if (tba->left != NULL && tba->right == NULL)
                bt->left = tba->left;
            else if (tba->right != NULL && tba->left == NULL)
                bt->left = tba->right;
            else if (tba->right != NULL && tba->left != NULL)
            {
                bt->left = tba->right;
                tba->right->left->left = tba->left;
            }
            printf("key destroyed\n");
            free(tba);
            return 1;
        }
    }
    if (bt->right)
    {
        if (*(k_type *)key == *(k_type*)bt->right->p.key)
        {
            struct btree *tba = bt->left;
            if (tba->left == NULL && tba->right == NULL)
                bt->right = NULL;
            else if (tba->left != NULL && tba->right == NULL)
                bt->right = tba->left;
            else if (tba->right != NULL && tba->left == NULL)
                bt->right = tba->right;
            else if (tba->right != NULL && tba->left != NULL)
            {
                bt->right = tba->right;
                tba->left->right->right = tba->right;
            }
            printf("key destroyed\n");
            free(tba);
            return 1;
        }
    }
    else
    {
        if (cmp((Map *)bt->p.key, key)) // идем в левый
            bt = bt->left;
        else                            // идем в правый
            bt = bt->right;
        return btree_delete((Map *)bt, key);
    }
    return -1;
}

int btree_change(Map *m, void *key, void *value)
{
    if (m == NULL)
        return -1;
    struct btree *bt = (struct btree *)m;
    if (*(k_type *)key == *(k_type*)bt->p.key)
    {
        bt->p.data = value;
        return 1;
    }
    else
    {
        if (cmp((Map *)bt->p.key, key)) // идем в левый
            bt = bt->left;
        else                            // идем в правый
            bt = bt->right;
        return btree_change((Map *)bt, key, value);
    }
}

Map * btree_create(void *key, void *data)
{
    struct btree * bt = calloc(1, sizeof(struct btree));
    bt->name = "btree";
    bt->right = NULL;
    bt->left = NULL;
    bt->p.key = key;
    bt->p.data = data;
    bt->m.destroy = bt_destroy;
    bt->m.insert = add_node;
    bt->m.compare_keys = cmp;
    bt->m.get = btree_get;
    bt->m.delete = btree_delete;
    bt->m.change = btree_change;
    bt->m.compare_keys = cmp;
    return (Map *)bt;
}
