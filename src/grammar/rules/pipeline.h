#ifndef GRAMMAR_RULES_PIPELINE_H
#define GRAMMAR_RULES_PIPELINE_H

#include "../ast.h"

AstNode *ast_parse_pipeline(void *tokenizer);

int ast_print_pipeline(AstNode *node, int outFd);

#endif // GRAMMAR_RULES_PIPELINE_H