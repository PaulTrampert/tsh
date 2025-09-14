#ifndef EXECUTION_EXECUTE_PIPELINE_H
#define EXECUTION_EXECUTE_PIPELINE_H
#include "../grammar/ast.h"
#include "execute.h"

int execute_pipeline(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext *result);

#endif // EXECUTION_EXECUTE_PIPELINE_H