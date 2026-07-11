#include "main.h"
#include "hash.h"
#include <stdio.h>

#define INPUT_SIZE 256
#define BUFFER_SZE 2 // This represents the size of the hashmap

int main()
{
    char input[INPUT_SIZE];
    printf("Welcome to fortunedb press Ctrl^c to exit\n\n");

    hashmap map;
    map.data = calloc (HASH_SIZE, sizeof(hnode_t));
    map.count = calloc(HASH_SIZE, sizeof(int)); // initilises the value in memory with the types
                                                    // zero value

    while (1)
    {
        printf("> ");
        fgets(input, INPUT_SIZE, stdin); // Get standard input
        char *lowercase = lower(input);

        if (strcmp(lowercase, "exit") == 0)
        {
            printf("Goodbye :)\n");
            return 0;
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
            default:
                printf("Something bad happened");
        }

        printf("\n"); // print another newline so the terminal can be pretty.
    }

    return 0;
}
