#include <stdlib.h>
#include "../exit_codes.h"
#include "../list.h"
#include "ast.h"
#include "rules/string.h"
#include "rules/command.h"
#include "rules/pipeline.h"
#include "rules/sqstring.h"
#include "rules/var_assign.h"
#include "rules/var_string.h"
#include "rules/word.h"

void ast_free_list(List *list)
{
    if (!list)
        return;

    while (list_size(list) > 0)
    {
        AstNode *node = (AstNode *)list_dequeue(list);
        ast_free_node(node);
    }

    list_destroy(list);
}

AstNode *ast_parse(void *tokenizer)
{
    return ast_parse_pipeline(tokenizer);
}

AstNode *ast_create_node(ASTNodeType type)
{
    AstNode *node = (AstNode *)malloc(sizeof(AstNode));
    if (!node)
        exit(EOOM);

    node->type = type;
    switch (type)
    {
    case AST_PIPELINE:
        node->pipeline.commands = list_create();
        node->pipeline.background = false;
        if (!node->pipeline.commands)
        {
            free(node);
            return NULL;
        }
        break;
    case AST_COMMAND:
        node->command.var_assigns = list_create();
        if (!node->command.var_assigns)
        {
            free(node);
            return NULL;
        }
        node->command.strings = list_create();
        if (!node->command.strings)
        {
            list_destroy(node->command.var_assigns);
            free(node);
            return NULL;
        }
        break;
    case AST_STRING:
        node->string.childNode = NULL;
        break;
    case AST_VAR_STRING:
        node->var_string.idWord = NULL;
        break;
    case AST_SQSTRING:
        node->sqstring.sqStringToken = NULL;
        break;
    case AST_WORD:
        node->word.wordToken = NULL;
        break;
    case AST_VAR_ASSIGN:
        node->var_assign.varWord = NULL;
        node->var_assign.stringNode = NULL;
        break;

    default:
        free(node);
        return NULL;
    }

    return node;
}

void ast_free_node(AstNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case AST_PIPELINE:
        ast_free_list(node->pipeline.commands);
        break;
    case AST_COMMAND:
        ast_free_list(node->command.var_assigns);
        ast_free_list(node->command.strings);
        break;
    case AST_STRING:
        if (node->string.childNode)
            ast_free_node(node->string.childNode);
        break;
    case AST_VAR_STRING:
        if (node->var_string.idWord)
            token_free(node->var_string.idWord);
        break;
    case AST_SQSTRING:
        if (node->sqstring.sqStringToken)
            token_free(node->sqstring.sqStringToken);
        break;
    case AST_WORD:
        if (node->word.wordToken)
            token_free(node->word.wordToken);
        break;
    case AST_VAR_ASSIGN:
        if (node->var_assign.varWord)
            token_free(node->var_assign.varWord);
        if (node->var_assign.stringNode)
            ast_free_node(node->var_assign.stringNode);
        break;
    default:
        break;
    }

    free(node);
}

int ast_print(AstNode *node, int outFd)
{
    if (!node)
        return -1;

    switch (node->type)
    {
    case AST_PIPELINE:
        ast_print_pipeline(node, outFd);
        break;
    case AST_COMMAND:
        ast_print_command(node, outFd);
        break;
    case AST_STRING:
        ast_print_string(node, outFd);
        break;
    case AST_VAR_STRING:
        ast_print_var_string(node, outFd);
        break;
    case AST_SQSTRING:
        ast_print_sqstring(node, outFd);
        break;
    case AST_WORD:
        ast_print_word(node, outFd);
        break;
    case AST_VAR_ASSIGN:
        ast_print_var_assign(node, outFd);
    default:
        break;
    }

    return 0;
}

char *ast_type_name(ASTNodeType type)
{
    switch (type)
    {
    case AST_PIPELINE:
        return "PIPELINE";
    case AST_COMMAND:
        return "COMMAND";
    case AST_STRING:
        return "STRING";
    case AST_VAR_STRING:
        return "VAR_STRING";
    default:
        return "UNKNOWN";
    }
}
