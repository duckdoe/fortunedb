#include "main.h"
#include "tokens.h"
#include <stdio.h>

#define INPUT_SIZE 256

int main()
{
    char input[INPUT_SIZE];
    fgets(input, INPUT_SIZE, stdin); // Get standard input;

    token_t *tokens = tokenize(input);

    printf("Tokenized successfully!\n");

    if (tokens == NULL)
    {
        printf("Something bad happened while trying to parse stuff");
        return 0;
    }

    int i = 0;
    while (tokens[i].type != EOI)
    {
        token_to_string(tokens[i]);
        printf("\n");
        i++;
    }

    token_to_string(tokens[i]);
    printf("\n");
    return 0;
}
