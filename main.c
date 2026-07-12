#include "main.h"
#include "storage.h"
#include <stdio.h>

#define INPUT_SIZE 256
#define BUFFER_SZE 256 // This represents the size of the hashmap

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char filename[256];

    snprintf(filename, sizeof(filename), "%s.db", argv[1]);

    FILE *file = fopen(filename, "r");

    char input[INPUT_SIZE];
    printf("Welcome to fortunedb press Ctrl^D to save and exit, press Ctrl^c to terminate this program\n\n");

    hashmap map;
    map.data = calloc (HASH_SIZE, sizeof(hnode_t));
    map.count = calloc(HASH_SIZE, sizeof(int)); // initilises the value in memory with the types
                                                    // zero value

    if (file != NULL)
        read_from_file(&map, file); // read from the file;

    file = fopen(filename, "w");

    while (1)
    {
        printf("> ");
        fgets(input, INPUT_SIZE, stdin); // Get standard input
        char *lowercase = lower(input);

        if (strcmp(lowercase, "exit\n") == 0)
        {
            printf("Goodbye :)\n");
            break;
        }

        token_t *tokens = tokenize(input);

        if (tokens == NULL)
        {
            printf("Something bad happened please try again.\n");
            break;
        }

        node_t node = parse(tokens);

        if (node.has_error == true)
        {
            continue;
        }

        switch(node.type)
        {

            case NODE_SET:
                hnode_t hnode;
                hnode.key = node.key;
                hnode.value = node.value;
                hnode.next = NULL;

                hashmap_set(&map, &hnode);

                hashmap_to_string(map);
                break;
            case NODE_GET:
                hashmap_get(&map, node.key);
                break;
            case NODE_DEL:
                hashmap_del(&map, node.key);

                hashmap_to_string(map);
                break;
            case NODE_COUNT:
                int total = hashmap_count(map);
                printf("%d keys\n", total);
                break;
            case NODE_EXIST:
                printf("%s", hashmap_exist(&map, node.key) ? "YES" : "NO");
                break;
            default:
                printf("Something bad happened");
        }

        printf("\n"); // print another newline so the terminal can be pretty.
    }
    printf("Saving changes...");
    write_to_file(map, file);
    return 0;
}
