#ifndef CHAR_UTIL_H
#define CHAR_UTIL_H

#include <stdbool.h>

// Returns true if c is a whitespace character (space, tab, newline, etc.)
bool char_is_whitespace(char c);

// Returns true if c is an upper-case letter (A-Z)
bool char_is_upper(char c);

// Returns true if c is a lower-case letter (a-z)
bool char_is_lower(char c);

// Returns true if c is a letter (A-Z or a-z)
bool char_is_alpha(char c);

// Returns true if c is a digit (0-9)
bool char_is_digit(char c);

// Returns true if c is an operator. Currently, operators are: '&', '|'
bool char_is_operator(char c);

#endif // CHAR_UTIL_H
