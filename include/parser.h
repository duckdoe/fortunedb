#ifndef PARSER_H_
#define PARSER_H_

#include "tokens.h"
#include <stdbool.h>

typedef struct node_t node_t;

typedef enum
{
NODE_SET,
NODE_GET,
NODE_DEL,
NODE_EXIST,
NODE_COUNT,
} nodetype;

struct node_t
{
    nodetype type;

    char *key; // represents the key
    char *value; // represents the value

    bool has_error;

    node_t *next; // represents the next node in the 'linked list'
};

node_t parse(token_t *tokens);
void node_to_string(node_t node);


#endif // PARSER_H_
