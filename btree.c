#include "btree.h"
#include "btreep.h"
#include <stdio.h>

void destroy(struct tree *t)
{
    if (t != NULL)
    {
        destroy(t->left);
        destroy(t->right);
        free(t);
    }
}

void bt_destroy(Map * t)
{
    if (t != NULL)
    {
        struct btree *bt = (struct btree *)t;
        destroy(bt->t);
        printf("%s destroyed\n", bt->name);
        free(bt);
    }
}

struct tree * add_node(struct tree *t, void *key, void *data, int (*cmp)(void *, void *))
{
    if (t == NULL)
    {
        t = (struct tree *)calloc(1, sizeof(struct tree));
        t->right = NULL;
        t->left = NULL;
        t->p.key = key;
        t->p.data = data;
        return t;
    }
    else if (cmp(t->p.key, key))
        t->left = add_node(t->left, key, data, cmp);
    else
        t->right = add_node(t->right, key, data, cmp);
    return t;
}

int add_btree(Map *m, void *key, void *data)
{
    struct btree *bt = (struct btree *)m;
    if (bt == NULL)
        return 0;
    bt->t = add_node(bt->t, key, data, bt->cmp);
    return 1;
}

void * get(struct tree *t, void *key, int (*cmp)(void *, void *))
{
    if (t == NULL)
        return "no such key";
    if (key == t->p.key)
        return t->p.data;
    else if (cmp(t->p.key, key))
        return get(t->left, key, cmp);
    else
        return get(t->right, key, cmp);
}

void *btree_get(Map *m, void *key)
{
    struct btree *bt = (struct btree *)m;
    return get(bt->t, key, bt->cmp);
}

int delete(struct tree *t, void *key, int (*cmp)(void *, void *))
{
    if (t == NULL)
        return -1;
    if (key == t->p.key)
    {
        printf("btree destroyed\n");
        free(t);
        return 1;
    }
    else if (t->left)
    {
        if (key == t->left->p.key)
        {
            struct tree *tba = t->left;
            if (tba->left == NULL && tba->right == NULL)
                t->left = NULL;
            else if (tba->left != NULL && tba->right == NULL)
                t->left = tba->left;
            else if (tba->right != NULL && tba->left == NULL)
                t->left = tba->right;
            else if (tba->right != NULL && tba->left != NULL)
            {
                t->left = tba->right;
                tba->right->left->left = tba->left;
            }
            printf("key destroyed\n");
            free(tba);
            return 1;
        }
    }
    else if (t->right)
    {
        if (key == t->right->p.key)
        {
            struct tree *tba = t->right;
            if (tba->left == NULL && tba->right == NULL)
                t->right = NULL;
            else if (tba->left != NULL && tba->right == NULL)
                t->right = tba->left;
            else if (tba->right != NULL && tba->left == NULL)
                t->right = tba->right;
            else if (tba->right != NULL && tba->left != NULL)
            {
                t->right = tba->right;
                tba->left->right->right = tba->right;
            }
            printf("key destroyed\n");
            free(tba);
            return 1;
        }
    }
    else
    {
        if (cmp(t->p.key, key)) // идем в левый
            return delete(t->left, key, cmp);
        else                            // идем в правый
            return delete(t->right, key, cmp);
    }
    return -1;
}

int btree_delete(Map *m, void *key)
{
    struct btree *bt = (struct btree *)m;
    return delete(bt->t, key, bt->cmp);
}

int change(struct tree *t, void *key, void *data, int (*cmp)(void *, void *))
{
    if (t == NULL)
        return -1;
    if (key == t->p.key)
    {
        t->p.data = data;
        return 1;
    }
    else
    {
        if (cmp(t->p.key, key))         // идем в левый
            return change(t->left, key, data, cmp);
        else                            // идем в правый
            return change(t->right, key, data, cmp);
    }
}

int btree_change(Map *m, void *key, void *value)
{
    struct btree *bt = (struct btree *)m;
    return change(bt->t, key, value, bt->cmp);
}

Map * btree_create(int (*cmp)(void *, void *))
{
    struct btree * bt = calloc(1, sizeof(struct btree));
    bt->cmp = cmp;
    bt->t = NULL;
    bt->name = "btree";
    bt->m.destroy = bt_destroy;
    bt->m.insert = add_btree;
    bt->m.compare_keys = cmp;
    bt->m.get = btree_get;
    bt->m.delete = btree_delete;
    bt->m.change = btree_change;
    bt->m.compare_keys = cmp;
    return (Map *)bt;
}



