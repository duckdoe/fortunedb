#include "main.h"
#include "parser.h"
#include <stdio.h>

#define INPUT_SIZE 256
#define BUFFER_SZE 256 // This represents the size of the hashmap

int main()
{
    char input[INPUT_SIZE];
    printf("Welcome to fortunedb press Ctrl^c to exit\n\n");

    while (1)
    {
        printf("> ");
        fgets(input, INPUT_SIZE, stdin); // Get standard input
        char *lowercase = lower(input);

        if (strcmp(lowercase, "exit") == 0)
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
        node_to_string(node);

        node_t map[256];

        for (int i = 0; tokens[i].type != EOI; i++)
        {
            free(tokens[i].value); // free individual token values after use.
        }

        free(tokens); // free the tokens array after use.

        printf("\n"); // print another newline so the terminal can be pretty.
    }

    return 0;
}
