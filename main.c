#include "main.h"
#include <stdio.h>

#define INPUT_SIZE 256

int main()
{
    char input[INPUT_SIZE];
    fgets(input, INPUT_SIZE, stdin); // Get standard input;

    tokenize(input);
    return 0;
}
