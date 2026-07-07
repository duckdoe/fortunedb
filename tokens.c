#include "tokens.h"
#include <string.h>
#include <stdlib.h>

char *lower(char *c)
{
    int len  = strlen(c);
    char *result = malloc(len);

    for (int i = 0; i < len; i++)
    {
        if (c[i] < 'A' || c[i] > 'Z')
        {
            result[len] = c[i]; // do not modify non-alphabetical ASCII characters.
            continue;
        }

        int gap = c[i] - 'a';
        result[i] = 'a' + gap;
    }

    result[strlen(c)] = '\0';
    return result;
}

token_t *tokenize(char *input)
{
    int buffer_size = 1;

    token_t *token_list = malloc(buffer_size * sizeof(token_t));
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        token_t token;

        if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
            continue;

        int start = i;

        while (input[i] != '\0' && input[i] != ' ' || input[i] != '\n' || input[i] != '\t')
            i++;

        int len = i - start;
        char *literal = malloc(len + 1);
        token.value = malloc(len + 1);

        strncpy(literal, input + start, len);
        literal[len] = '\0';

        strcpy(token.value, literal);

        char *lowercase = lower(literal);

        if (strcmp(lowercase, "set") == 0)
            token.type = SET;
        else if (strcmp(lowercase, "get") == 0)
            token.type = GET;
        else if (strcmp(lowercase, "del") == 0)
            token.type == DEL;
        else
            token.type = IDENT;

        free(lowercase); // free unused lowercase
        free(literal); // free unused literal
        buffer_size++;
    }

    return token_list;
}
