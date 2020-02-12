/*#include "hashmap.h"
#include <stdio.h>
struct hashmap
{
    struct Map m;
    char *name;
};

void hm_destroy(struct map * m)
{
    struct hashmap hm = *(struct hashmap *)m;
    printf("%s destroyed\n", hm.name);
    free(m);
}

struct map * add (struct map *m)
{
    struct hashmap *hm = (struct hashmap *)m;

}

char * check_type(struct map *m)
{
    struct hashmap hm = *(struct hashmap *)m;
    return hm.name;
}

struct map * hmap_create()
{
    struct hashmap * hm = calloc(1, sizeof(struct hashmap));
    hm->name = "hashmap";
    hm->m.destroy = hm_destroy;
    hm->m.check_type = check_type;
    return (struct map *)hm;
}
*/