//
// Created by paul on 9/3/25.
//

#ifndef TSH_SQSTRING_H
#define TSH_SQSTRING_H
#include "../ast.h"

AstNode *ast_parse_sqstring(void *tokenizer);

int ast_print_sqstring(AstNode *node, int outFd);

#endif //TSH_SQSTRING_H