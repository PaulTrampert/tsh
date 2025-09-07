#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *input;
    size_t length;
    size_t position;
} Scanner;

bool scanner_has_next(Scanner *scanner);
char scanner_next(Scanner *scanner);
char scanner_peek(Scanner *scanner);
int scanner_match(Scanner *scanner, char expected);
int scanner_find_next(Scanner *scanner, char target);
int scanner_find_next_whitespace(Scanner *scanner);
int scanner_scan_word(Scanner *scanner);

#endif // SCANNER_H