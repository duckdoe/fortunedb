#ifndef TOKENS_H_
#define TOKENS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
SET, // for settting key value pairs
GET, // for getting the value of a key
DEL, // for deleting a key
COUNT,
EXIST,
IDENT, // just the representation of the key/value
STRING, // Represents a string
EOI, // Represent end of input
} tokentype;


typedef struct
{
    tokentype type;
    char *value;
} token_t; // represent the input gotten during

char *lower(char *c);
token_t *tokenize(char *input);
void token_to_string(token_t token);

#endif // TOKENS_H_
