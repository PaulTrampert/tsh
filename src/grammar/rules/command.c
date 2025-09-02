#include <stdio.h>
#include "../../list.h"
#include "../ast.h"
#include "command.h"
#include "string.h"

AstNode *ast_parse_command(void *tokenizer)
{
    AstNode *node = ast_create_node(AST_COMMAND);
    if (!node)
    {
        return NULL;
    }

    while (1)
    {
        AstNode *string_node = ast_parse_string(tokenizer);
        if (!string_node)
        {
            break;
        }
        if (list_append(node->command.strings, string_node) != 0)
        {
            ast_free_node(string_node);
            ast_free_node(node);
            return NULL;
        }
    }

    if (list_size(node->command.strings) == 0)
    {
        ast_free_node(node);
        return NULL;
    }

    return node;
}

int ast_print_command(AstNode *node, int outFd)
{
    if (!node || node->type != AST_COMMAND)
    {
        return 1;
    }

    ListIterator *it = list_iterator_create(node->command.strings);
    bool first = true;
    while (list_iterator_has_next(it))
    {
        if (!first)
        {
            dprintf(outFd, " ");
        }
        AstNode *childNode = list_iterator_next(it);
        ast_print(childNode, outFd);
        first = false;
    }

    list_iterator_destroy(it);
    return 0;
}
