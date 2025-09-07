#include "execute_var_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int execute_var_string(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult* result)
{
    if (!root || root->type != AST_VAR_STRING || !result)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for variable string execution");
        }
        return result ? result->status : -1;
    }

    char *varName = root->var_string.idWord->text;
    char *varValue = getenv(varName);
    if (!varValue)
    {
        varValue = "";
    }
    dprintf(stdout_fd, "%s", varValue);
    result->status = 0;
    result->error = NULL;
    return result->status;
}

