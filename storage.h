#ifndef STORAGE_H_
#define STORAGE_H_

#include "hash.h"

void write_to_file(hashmap map, FILE *file);
void read_from_file(hashmap *map, FILE *file);

#endif // STORAGE_H_
