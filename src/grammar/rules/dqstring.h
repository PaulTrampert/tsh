//
// Created by paul on 9/7/25.
//

#ifndef GRAMMAR_RULES_DQSTRING_H
#define GRAMMAR_RULES_DQSTRING_H
#include "../ast.h"

AstNode *ast_parse_dqstring(void *tokenizer);

int ast_print_dqstring(AstNode *node, int outFd);

#endif //GRAMMAR_RULES_DQSTRING_H