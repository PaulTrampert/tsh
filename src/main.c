#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar/tokenizer.h"
#include "grammar/token.h"
#include "grammar/ast.h"

int main(int argc, char** argv) {
    
    while(true) {
        char *input = NULL;
        size_t len = 0;
        printf("> ");
        if (getline(&input, &len, stdin) == -1) {
            perror("getline");
            free(input);
            break;
        }

        if (strncmp(input, "exit", 4) == 0) {
            free(input);
            break;
        }

        void *tokenizer = tokenizer_init(input, len);
        AstNode *ast = ast_parse(tokenizer);
        if (!ast) {
            fprintf(stderr, "Failed to parse AST\n");
            tokenizer_finalize(tokenizer);
            free(input);
            continue;
        }

        ast_print(ast, 0);
        ast_free_node(ast);
        tokenizer_finalize(tokenizer);
        free(input);
    }

    return 0;
}