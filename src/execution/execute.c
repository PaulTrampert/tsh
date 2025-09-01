#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "../exit_codes.h"
#include "execute.h"
#include "../list.h"
#include "../array_list.h"

#define EXECUTE_RESULT_FAILED(status) (status < 0)



ExecuteResult *execute_new_result() {
    ExecuteResult *result = (ExecuteResult *)malloc(sizeof(ExecuteResult));
    if (result) {
        result->status = 0;
        result->output = NULL;
        result->error = NULL;
    }
    return result;
}

void execute_free_result(ExecuteResult *result) {
    if (result) {
        free(result->output);
        free(result->error);
        free(result);
    }
}

int execute_ast(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result) {
    if (!root || !result) return -1;

    switch (root->type) {
        case AST_STRING:
            return execute_string(root, stdin_fd, stdout_fd, stderr_fd, result);
        case AST_COMMAND:
            return execute_command(root, stdin_fd, stdout_fd, stderr_fd, result);
        case AST_PIPELINE:
            return execute_pipeline(root, stdin_fd, stdout_fd, stderr_fd, result);
        default:
            result->status = -1;
            result->error = strdup("Unknown AST node type");
            return result->status;
    }
}

int execute_pipeline(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result) {
    if (!root || root->type != AST_PIPELINE || !result) {
        if (result) {
            result->status = -1;
            result->error = strdup("Invalid AST node for pipeline execution");
        }
        return result->status;
    }

    int numCommands = list_size(root->pipeline.commands);
    if (numCommands == 0) {
        result->status = 0;
        return result->status;
    }

    ListIterator *cmdIter = list_iterator_create(root->pipeline.commands);

    while (list_iterator_has_next(cmdIter)) {
        AstNode *cmdNode = list_iterator_next(cmdIter);
        ExecuteResult cmdResult;
        cmdResult.status = 0;
        cmdResult.output = NULL;
        cmdResult.error = NULL;
        execute_ast(cmdNode, stdin_fd, stdout_fd, stderr_fd, &cmdResult);
        if (EXECUTE_RESULT_FAILED(cmdResult.status)) {
            result->status = cmdResult.status;
            result->error = cmdResult.error;
            break;
        }
        
        waitpid(cmdResult.status, &result->status, 0);
    }
    list_iterator_destroy(cmdIter);

    return result->status;
}

int execute_command(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result) {
    result->status = -1;
    if (root && root->type == AST_COMMAND) {
        ArrayList *args = array_list_create();
        ListIterator *iter = list_iterator_create(root->command.strings);
        while (list_iterator_has_next(iter)) {
            AstNode *argNode = list_iterator_next(iter);
            ExecuteResult argResult;
            argResult.status = 0;
            argResult.error = NULL;
            argResult.output = NULL;
            execute_ast(argNode, stdin_fd, stdout_fd, stderr_fd, &argResult);
            if (EXECUTE_RESULT_FAILED(argResult.status)) {
                // Handle argument execution failure
                result->status = argResult.status;
                result->error = argResult.error;
                list_iterator_destroy(iter);
                array_list_destroy(args, &free);
                return result->status;
            }
            if (argResult.output) {
                array_list_append(args, argResult.output);
            }
        }
        list_iterator_destroy(iter);

        pid_t pid = fork();

        if (pid == -1) {
            result->status = -1;
            result->error = strdup("Failed to fork");
            array_list_destroy(args, &free);
            return result->status;
        }
        else if (pid == 0) {
            // Child process
            if (stdin_fd != STDIN_FILENO) {
                dup2(stdin_fd, STDIN_FILENO);
                close(stdin_fd);
            }
            if (stdout_fd != STDOUT_FILENO) {
                dup2(stdout_fd, STDOUT_FILENO);
                close(stdout_fd);
            }
            if (stderr_fd != STDERR_FILENO) {
                dup2(stderr_fd, STDERR_FILENO);
                close(stderr_fd);
            }
            int execResult = execvp((char *)array_list_get(args, 0), (char **)array_list_get_data(args));
            // If execvp returns, it must have failed
            exit(execResult);
        }

        result->status = pid;
    }
    return result->status;
}

int execute_string(AstNode *root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult *result) {
    result->status = -1;
    if (root && root->type == AST_STRING) {
        // Execute the string command
        result->status = 0;
        result->output = strdup(root->string.value);
        result->error = NULL;
    }
    return result->status;
}
