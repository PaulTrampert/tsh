#include "execute_command.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include "../list.h"
#include "../array_list.h"
#include "../exit_codes.h"

#define EXECUTE_RESULT_FAILED(status) (status < 0)

int execute_command(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result)
{
    result->status = -1;
    if (root && root->type == AST_COMMAND)
    {
        ListIterator *varIter = list_iterator_create(root->command.var_assigns);
        while (list_iterator_has_next(varIter))
        {
            AstNode *varAssignNode = list_iterator_next(varIter);
            ExecuteResult varResult;
            execute_result_init(&varResult);
            execute_ast(varAssignNode, stdin_fd, stdout_fd, stderr_fd, &varResult);
            if (EXECUTE_RESULT_FAILED(varResult.status))
            {
                result->status = varResult.status;
                result->error = varResult.error;
                list_iterator_destroy(varIter);
                return result->status;
            }
        }
        list_iterator_destroy(varIter);
        ArrayList *args = array_list_create();
        ListIterator *iter = list_iterator_create(root->command.strings);
        while (list_iterator_has_next(iter))
        {
            AstNode *argNode = list_iterator_next(iter);
            ExecuteResult argResult;
            execute_result_init(&argResult);
            execute_ast(argNode, stdin_fd, stdout_fd, stderr_fd, &argResult);
            if (EXECUTE_RESULT_FAILED(argResult.status))
            {
                result->status = argResult.status;
                result->error = argResult.error;
                list_iterator_destroy(iter);
                array_list_destroy(args, &free);
                return result->status;
            }
            if (argResult.output)
            {
                array_list_append(args, argResult.output);
            }
        }
        list_iterator_destroy(iter);

        pid_t pid = fork();

        if (pid == -1)
        {
            result->status = -1;
            result->error = strdup("Failed to fork");
            array_list_destroy(args, &free);
            return result->status;
        }
        else if (pid == 0)
        {
            if (stdin_fd != STDIN_FILENO)
            {
                dup2(stdin_fd, STDIN_FILENO);
                close(stdin_fd);
            }
            if (stdout_fd != STDOUT_FILENO)
            {
                dup2(stdout_fd, STDOUT_FILENO);
                close(stdout_fd);
            }
            if (stderr_fd != STDERR_FILENO)
            {
                dup2(stderr_fd, STDERR_FILENO);
                close(stderr_fd);
            }
            int execResult = execvp((char *)array_list_get(args, 0), (char **)array_list_get_data(args));
            dprintf(stderr_fd, "Error executing command: %s\n", strerror(errno));
            exit(execResult);
        }

        array_list_destroy(args, &free);
        result->status = pid;
    }
    return result->status;
}

