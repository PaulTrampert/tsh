#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "grammar/tokenizer.h"
#include "grammar/ast.h"
#include "execution/execute.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "state/job.h"

int main(int argc, char **argv)
{

    bool echoCommand = false;

    if (argc > 1)
    {
        if (strcmp(argv[1], "--echoCommands") == 0)
        {
            echoCommand = true;
        }
    }

    while (true)
    {
        char *input = NULL;
        size_t len = 0;
        input = readline("> ");
        len = strlen(input);

        if (strncmp(input, "exit", 4) == 0)
        {
            free(input);
            break;
        }

        void *tokenizer = tokenizer_init(input, len);
        AstNode *ast = ast_parse(tokenizer);
        if (!ast)
        {
            fprintf(stderr, "Failed to parse AST\n");
            tokenizer_finalize(tokenizer);
            free(input);
            continue;
        }
        add_history(input);

        if (echoCommand)
        {
            ast_print(ast, STDOUT_FILENO);
            fprintf(stdout, "\n");
        }

        ExecuteResult result;
        result.status = 0;
        result.error = NULL;

        execute_ast(ast, STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, &result);

        if (result.error)
        {
            fprintf(stderr, "Error: %s\n", result.error);
            free(result.error);
        }

        tokenizer_finalize(tokenizer);
        free(input);
    }

    return 0;
}
