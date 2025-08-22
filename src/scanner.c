#include "scanner.h"

char scanner_next(Scanner *scanner) {
    if (scanner->position < scanner->length) {
        return scanner->input[scanner->position++];
    }
    return EOF;
}

char scanner_peek(Scanner *scanner) {
    if (scanner->position < scanner->length) {
        return scanner->input[scanner->position];
    }
    return EOF;
}

int scanner_match(Scanner *scanner, char expected) {
    if (scanner_peek(scanner) == expected) {
        scanner_next(scanner);
        return 1;
    }
    return 0;
}
