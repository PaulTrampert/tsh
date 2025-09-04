#include "execute_pipeline.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "../list.h"
#include "../array_list.h"
#include "../exit_codes.h"

#define EXECUTE_RESULT_FAILED(status) (status < 0)

int execute_pipeline(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result)
{
    if (!root || root->type != AST_PIPELINE || !result)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for pipeline execution");
        }
        return result->status;
    }

    int numCommands = list_size(root->pipeline.commands);
    if (numCommands == 0)
    {
        result->status = 0;
        return result->status;
    }

    pid_t *pids = malloc(numCommands * sizeof(pid_t));
    if (!pids)
        exit(EOOM);

    int cmdIn = stdin_fd;
    int cmdOut = -1;
    int nextCmdIn = -1;
    int i = 0;
    ListIterator *cmdIter = list_iterator_create(root->pipeline.commands);

    while (list_iterator_has_next(cmdIter))
    {
        AstNode *cmdNode = list_iterator_next(cmdIter);
        ExecuteResult cmdResult;
        execute_result_init(&cmdResult);
        int pipeFds[2];
        if (list_iterator_has_next(cmdIter))
        {
            if (pipe(pipeFds) == -1)
            {
                result->status = -1;
                result->error = strdup("Failed to create pipe");
                return result->status;
            }
            cmdOut = pipeFds[1];
            nextCmdIn = pipeFds[0];
        }
        else
        {
            pipeFds[0] = -1;
            pipeFds[1] = -1;
            nextCmdIn = -1;
            cmdOut = stdout_fd;
        }
        execute_ast(cmdNode, cmdIn, cmdOut, stderr_fd, &cmdResult);
        if (cmdIn != stdin_fd && cmdIn != -1)
        {
            close(cmdIn);
        }
        if (cmdOut != stdout_fd && cmdOut != -1)
        {
            close(cmdOut);
        }
        cmdIn = nextCmdIn;
        if (EXECUTE_RESULT_FAILED(cmdResult.status))
        {
            if (cmdResult.error)
            {
                dprintf(stderr_fd, "Error executing command: %s\n", cmdResult.error);
                free(cmdResult.error);
            }
        }

        pids[i++] = cmdResult.status;
    }
    list_iterator_destroy(cmdIter);

    for (int j = 0; j < i; j++)
    {
        if (pids[j] != -1)
        {
            waitpid(pids[j], &result->status, 0);
        }
    }
    free(pids);
    return result->status;
}

