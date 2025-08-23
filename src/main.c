#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./tokenizer.h"
#include "token.h"

int main(int argc, char** argv) {
    char *inputStr = "bobby said 'you\\'re fat'";
    void *tokenizer = tokenizer_init(inputStr, strlen(inputStr));

    Token *token;
    while ((token = tokenizer_next(tokenizer)) != NULL) {
        printf("Token: %s\n", token->text);
        token_free(token);
    }

    tokenizer_finalize(tokenizer);
    return 0;
}