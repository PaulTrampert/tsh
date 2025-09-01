#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../list.h"
#include "../scanner.h"
#include "token.h"
#include "tokenizer.h"
#include "../char_util.h"


void *tokenizer_init(char *inputStr, int inputLen) {
    Scanner scanner;
    scanner.input = inputStr;
    scanner.length = inputLen;
    scanner.position = 0;

    List *tokenList = list_create();
    if (!tokenList) return NULL;

    char currentChar;
    int start = scanner.position;
    while ((currentChar = scanner_next(&scanner)) != NULL) {
        start = scanner.position - 1;
        if (char_is_whitespace(currentChar)) {
            continue;
        }

        TokenType type;
        switch(currentChar) {
            case '&': 
                type = AMP; 
                break;
            case '|': 
                type = PIPE; 
                break;
            case '\'':
                type = SQSTRING;
                if (scanner_find_next(&scanner, '\'') == -1) {
                    fprintf(stderr, "Unterminated single quote string at position %d\n", start);
                }
                break;
            default: 
                type = UQSTRING;
                scanner_find_next_whitespace(&scanner);
                break;
        }

        Token *token = token_new(type, scanner.input + start, scanner.position - start);
        if (!token) {
            list_destroy(tokenList);
            return NULL;
        }

        list_append(tokenList, token);
    }

    return tokenList;
}

void tokenizer_finalize(void *tokenizer) {
    if (!tokenizer) return;

    List *tokenList = (List *)tokenizer;

    while (list_size(tokenList) > 0) {
        Token *token = (Token *)list_dequeue(tokenList);
        token_free(token);
    }

    list_destroy(tokenList);
}

Token *tokenizer_peek(void *tokenizer) {
    if (!tokenizer) return NULL;

    List *tokenList = (List *)tokenizer;

    return (Token *)list_head(tokenList);
}

Token *tokenizer_next(void *tokenizer) {
    if (!tokenizer) return NULL;

    List *tokenList = (List *)tokenizer;

    return (Token *)list_dequeue(tokenList);
}