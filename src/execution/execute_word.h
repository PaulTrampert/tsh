#ifndef EXECUTION_EXECUTE_WORD_H
#define EXECUTION_EXECUTE_WORD_H
#include "../grammar/ast.h"
#include "execute.h"

int execute_word(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext* result);

#endif // EXECUTION_EXECUTE_WORD_H

