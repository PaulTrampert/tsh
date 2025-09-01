#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include "grammar/tokenizer.h"
#include "grammar/token.h"
#include "grammar/ast.h"
#include "execution/execute.h"

int main(int argc, char** argv) {
    
    bool echoCommand = false;

    if (argc > 1) {
        if (strcmp(argv[1], "--echoCommands") == 0) {
            echoCommand = true;
        }
    }


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

        if (echoCommand) {
            ast_print(ast, STDOUT_FILENO);
        }

        ExecuteResult result;
        result.status = 0;
        result.output = NULL;
        result.error = NULL;

        execute_ast(ast, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, &result);
        
        if (result.error) {
            fprintf(stderr, "Error: %s\n", result.error);
            free(result.error);
        }

        ast_free_node(ast);
        tokenizer_finalize(tokenizer);
        free(input);
    }

    return 0;
}