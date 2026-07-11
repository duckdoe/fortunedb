#include "hash.h"
#include <stdatomic.h>
#include <stdio.h>

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
       map->count[hash]++;
       return;
   }

   map->data[hash].key = node->key;
   map->data[hash].value = node->value;
   map->data[hash].next = NULL;
   map->count[hash]++;
}

void hashmap_get(hashmap *map, char *key)
{
    unsigned long hash = djb2(key);
    hash = hash % HASH_SIZE;

    if (map->count[hash] > 0)
    {
        hnode_t *cnode = &map->data[hash];

        while (cnode->next != NULL && strcmp(cnode->key, key) != 0)
        {
            cnode = cnode->next;
        }

        if (strcmp(cnode->key, key) != 0)
        {
            printf("Error '%s' does not exist\n", key);
            return;
        }


        printf("%s", cnode->value);
        return;
    }

    printf("Error '%s' does not exist\n", key);
}

void hashmap_del(hashmap *map, char *key)
{
    unsigned long hash = djb2(key);
    hash = hash % HASH_SIZE;

    if (map->count[hash] > 0)
    {
        hnode_t *pnode = NULL; // represents the previous node
        hnode_t *cnode = &map->data[hash]; // represents the current node

        while (cnode->next != NULL && strcmp(cnode->key, key) != 0)
        {
            pnode = cnode;
            cnode = cnode->next;
        }

        if (cnode->key == NULL)
            return;

        if (strcmp(cnode->key, key) != 0) // so we don't delete unwanted shi
        {
            printf("Error '%s' does not exist", key);
            return;
        }

        if (pnode == NULL && cnode->next == NULL)
        {
            cnode->value = NULL; // clear the node
            cnode->key = NULL; // clear the node

            map->count[hash]--;

            return;
        }

        if (pnode != NULL && cnode->next == NULL) // This only works if pnode is a valid node
        {
            pnode->next = NULL;


            free(cnode); // destroy/free the current node
            map->data[hash] = *pnode;

            map->count[hash]--;

            free(pnode);
            return;
        }

        // Handle deleting the first node in the linked list

        if (pnode == NULL && cnode->next != NULL)
        {
            hnode_t *next = cnode->next;
            map->data[hash] = *next;

            return;
        }

        // This is for when the node we are deleting is somewhere in the middle.
        // And both cnode->next and pnode->next are not NULL.

        pnode->next = cnode->next; // Let the previous node point to the next node

        free(cnode); // detroy/free the current node
        map->count[hash]--;
        return;
    }

    printf("Error '%s' does not exist", key);
}

int hashmap_count(hashmap map)
{
    int total = 0;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        total += map.count[i];
    }

    return total;
}

bool hashmap_exists(hashmap *map, char *key)
{
    unsigned long hash = djb2(key);
    hash = hash % HASH_SIZE;

    if (map->count[hash] > 0)
    {
        hnode_t *cnode = &map->data[hash];

        while (cnode->next != NULL && strcmp(cnode->key, key) != 0)
        {
            cnode = cnode->next;
        }

        if (strcmp(cnode->key, key) != 0)
            return false;

        return true;
    }

    return false;
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
