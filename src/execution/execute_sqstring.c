#include "execute_sqstring.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../esc_map.h"
#include "../exit_codes.h"

int execute_sqstring(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult* result)
{
    if (!root || root->type != AST_SQSTRING)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for single-quoted string execution");
        }
        return result->status;
    }
    Token *token = root->sqstring.sqStringToken;
    result->output = calloc(token->length, sizeof(char));
    if (!result->output) exit(EOOM);

    int resultPos = 0;
    for (int i = 1; i < token->length - 1; i++)
    {
        if (token->text[i] == '\\')
        {
            i++;
            result->output[resultPos++] = esc_map_escape(token->text[i]);
        }
        else
        {
            result->output[resultPos++] = token->text[i];
        }
    }
    result->status = 0;
    return result->status;
}

