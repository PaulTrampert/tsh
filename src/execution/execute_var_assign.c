//
// Created by paul on 9/3/25.
//

#include "execute_var_assign.h"
#include "../read_to_end.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

    int pipeFds[2];
    if (pipe(pipeFds) == -1)
    {
        result->status = -1;
        result->error = strdup("Failed to create pipe for variable assignment execution");
        return result->status;
    }

    execute_ast(root->var_assign.stringNode, stdin_fd, pipeFds[1], stderr_fd, &valueResult);
    close(pipeFds[1]);
    if (valueResult.status != 0)
    {
        result->status = valueResult.status;
        result->error = valueResult.error;
        return result->status;
    }

    char *valueStr = read_to_end(pipeFds[0]);

    setenv(varName, valueStr, 1);
    free(valueStr);
    result->status = 0;
    return result->status;
}
