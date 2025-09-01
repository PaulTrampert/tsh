#ifndef GRAMMAR_RULES_STRING_H
#define GRAMMAR_RULES_STRING_H

#include "../ast.h"

AstNode *ast_parse_string(void *tokenizer);

int ast_print_string(AstNode *node, int depth);

#endif // GRAMMAR_RULES_STRING_H