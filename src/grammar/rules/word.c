//
// Created by paul on 9/3/25.
//

#include "word.h"
#include "../tokenizer.h"
#include <stdio.h>

AstNode* ast_parse_word(void* tokenizer)
{
    Token *wordToken = tokenizer_peek(tokenizer);
    if (!wordToken || wordToken->type != WORD) {
        return NULL;
    }
    wordToken = tokenizer_next(tokenizer); // consume WORD
    AstNode* node = ast_create_node(AST_WORD);
    node->word.wordToken = wordToken;
    return node;
}

int ast_print_word(AstNode* node, int outFd)
{
    if (!node || !node->word.wordToken || !node->word.wordToken->text) {
        return -1;
    }
    dprintf(outFd, "%s", node->word.wordToken->text);
    return 0;
}
