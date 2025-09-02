#include "esc_map.h"

// 256-entry lookup table for O(1) escape sequence mapping
static const unsigned char esc_lookup[256] = {
    ['a'] = '\a',
    ['b'] = '\b',
    ['f'] = '\f',
    ['n'] = '\n',
    ['r'] = '\r',
    ['t'] = '\t',
    ['v'] = '\v',
    ['\\'] = '\\',
    ['\''] = '\'',
    ['"'] = '"',
    ['?'] = '\?',
};

char esc_map_escape(char c)
{
    if (esc_lookup[(unsigned char)c])
    {
        return esc_lookup[(unsigned char)c];
    }
    return c;
}
