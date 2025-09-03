//
// Created by paul on 9/3/25.
//

#include "var_string.h"

#include <stdio.h>

#include "../tokenizer.h"


AstNode* ast_parse_var_string(void* tokenizer)
{
    Token *dollarToken = tokenizer_peek(tokenizer);
    if (!dollarToken || dollarToken->type != OUT_AS_VAL) {
        return NULL;
    }
    dollarToken = tokenizer_next(tokenizer); // consume $
    Token* idToken = tokenizer_peek(tokenizer);
    if (!idToken || idToken->type != WORD)
    {
        fprintf(stderr, "Expected variable name after '$' at position %d\n", dollarToken->position);
        tokenizer_replace(tokenizer, dollarToken);
        return NULL;
    }
    idToken = tokenizer_next(tokenizer); // consume variable name
    AstNode* node = ast_create_node(AST_VAR_STRING);
    node->var_string.idWord = idToken;
    token_free(dollarToken);
    return node;
}

int ast_print_var_string(AstNode* node, int outFd)
{
    dprintf(outFd, "$%s", node->var_string.idWord->text);
    return 0;
}
