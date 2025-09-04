#ifndef EXECUTION_EXECUTE_COMMAND_H
#define EXECUTION_EXECUTE_COMMAND_H
#include "../grammar/ast.h"
#include "execute.h"

int execute_command(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result);

#endif // EXECUTION_EXECUTE_COMMAND_H

