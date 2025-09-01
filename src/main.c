#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar/tokenizer.h"
#include "grammar/token.h"
#include "grammar/ast.h"

int main(int argc, char** argv) {
    char *inputStr = "bobby said 'you\\'re fat' | am not! | r2d2\\n\\nlikes new lines";
    void *tokenizer = tokenizer_init(inputStr, strlen(inputStr));

    AstNode *ast = ast_parse(tokenizer);
    if (!ast) {
        fprintf(stderr, "Failed to parse AST\n");
        tokenizer_finalize(tokenizer);
        return 1;
    }

    ast_print(ast, 0);

    ast_free_node(ast);
    tokenizer_finalize(tokenizer);

    return 0;
}