//
// Created by paul on 9/3/25.
//

#ifndef TSH_VAR_STRING_H
#define TSH_VAR_STRING_H
#include "../ast.h"

AstNode *ast_parse_var_string(void *tokenizer);

int ast_print_var_string(AstNode *node, int outFd);

#endif //TSH_VAR_STRING_H