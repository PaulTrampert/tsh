#include "scanner.h"
#include "char_util.h"

bool scanner_has_next(Scanner* scanner)
{
    return scanner->position < scanner->length;
}

char scanner_next(Scanner *scanner)
{
    if (scanner->position < scanner->length)
    {
        return scanner->input[scanner->position++];
    }
    return 0;
}

char scanner_peek(Scanner *scanner)
{
    if (scanner->position < scanner->length)
    {
        return scanner->input[scanner->position];
    }
    return 0;
}

int scanner_match(Scanner *scanner, char expected)
{
    if (scanner_peek(scanner) == expected)
    {
        scanner_next(scanner);
        return 1;
    }
    return 0;
}

int scanner_find_next(Scanner *scanner, char target)
{
    while (scanner->position < scanner->length)
    {
        if (scanner->input[scanner->position] == target)
        {
            return scanner->position++;
        }
        if (scanner->input[scanner->position] == '\\' && scanner->position + 1 < scanner->length)
        {
            // Skip escaped character
            scanner->position++;
        }
        scanner->position++;
    }
    return -1; // Not found
}

int scanner_find_next_whitespace(Scanner *scanner)
{
    while (scanner->position < scanner->length)
    {
        if (char_is_whitespace(scanner->input[scanner->position]))
        {
            return scanner->position;
        }
        if (scanner->input[scanner->position] == '\\' && scanner->position + 1 < scanner->length)
        {
            // Skip escaped character
            scanner->position++;
        }
        scanner->position++;
    }
    return -1; // Not found
}

int scanner_scan_word(Scanner* scanner)
{
    do
    {
        char currentChar = scanner_next(scanner);
        if (currentChar == '\\')
        {
            scanner_next(scanner);
        }
        else if (char_is_whitespace(currentChar) || char_is_operator(currentChar))
        {
            return scanner->position;
        }
    } while (scanner_has_next(scanner));
    return -1; // Not found
}
