#include "tokens.h"

char *lower(char *c)
{
    int len  = strlen(c);
    char *result = malloc(len + 1);

    for (int i = 0; i < len; i++)
    {
        if (c[i] < 'A' || c[i] > 'Z')
        {
            result[i] = c[i]; // do not modify non-alphabetical characters.
            continue;
        }

        int gap = c[i] - 'A';
        result[i] = 'a' + gap;
    }

    result[len] = '\0';
    return result;
}


void token_to_string(token_t token)
{
    printf("Token<type: %d, value: %s>", token.type, token.value);
}


token_t *tokenize(char *input)
{
    int buffer_size = 1; // the token_list buffer size
    token_t *token_list = malloc(buffer_size * sizeof(token_t));
    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        token_t token;

        if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
            continue;

        if (input[i] == '\'' || input[i] == '"') // Handle support for strings
        {
            int quote = input[i];

            i++;
            int start = i;

            while (input[i] != '\0' && input[i] != quote)
                i++;

            int len = i - start;

            token.value = malloc(len + 1);
            token.type = STRING;

            strncpy(token.value, input + start, len);
            token.value[len] = '\0';

            token_list[buffer_size - 1] = token;
            token_t *temp = realloc(token_list, ++buffer_size * sizeof(token_t));

            if (temp == NULL)
            {
                free(temp);
                free(token_list);
                return NULL;
            }

            token_list = temp;
            continue;
        }

        int start = i;

        while (input[i] != '\0' && input[i] != ' ' && input[i] != '\n' && input[i] != '\t')
            i++;

        int len = i - start;
        token.value = malloc(len + 1);

        strncpy(token.value, input + start, len);
        token.value[len] = '\0';

        char *lowercase = lower(token.value);

        if (strcmp(lowercase, "set") == 0)
            token.type = SET;
        else if (strcmp(lowercase, "get") == 0)
            token.type = GET;
        else if (strcmp(lowercase, "del") == 0)
            token.type = DEL;
        else if (strcmp(lowercase, "count") == 0)
            token.type = COUNT;
        else if (strcmp(lowercase, "exist") == 0)
            token.type = EXIST;
        else
            token.type = IDENT;

        free(lowercase); // free unused lowercase

        token_list[buffer_size - 1] = token;
        token_t *temp = realloc(token_list, ++buffer_size * sizeof(token_t));

        if (token_list == NULL){
            free(temp);
            return NULL;
        }

        token_list = temp;
    }

    token_t token;

    token.type = EOI;
    token.value = "\0";

    token_list[buffer_size - 1] = token;

    return token_list;
}
