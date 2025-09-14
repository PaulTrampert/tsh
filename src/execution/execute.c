#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "execute.h"

#include "execute_command.h"
#include "execute_dqstring.h"
#include "execute_pipeline.h"
#include "execute_sqstring.h"
#include "execute_string.h"
#include "execute_var_assign.h"
#include "execute_var_string.h"
#include "execute_word.h"

#define EXECUTE_RESULT_FAILED(status) (status < 0)

ExecuteContext *execute_new_result()
{
    ExecuteContext *result = (ExecuteContext *)malloc(sizeof(ExecuteContext));
    if (result)
    {
        result->status = 0;
        result->error = NULL;
    }
    return result;
}

void execute_result_init(ExecuteContext* result)
{
    result->status = 0;
    result->groupId = 0;
    result->error = NULL;
}

void execute_free_result(ExecuteContext *result)
{
    if (result)
    {
        free(result->error);
        free(result);
    }
}

int execute_ast(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext *result)
{
    if (!root || !result)
        return -1;

    switch (root->type)
    {
    case AST_STRING:
        return execute_string(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_COMMAND:
        return execute_command(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_PIPELINE:
        return execute_pipeline(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_VAR_STRING:
        return execute_var_string(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_SQSTRING:
        return execute_sqstring(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_WORD:
        return execute_word(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_VAR_ASSIGN:
        return execute_var_assign(root, stdin_fd, stdout_fd, stderr_fd, result);
    case AST_DQSTRING:
        return execute_dqstring(root, stdin_fd, stdout_fd, stderr_fd, result);
    default:
        result->status = -1;
        result->error = strdup("Unknown AST node type");
        return result->status;
    }
}
