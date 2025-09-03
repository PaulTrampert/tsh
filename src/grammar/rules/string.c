#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "var_string.h"
#include "../tokenizer.h"
#include "../../esc_map.h"

AstNode *ast_parse_string(void *tokenizer)
{
    AstNode *varStringNode = ast_parse_var_string(tokenizer);
    if (varStringNode)
    {
        AstNode *node = ast_create_node(AST_STRING);
        if (!node)
        {
            ast_free_node(varStringNode);
            return NULL;
        }
        node->string.varStringNode = varStringNode;
        return node;
    }
    Token *token = tokenizer_peek(tokenizer);
    if (!token || (token->type != WORD && token->type != SQSTRING))
    {
        return NULL;
    }
    token = tokenizer_next(tokenizer);

    char *string = calloc(token->length + 1, sizeof(char));
    if (!string)
    {
        return NULL;
    }

    int sPos = 0;
    int tPos = token->type == SQSTRING ? 1 : 0;
    int tLen = token->type == SQSTRING ? token->length - 1 : token->length;
    for (; tPos < tLen; sPos++, tPos++)
    {
        if (token->text[tPos] == '\\')
        {
            tPos++;
            string[sPos] = esc_map_escape(token->text[tPos]);
        }
        else
        {
            string[sPos] = token->text[tPos];
        }
    }
    AstNode *node = ast_create_node(AST_STRING);
    if (!node)
    {
        token_free(token);
        free(string);
        return NULL;
    }
    node->string.value = string;
    node->string.originalToken = token;
    return node;
}

int ast_print_string(AstNode *node, int outFd)
{
    if (!node || node->type != AST_STRING)
    {
        return 1;
    }
    dprintf(outFd, "%s", node->string.originalToken->text);
    return 0;
}
