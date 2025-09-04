//
// Created by paul on 9/3/25.
//

#include "sqstring.h"
#include "../tokenizer.h"

#include <stdio.h>

AstNode* ast_parse_sqstring(void* tokenizer)
{
    Token *token = tokenizer_peek(tokenizer);
    if (!token || token->type != SQSTRING)
    {
        return NULL;
    }
    token = tokenizer_next(tokenizer);

    AstNode *node = ast_create_node(AST_SQSTRING);
    node->sqstring.sqStringToken = token;

    return node;
}

int ast_print_sqstring(AstNode* node, int outFd)
{
    dprintf(outFd, "%s", node->sqstring.sqStringToken->text);
    return 0;
}
