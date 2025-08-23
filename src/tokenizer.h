#ifndef TOKENIZER_H
#define TOKENIZER_H

void *tokenizer_init(char *inputStr, int inputLen);

void tokenizer_finalize(void *tokenizer);

#endif // TOKENIZER_H