#ifndef TOKENS_H_
#define TOKENS_H_

typedef enum
{
SET, // for settting key value pairs
GET, // for getting the value of a key
DEL, // for deleting a key
IDENT, // just the representation of the key/value
} tokentype;


typedef struct
{
    tokentype type;
    char *value;
} token_t; // represent the input gotten during

char *lower(char *c);

#endif // TOKENS_H_
