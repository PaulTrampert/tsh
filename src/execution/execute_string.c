#include "execute_string.h"
#include <stdlib.h>
#include "../exit_codes.h"

int execute_string(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result)
{
    result->status = -1;
    if (root && root->type == AST_STRING && root->string.childNode)
    {
        ExecuteResult varResult;
        execute_result_init(&varResult);
        execute_ast(root->string.childNode, stdin_fd, stdout_fd, stderr_fd, &varResult);
        result->status = varResult.status;
        result->error = varResult.error;
        return result->status;
    }
    return result->status;
}

