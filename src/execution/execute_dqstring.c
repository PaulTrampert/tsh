//
// Created by paul on 9/7/25.
//
#include "execute_dqstring.h"
#include "execute.h"

#include <string.h>

int execute_dqstring(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext* result)
{
    if (!root || root->type != AST_DQSTRING || !result)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for double-quoted string execution");
        }
        return -1;
    }

    ListIterator *it = list_iterator_create(root->dqstring.children);
    while (list_iterator_has_next(it))
    {
        ExecuteContext childResult;
        execute_result_init(&childResult);
        AstNode *child = list_iterator_next(it);
        execute_ast(child, stdin_fd, stdout_fd, stderr_fd, &childResult);
        if (EXECUTE_RESULT_FAILED(childResult.status))
        {
            result->status = -1;
            result->error = childResult.error;
            list_iterator_destroy(it);
            return result->status;
        }
    }
    list_iterator_destroy(it);
    result->status = 0;
    result->error = NULL;
    return result->status;
}
