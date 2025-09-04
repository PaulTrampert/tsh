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
        return result->status;
    }

    Token *token = root->word.wordToken;
    result->output = calloc(token->length + 1, sizeof(char));
    if (!result->output) exit(EOOM);

    int resultPos = 0;
    for (int i = 0; i < token->length; i++)
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

