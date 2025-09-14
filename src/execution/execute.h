#ifndef EXECUTION_EXECUTE_H
#define EXECUTION_EXECUTE_H

#include <sys/types.h>
#include "../grammar/ast.h"

#define EXECUTE_RESULT_FAILED(status) (status < 0)

typedef struct
{
    int status;
    pid_t groupId;
    char *error;
} ExecuteContext;

int execute_ast(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext *result);

ExecuteContext *execute_new_result();

void execute_result_init(ExecuteContext *result);

void execute_free_result(ExecuteContext *result);

#endif // EXECUTION_EXECUTE_H