void TestAll()
{
    TestInsert();
    TestGet();
    TestChange();
    TestDelete();
    printf("\n\n");
}

int cmpr(void *l, void *r)
{
    return *(int*)l > *(int*)r;
}

void TestInsert()
{
    Map *btree = btree_create(cmpr);
    struct btree *bt = (struct btree *)btree;
    int x = 1, y = 2, z = 3, p = 4;
    btree->insert(btree, (void*)&z, (void*)&z);
    btree->insert(btree, (void*)&x, (void*)&x);
    btree->insert(btree, (void*)&p, (void*)&p);
    btree->insert(btree, (void*)&y, (void*)&y);
    if (bt->t->p.key == (void*)&z && bt->t->p.data == (void*)&z && bt->t->right->p.key == (void*)&p && bt->t->right->p.data == (void*)&p &&
        bt->t->right->right == NULL && bt->t->right->left == NULL && bt->t->left->p.key == (void*)&x && bt->t->left->p.data == (void*)&x &&
        bt->t->left->left == NULL && bt->t->left->right->p.key == (void*)&y && bt->t->left->right->p.data == (void*)&y)
        printf("Insert is OK\n");
    else
        printf("ERROR in Insert\n");
    btree->destroy(btree);
}

void TestGet()
{
    Map *btree = btree_create(cmpr);
    struct btree *bt = (struct btree *)btree;
    int x = 1, y = 2, z = 3, p = 4;
    btree->insert(btree, (void*)&z, (void*)&z);
    btree->insert(btree, (void*)&x, (void*)&x);
    btree->insert(btree, (void*)&p, (void*)&p);
    btree->insert(btree, (void*)&y, (void*)&y);
    int x1 = *(int*)btree->get(btree, (void*)&x);
    int y2 = *(int*)btree->get(btree, (void*)&y);
    int z3 = *(int*)btree->get(btree, (void*)&z);
    int p4 = *(int*)btree->get(btree, (void*)&p);
    if (x1 == x && y2 == y && z3 == z && p4 == p && bt->t->p.key == (void*)&z && bt->t->p.data == (void*)&z &&
        bt->t->right->p.key == (void*)&p && bt->t->right->p.data == (void*)&p &&bt->t->right->right == NULL &&
        bt->t->right->left == NULL && bt->t->left->p.key == (void*)&x && bt->t->left->p.data == (void*)&x &&
        bt->t->left->left == NULL && bt->t->left->right->p.key == (void*)&y && bt->t->left->right->p.data == (void*)&y)
        printf("Get is OK\n");
    else
        printf("ERROR in Get\n");
    btree->destroy(btree);
}

void TestChange()
{
    Map *btree = btree_create(cmpr);
    int x = 1, y = 2, z = 3, p = 4;
    btree->insert(btree, (void*)&z, (void*)&z);
    btree->insert(btree, (void*)&x, (void*)&x);
    btree->insert(btree, (void*)&p, (void*)&p);
    btree->insert(btree, (void*)&y, (void*)&y);
    int tba1 = 12, tba2 = 16;
    btree->change(btree, (void*)&z, (void*)&tba1);
    btree->change(btree, (void*)&x, (void*)&tba2);
    if (*(int*)btree->get(btree, (void*)&z) == tba1 && *(int*)btree->get(btree, (void*)&x) == tba2)
        printf("Change is OK\n");
    else
        printf("ERROR in Change\n");
    btree->destroy(btree);
}

void TestDelete()
{
    Map *btree = btree_create(cmpr);
    struct btree *bt = (struct btree *)btree;
    int x = 1, y = 2, z = 3, p = 4;
    btree->insert(btree, (void*)&z, (void*)&z);
    btree->insert(btree, (void*)&x, (void*)&x);
    btree->insert(btree, (void*)&p, (void*)&p);
    btree->insert(btree, (void*)&y, (void*)&y);
    btree->delete(btree, (void*)&x);
    if (bt->t->p.key == (void*)&z && bt->t->p.data == (void*)&z && bt->t->right->p.key == (void*)&p && bt->t->right->p.data == (void*)&p &&
        bt->t->left->p.key == (void*)&y && bt->t->left->p.data == (void*)&y && bt->t->left->left == NULL && bt->t->left->right == NULL)
        printf("Delete is OK\n");
    else
        printf("ERROR in Delete\n");
    btree->destroy(btree);
}
