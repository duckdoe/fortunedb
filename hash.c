#include "hash.h"

unsigned long djb2(const char *str)
{
    unsigned long h = 5381; // represents the hash
    int c;

    while ((c = *str++))
    {
        h = ((h << 5)+ h) + c;
    }

    return h;
}

void hashmap_set(hashmap *map, hnode_t *node)
{
   unsigned long hash = djb2(node->key);
   hash = hash % HASH_SIZE;

   if (map->count[hash] > 0)
   {
       hnode_t *cnode = &map->data[hash];

       while (cnode->next != NULL && strcmp(cnode->key, node->key) != 0)
       {
           cnode = cnode->next;
       }


       if (strcmp(cnode->key, node->key) == 0)
       {
           cnode->value = node->value;
           return;
       }

       hnode_t *new_node = malloc(sizeof(hnode_t));

       *new_node = *node;
       new_node->next = NULL;

       cnode->next = new_node;
       return;
   }

   map->data[hash] = *node;
   map->data[hash].next = NULL;   map->data[hash] = *node;
   map->count[hash]++;
}

void hashmap_get(hashmap *map, char *key)
{
    unsigned long hash = djb2(key);
    hash = hash % HASH_SIZE;

    if (map->count[hash] > 0)
    {
        hnode_t *cnode = &map->data[hash];

        while (cnode->next != NULL && strcmp(cnode->key, cnode->key) == 0)
        {
            cnode = cnode->next;
        }

        printf("%s", cnode->value);
        return;
    }

    printf("Error '%s' does not exist\n", key);
}

void hashmap_to_string(hashmap map)
{
    printf("{\n");

    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (map.count[i] > 0)
        {
            hnode_t *cnode = &map.data[i];

            while (cnode != NULL)
            {
                printf("\tkey: %s, value: %s\n",
                       cnode->key,
                       cnode->value);

                cnode = cnode->next;
            }
        }
    }

    printf("}\n");
}
