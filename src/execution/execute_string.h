#ifndef EXECUTION_EXECUTE_STRING_H
#define EXECUTION_EXECUTE_STRING_H
#include "../grammar/ast.h"
#include "execute.h"

int execute_string(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result);

#endif // EXECUTION_EXECUTE_STRING_H

