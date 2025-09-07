#include <stdlib.h>
#include <string.h>
#include "./token.h"

Token *token_new(TokenType type, const char *text, size_t length, size_t position)
{
    Token *token = malloc(sizeof(Token));
    if (!token)
        return NULL;

    token->type = type;
    token->length = length;
    token->position = position;
    token->text = malloc(length + 1);
    if (!token->text)
    {
        free(token);
        return NULL;
    }
    strncpy(token->text, text, length);
    token->text[length] = '\0';

    return token;
}

void token_free(Token *token)
{
    if (!token)
        return;
    free(token->text);
    free(token);
}
