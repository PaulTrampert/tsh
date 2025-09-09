#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../list.h"
#include "../scanner.h"
#include "token.h"
#include "tokenizer.h"
#include "../char_util.h"
static Token *read_default_token(Scanner *scanner, char firstChar, List *modeList);
static Token *read_dquote_token(Scanner *scanner, char firstChar, List *modeList);
static Token *read_var_token(Scanner *scanner, char firstChar, List *modeList);

static Token *read_var_token(Scanner *scanner, char firstChar, List *modeList)
{
    size_t start = scanner->position - 1;
    char currentChar = firstChar;

    TokenType type;
    switch (currentChar)
    {
    default:
        type = WORD;
        scanner_scan_word(scanner);
        list_pop_head(modeList);
        break;
    }
    Token *token = token_new(type, scanner->input + start, scanner->position - start, start);
    if (!token)
    {
        return NULL;
    }
    return token;
}

static Token *read_dquote_token(Scanner *scanner, char firstChar, List *modeList)
{
    size_t start = scanner->position - 1;
    char currentChar = firstChar;

    TokenType type;
    switch (currentChar)
    {
    case '"':
        type = DQUOTE;
        list_pop_head(modeList);
        break;
    case '$':
        type = OUT_AS_VAL;
        list_prepend(modeList, &read_var_token);
        break;
    default:
        type = WORD;
        scanner_find_next_in(scanner, "\"$");
        break;
    }

    Token *token = token_new(type, scanner->input + start, scanner->position - start, start);
    if (!token)
    {
        return NULL;
    }
    return token;
}

static Token *read_default_token(Scanner *scanner, char firstChar, List *modeList)
{
    size_t start = scanner->position - 1;
    char currentChar = firstChar;
    if (char_is_whitespace(currentChar))
    {
        return NULL;
    }

    TokenType type;
    switch (currentChar)
    {
    case '&':
        type = AMP;
        break;
    case '|':
        type = PIPE;
        break;
    case '$':
        type = OUT_AS_VAL;
        list_prepend(modeList, &read_var_token);
        break;
    case '=':
        type = ASSIGN;
        break;
    case '"':
        type = DQUOTE;
        list_prepend(modeList, &read_dquote_token);
        break;
    case '\'':
        type = SQSTRING;
        if (scanner_find_next(scanner, '\'') == -1)
        {
            fprintf(stderr, "Unterminated single quote string at position %ld\n", start);
        }
        scanner_next(scanner);
        break;
    default:
        type = WORD;
        scanner_scan_word(scanner);
        break;
    }

    Token *token = token_new(type, scanner->input + start, scanner->position - start, start);
    if (!token)
    {
        return NULL;
    }
    return token;
}

typedef Token *(*ReadTokenFunc)(Scanner *scanner, char firstChar, List *modeList);

void *tokenizer_init(char *inputStr, int inputLen)
{
    Scanner scanner;
    scanner.input = inputStr;
    scanner.length = inputLen;
    scanner.position = 0;

    List *tokenList = list_create();
    List *modeList = list_create();
    list_prepend(modeList, &read_default_token);

    char currentChar;
    while ((currentChar = scanner_next(&scanner)) != '\0')
    {
        ReadTokenFunc readTokenFunc = list_head(modeList);
        Token *token = readTokenFunc(&scanner, currentChar, modeList);
        if (token)
        {
            list_append(tokenList, token);
        }
    }

    return tokenList;
}

void tokenizer_finalize(void *tokenizer)
{
    if (!tokenizer)
        return;

    List *tokenList = (List *)tokenizer;

    while (list_size(tokenList) > 0)
    {
        Token *token = (Token *)list_pop_head(tokenList);
        token_free(token);
    }

    list_destroy(tokenList);
}

Token *tokenizer_peek(void *tokenizer)
{
    if (!tokenizer)
        return NULL;

    List *tokenList = (List *)tokenizer;

    return (Token *)list_head(tokenList);
}

Token *tokenizer_next(void *tokenizer)
{
    if (!tokenizer)
        return NULL;

    List *tokenList = (List *)tokenizer;

    return (Token *)list_pop_head(tokenList);
}

void tokenizer_replace(void *tokenizer, Token* token)
{
    if (!tokenizer || !token)
        return;

    List *tokenList = (List *)tokenizer;
    list_prepend(tokenList, token);
}
