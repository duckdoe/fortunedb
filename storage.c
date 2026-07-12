#include "storage.h"

void write_to_file(hashmap map, FILE *file)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        if (map.count[i] > 0)
        {
            hnode_t *cnode = &map.data[i];

            fprintf(file, "%s=%s\n", cnode->key, cnode->value);
            while (cnode->next != NULL)
            {
                cnode = cnode->next;
                fprintf(file, "%s=%s\n", cnode->key, cnode->value);
            }
        }
    }
}

void read_from_file(hashmap *map, FILE *file)
{
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL)
    {

        int len = strlen(line);
        int i = 0;
        int start = 0;


        while (i < len && line[i] != '=')
            i++;
        char key[i - 1];

        strncpy(key, line + start, i);
        key[i] = '\0';

        start += i + 1;
        while (i < len)
            i++;

        char value[i - start - 1];

        strncpy(value, line + start, i - start - 1);
        value[i - start - 1] = '\0';

        hnode_t node;

       node.key = malloc(strlen(key) + 1);
       strcpy(node.key, key);

       node.value = malloc(strlen(value) + 1);
       strcpy(node.value, value);

        
       hashmap_set(map, &node);
    }
}
