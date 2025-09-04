#ifndef EXECUTION_EXECUTE_SQSTRING_H
#define EXECUTION_EXECUTE_SQSTRING_H
#include "../grammar/ast.h"
#include "execute.h"

int execute_sqstring(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult* result);

#endif // EXECUTION_EXECUTE_SQSTRING_H

