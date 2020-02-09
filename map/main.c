#include <stdio.h>
#include "hashmap.h"
#include "btree.h"
int main()
{
    struct map *hm = hmap_create();
    struct map *bt = btree_create();
    hm->destroy(hm);
    bt->destroy(bt);
    return 0;
}