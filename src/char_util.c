#include "char_util.h"

bool char_is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

bool char_is_upper(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool char_is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

bool char_is_alpha(char c)
{
    return char_is_upper(c) || char_is_lower(c);
}

bool char_is_digit(char c)
{
    return c >= '0' && c <= '9';
}

bool char_is_operator(char c)
{
    return c == '&'
        || c == '|'
        || c == '\''
        || c == '$'
        || c == '='
        || c == '"'
    ;
}