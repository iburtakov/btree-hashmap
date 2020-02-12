#include <stdio.h>
#include "hashmap.h"
#include "btree.h"

int main()
{
    int key1 = 4, value1 = 4;
    int key2 = 3, value2 = 3;
    int key3 = 2, value3 = 2, value4 = 22;
    int key5 = 5, value5 = 5;
    Map *bt = btree_create((void *)&key1, (void *)&value1);
    bt->insert(bt, (void*)&key2, (void*)&value2);
    bt->insert(bt, (void*)&key3, (void*)&value3);
    bt->insert(bt, (void*)&key5, (void*)&value5);
    void *value = bt->get(bt, (void *)&key3);
    printf("%d\n", *(int*)value);
    bt->change(bt, (void*)&key3, (void*)&value4);
    printf("%d\n", *(int*)bt->get(bt, (void*)&key5));
    bt->change(bt, (void*)&key5, (void*)&value4);
    bt->delete(bt, (void *)&key2);
    bt->delete(bt, (void *)&key5);
    bt->delete(bt, (void *)&key3);
    bt->destroy(bt);
    return 0;
}