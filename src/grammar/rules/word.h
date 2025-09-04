//
// Created by paul on 9/3/25.
//

#ifndef TSH_WORD_H
#define TSH_WORD_H
#include "../ast.h"

AstNode *ast_parse_word(void *tokenizer);

int ast_print_word(AstNode *node, int outFd);
#endif //TSH_WORD_H