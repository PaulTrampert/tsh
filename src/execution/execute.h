#ifndef EXECUTION_EXECUTE_H
#define EXECUTION_EXECUTE_H

#include "../grammar/ast.h"

typedef struct _executeResult
{
    int status;
    char *error;

} ExecuteResult;

int execute_ast(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result);

ExecuteResult *execute_new_result();

void execute_result_init(ExecuteResult *result);

void execute_free_result(ExecuteResult *result);

#endif // EXECUTION_EXECUTE_H