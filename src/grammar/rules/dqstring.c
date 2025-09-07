//
// Created by paul on 9/7/25.
//

#include "dqstring.h"

#include <stdio.h>

#include "word.h"
#include "../tokenizer.h"
#include "../token.h"

AstNode* ast_parse_dqstring(void* tokenizer)
{
    Token *openQuote = tokenizer_peek(tokenizer);
    if (!openQuote || openQuote->type != DQUOTE)
    {
        return NULL;
    }
    openQuote = tokenizer_next(tokenizer);
    AstNode *node = ast_create_node(AST_DQSTRING);
    AstNode *child;
    while (tokenizer_peek(tokenizer)->type != DQUOTE)
    {
        child = ast_parse_word(tokenizer);
        if (child) list_append(node->dqstring.children, child);
    }
}

int ast_print_dqstring(AstNode* node, int outFd)
{
    dprintf(outFd, "\"");

    ListIterator *it = list_iterator_create(node->dqstring.children);
    while (list_iterator_has_next(it))
    {
        AstNode *child = (AstNode *)list_iterator_next(it);
        ast_print(child, outFd);
    }
    list_iterator_destroy(it);

    dprintf(outFd, "\"");

    return 0;
}
