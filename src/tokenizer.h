#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "./token.h"


void *tokenizer_init(char *inputStr, int inputLen);

void tokenizer_finalize(void *tokenizer);

#endif // TOKENIZER_H