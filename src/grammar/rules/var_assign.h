//
// Created by paul on 9/3/25.
//

#ifndef TSH_VAR_ASSIGN_H
#define TSH_VAR_ASSIGN_H
#include "../ast.h"

AstNode* ast_parse_var_assign(void* tokenizer);

int ast_print_var_assign(AstNode* node, int outFd);

#endif //TSH_VAR_ASSIGN_H