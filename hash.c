#include "hash.h"

unsigned long dbj2(const char *str)
{
    unsigned long h = 5381; // represents the hash
    int c;

    while ((c = *str++))
    {
        h = ((h << 5)+ h) + c;
    }

    return h;
}
