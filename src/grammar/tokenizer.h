#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "token.h"

void *tokenizer_init(char *inputStr, int inputLen);

void tokenizer_finalize(void *tokenizer);

Token *tokenizer_peek(void *tokenizer);

Token *tokenizer_next(void *tokenizer);

#endif // TOKENIZER_H