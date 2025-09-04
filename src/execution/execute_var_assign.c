//
// Created by paul on 9/3/25.
//

#include "execute_var_assign.h"

#include <stdlib.h>
#include <string.h>

int execute_var_assign(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult* result)
{
    if (!root || root->type != AST_VAR_ASSIGN || !result)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for variable assignment execution");
        }
        return result ? result->status : -1;
    }
    char *varName = root->var_assign.varWord->text;
    ExecuteResult valueResult;
    execute_result_init(&valueResult);
    execute_ast(root->var_assign.stringNode, stdin_fd, stdout_fd, stderr_fd, &valueResult);
    if (valueResult.status != 0)
    {
        result->status = valueResult.status;
        result->error = valueResult.error;
        free(valueResult.output);
        return result->status;
    }
    setenv(varName, valueResult.output, 1);
    free(valueResult.output);
    result->status = 0;
    return result->status;
}
