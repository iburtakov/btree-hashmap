#include "hashmap.h"
#include <stdio.h>
struct hashmap
{
    struct map m;
    char *name;
};

void hm_destroy(struct map * m)
{
    struct hashmap hm = *(struct hashmap *)m;
    printf("%s destroyed\n", hm.name);
    free(m);
}


struct map * hmap_create()
{
    struct hashmap * hm = calloc(1, sizeof(struct hashmap));
    hm->name = "hashmap";
    hm->m.destroy = hm_destroy;
    return (struct map *)hm;
}
