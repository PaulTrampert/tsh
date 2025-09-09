//
// Created by paul on 9/7/25.
//

#include "dqstring.h"

#include <stdio.h>

#include "var_string.h"
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
    AstNode *child = NULL;
    Token *nextToken = tokenizer_peek(tokenizer);
    while (nextToken && nextToken->type != DQUOTE)
    {
        child = ast_parse_word(tokenizer);
        if (!child) child = ast_parse_var_string(tokenizer);
        if (child) list_append(node->dqstring.children, child);
        nextToken = tokenizer_peek(tokenizer);
    }
    Token *closeQuote = tokenizer_peek(tokenizer);
    if (!closeQuote || closeQuote->type != DQUOTE)
    {
        fprintf(stderr, "Unterminated double-quoted string starting at position %p\n", &openQuote->position);
        while (list_size(node->dqstring.children) > 0)
        {
            Token *t = list_pop_tail(node->dqstring.children);
            tokenizer_replace(tokenizer, t);
        }
        tokenizer_replace(tokenizer, openQuote);
        ast_free_node(node);
        return NULL;
    }
    closeQuote = tokenizer_next(tokenizer);
    token_free(openQuote);
    token_free(closeQuote);
    return node;
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
