#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./tokenizer.h"

int main(int argc, char** argv) {
    char *inputStr = "this is the first test string for the tokenizer";
    void *tokenizer = tokenizer_init(inputStr, strlen(inputStr));

    tokenizer_finalize(tokenizer);
    return 0;
}