#ifndef HASH_H_
#define HASH_H_

#define HASH_SIZE 2

#include "parser.h"

typedef struct hashmap hashmap;
typedef struct hnode_t hnode_t;

struct hnode_t
{
    char *key;
    char *value;

    hnode_t *next;
};

struct hashmap
{
    hnode_t *data;
    int *count;
};

unsigned long dbj2(const char *c);
void hashmap_set(hashmap *map, hnode_t *node);
void hashmap_get(hashmap *map, char *key);
void hashmap_del(hashmap *map, char *key);
void hashmap_to_string(hashmap map);

#endif // HASH_H_
