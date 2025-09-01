#include <stdlib.h>
#include "../list.h"
#include "ast.h"
#include "rules/string.h"
#include "rules/command.h"
#include "rules/pipeline.h"

void ast_free_list(List *list) {
    if (!list) return;

    while (list_size(list) > 0) {
        AstNode *node = (AstNode *)list_dequeue(list);
        ast_free_node(node);
    }

    list_destroy(list);
}

AstNode *ast_parse(void *tokenizer) {
    return ast_parse_pipeline(tokenizer);
}

AstNode *ast_create_node(ASTNodeType type) {
    AstNode *node = (AstNode *)malloc(sizeof(AstNode));
    if (!node) return NULL;

    node->type = type;
    switch (type) {
        case AST_PIPELINE:
            node->pipeline.commands = list_create();
            node->pipeline.background = false;
            if (!node->pipeline.commands) {
                free(node);
                return NULL;
            }
            break;
        case AST_COMMAND:
            node->command.strings = list_create();
            if (!node->command.strings) {
                free(node);
                return NULL;
            }
            break;
        case AST_STRING:
            node->string.value = NULL;
            break;
        default:
            free(node);
            return NULL;
    }

    return node;
}

void ast_free_node(AstNode *node) {
    if (!node) return;

    switch (node->type) {
        case AST_PIPELINE:
            ast_free_list(node->pipeline.commands);
            break;
        case AST_COMMAND:
            ast_free_list(node->command.strings);
            break;
        case AST_STRING:
            if (node->string.value) free(node->string.value);
            break;
        default:
            break;
    }

    free(node);
}

int ast_print(AstNode *node, int depth) {
    if (!node) return -1;

    int nextDepth = depth + 1;
    switch (node->type) {
        case AST_PIPELINE:
            ast_print_pipeline(node, depth);
            break;
        case AST_COMMAND:
            ast_print_command(node, depth);
            break;
        case AST_STRING:
            ast_print_string(node, depth);
            break;
        default:
            break;
    }

    return 0;
}

char *ast_type_name(ASTNodeType type) {
    switch (type) {
        case AST_PIPELINE: return "PIPELINE";
        case AST_COMMAND:  return "COMMAND";
        case AST_STRING:   return "STRING";
        default:          return "UNKNOWN";
    }
}
