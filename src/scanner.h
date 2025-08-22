#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *input;
    size_t length;
    size_t position;
} Scanner;

char scanner_next(Scanner *scanner);
char scanner_peek(Scanner *scanner);
int scanner_match(Scanner *scanner, char expected);

#endif // SCANNER_H