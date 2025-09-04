//
// Created by paul on 9/3/25.
//

#include <stdio.h>
#include "var_assign.h"

#include "string.h"
#include "../tokenizer.h"

AstNode* ast_parse_var_assign(void* tokenizer)
{
    Token *varWord = tokenizer_peek(tokenizer);
    if (!varWord || varWord->type != WORD)
    {
        return NULL;
    }
    varWord = tokenizer_next(tokenizer); // consume variable name
    Token *equalsToken = tokenizer_peek(tokenizer);
    if (!equalsToken || equalsToken->type != ASSIGN)
    {
        tokenizer_replace(tokenizer, varWord);
        return NULL;
    }
    equalsToken = tokenizer_next(tokenizer); // consume '='
    AstNode* stringNode = ast_parse_string(tokenizer);
    if (!stringNode)
    {
        tokenizer_replace(tokenizer, equalsToken);
        tokenizer_replace(tokenizer, varWord);
        return NULL;
    }
    token_free(equalsToken);
    AstNode* node = ast_create_node(AST_VAR_ASSIGN);
    node->var_assign.varWord = varWord;
    node->var_assign.stringNode = stringNode;
    return node;
}

int ast_print_var_assign(AstNode* node, int outFd)
{
    if (node == NULL || node->type != AST_VAR_ASSIGN || node->var_assign.varWord == NULL) {
        return -1;
    }
    dprintf(outFd, "%s=", node->var_assign.varWord->text);
    return ast_print(node->var_assign.stringNode, outFd);
}
