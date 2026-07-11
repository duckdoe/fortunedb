#include "parser.h"
#include <stdio.h>

node_t parse (token_t *tokens)
{
    node_t node;
    char *key;
    char *value;

    node.has_error = false;
    int i = 0;

    switch (tokens[i].type) {
        case SET:
            i++; // advance to the key or value.

            if (tokens[i].type == EOI)
            {
                printf("The SET command takes two arguments, but %d were given\n", i-1);
                node.has_error = true;
                break;
            }

            if (tokens[i].type != IDENT)
            {
                printf("Can only set identifiers to string/identifiers, '%s' is not an identifier\n", tokens[i].value);
                node.has_error = true;
                break;
            }

            key = tokens[i].value;

            i++;

            if (tokens[i].type == EOI)
            {
                printf("The SET command takes two arguments, but %d was given\n", i-1);
                node.has_error = true;
                break;
            }

            value = tokens[i].value;

            i++; // advance to the final token eoi

            if (tokens[i].type != EOI)
            {
                printf("Too many arguments given to SET command\n");
                node.has_error = true;
                break;
            }

            node.type = NODE_SET;
            node.key = key;
            node.value = value;
            break;

        case GET:
            i++;
            if (tokens[i].type == EOI)
            {
                printf("The GET command takes only one argument, but %d was given\n", i - 1);
                node.has_error = true;
                break;
            }

            if (tokens[i].type != IDENT)
            {
                printf("Can only get identifiers, %s is not an identifier\n", tokens[i].value);
                node.has_error = true;
                break;
            }

            key = tokens[i].value;

            i++;

            if(tokens[i].type != EOI)
            {
                printf("Too many arguments given to GET command\n");
                node.has_error = true;
                break;
            }

            node.key = key;
            node.type = NODE_GET;
            node.value = NULL;

            break;
        case DEL:
            i++;

            if (tokens[i].type == EOI)
            {
                printf("The DEL command takes only one argument, but %d was given\n", i-1);
                node.has_error = true;
                break;
            }

            if (tokens[i].type != IDENT)
            {
                printf("Can only delete identifiers, %s is not an identifier\n", tokens[i].value);
                node.has_error = true;
                break;
            }

            key = tokens[i].value;

            i++;

            if (tokens[i].type != EOI)
            {
                printf("Too many arguments given to DEL command\n");
            }

            node.type = NODE_DEL;
            node.key = key;
            node.value = NULL;
            node.next = NULL;

            break;
        default:
            printf("Unknown command '%s'\n", tokens[i].value);
            node.has_error = true;
            break;
    }

    return node;
}

void node_to_string (node_t node)
{
    switch (node.type)
    {
        case NODE_SET:
            printf("Set<type: %d, key: %s,value: '%s'>\n", node.type, node.key, node.value);
            break;
        case NODE_GET:
            printf("Get<type: %d, key: %s>\n", node.type, node.key);
            break;
        case NODE_DEL:
            printf("Del<type: %d, key: %s>\n", node.type, node.key);
            break;
        default:
            printf("What the hell is this node again?\n");
    }
}
