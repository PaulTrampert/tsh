#ifndef GRAMMAR_RULES_COMMAND_H
#define GRAMMAR_RULES_COMMAND_H

#include "../ast.h"

AstNode *ast_parse_command(void *tokenizer);

int ast_print_command(AstNode *node, int depth);

#endif // GRAMMAR_RULES_COMMAND_H