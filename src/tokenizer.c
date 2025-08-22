#include <stdlib.h>
#include <string.h>
#include "./tokenizer.h"

struct tokenizer_struct {
    char *inputStr;
    int inputLen;
    int currentPos;
};

typedef struct tokenizer_struct Tokenizer;

int char_is_delimiter(char c);
void seek_to_next_token(Tokenizer *tokenizer);
int get_token_length(char *start);

int char_is_delimiter(char c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == NULL);
}

void seek_to_next_token(Tokenizer *tokenizer) {
    while (tokenizer->currentPos < tokenizer->inputLen &&
           char_is_delimiter(tokenizer->inputStr[tokenizer->currentPos])) {
        tokenizer->currentPos++;
    }
}

int get_token_length(char *start) {
    char *current = start;
    int length = 0;
    while (!char_is_delimiter(*current)) {
        length++;
        current++;
    }
    return length;
}

void *tokenizer_init(char *inputStr, int inputLen) {
    Tokenizer *tokenizer = malloc(sizeof(Tokenizer));
    if (!tokenizer) return NULL;

    tokenizer->inputStr = malloc(inputLen + 1);
    if (!tokenizer->inputStr) {
        free(tokenizer);
        return NULL;
    }

    strncpy(tokenizer->inputStr, inputStr, inputLen);
    tokenizer->inputStr[inputLen] = '\0';
    tokenizer->inputLen = inputLen;
    tokenizer->currentPos = 0;

    return tokenizer;
}

Token *tokenizer_next(void *tokenizer) {
    return NULL;
}

void tokenizer_finalize(void *tokenizer) {
    Tokenizer *t = (Tokenizer *)tokenizer;
    if (t) {
        free(t->inputStr);
        free(t);
    }
}