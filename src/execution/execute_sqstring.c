#include "execute_sqstring.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "../esc_map.h"
#include "../exit_codes.h"

int execute_sqstring(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteContext* result)
{
    if (!root || root->type != AST_SQSTRING || !result)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for single-quoted string execution");
        }
        return -1;
    }
    Token *token = root->sqstring.sqStringToken;
    char *resultString = calloc(token->length + 1, sizeof(char));
    if (!resultString) exit(EOOM);

    int resultPos = 0;
    for (int i = 1; i < token->length - 1; i++)
    {
        if (token->text[i] == '\\')
        {
            i++;
            resultString[resultPos++] = esc_map_escape(token->text[i]);
        }
        else
        {
            resultString[resultPos++] = token->text[i];
        }
    }

    dprintf(stdout_fd, "%s", resultString);

    result->status = 0;
    free(resultString);
    return result->status;
}

