#include "execute_word.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../esc_map.h"
#include "../exit_codes.h"

int execute_word(AstNode* root, int stdin_fd, int stdout_fd, int stderr_fd, ExecuteResult* result)
{
    if (!root || root->type != AST_WORD || !result)
    {
        if (result)
        {
            result->status = -1;
            result->error = strdup("Invalid AST node for word execution");
        }
        return result ? result->status : -1;
    }

    Token *token = root->word.wordToken;
    char *resultString = calloc(token->length + 1, sizeof(char));
    if (!resultString) exit(EOOM);

    size_t resultPos = 0;
    for (size_t i = 0; i < token->length; i++)
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

