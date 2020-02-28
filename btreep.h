#pragma once
#include <stdio.h>
#include <stdlib.h>

struct pair
{
    void *key;
    void *data;
};

struct tree
{
    struct pair p;
    struct tree *left;
    struct tree *right;
};

struct btree
{
    Map m;
    char *name;
    struct tree *t;
    int (*cmp)(void *, void*);
};

//! destroys whole tree (struct tree in struct btree)
void destroy(struct tree *t);

//! destroys struct btree
void bt_destroy(Map * t);

//! inserts node to the tree
//! \param t
//! \param key
//! \param data
//! \param cmp (keys compare function)
//! \return modified tree (type: struct tree *)
struct tree * add_node(struct tree *t, void *key, void *data, int (*cmp)(void *, void *));

//!
//! \param m (binary tree container)
//! \param key
//! \param data
//! \return 1 if success and 0 if fault
int add_btree(Map *m, void *key, void *data);

//! returns data from key
//! \param t
//! \param key
//! \param cmp (keys compare function)
//! \return data (type: void *). If no such key, returns "no such key".
void * get(struct tree *t, void *key, int (*cmp)(void *, void *));

//!
//! \param m (binary tree container)
//! \param key
//! \return data (type: void *). If no such key, returns "no such key".
void *btree_get(Map *m, void *key);

//! deletes node by the key
//! \param t
//! \param key
//! \param cmp (keys compare function)
//! \return 1 if success and 0 if fault
int delete(struct tree *t, void *key, int (*cmp)(void *, void *));

//! deletes node by the key
//! \param m (binary tree container)
//! \param key
//! \return 1 if success and 0 if fault
int btree_delete(Map *m, void *key);

//! changes data by the key
//! \param t
//! \param key
//! \param data
//! \param cmp (keys compare function)
//! \return 1 if success and 0 if fault
int change(struct tree *t, void *key, void *data, int (*cmp)(void *, void *));

//! changes data by the key
//! \param m (binary tree container)
//! \param key
//! \param value
//! \return 1 if success and 0 if fault
int btree_change(Map *m, void *key, void *value);

