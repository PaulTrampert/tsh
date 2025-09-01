#ifndef AST_H
#define AST_H
#include <stdbool.h>
#include "../list.h"
#include "token.h"

typedef enum {
    AST_PIPELINE,
    AST_COMMAND,
    AST_STRING
} ASTNodeType;

struct _astNode {
    ASTNodeType type;
    union {
        struct {
            List *commands; // List of AstNode of type AST_COMMAND
            bool background;
        } pipeline;

        struct {
            List *strings; // List of AstNode of type AST_STRING
        } command;

        struct {
            char *value;
        } string;
    }; 
};

typedef struct _astNode AstNode;

AstNode *ast_create_node(ASTNodeType type);
void ast_free_node(AstNode *node);

AstNode *ast_parse(void *tokenizer);

int ast_print(AstNode *node, int depth);

char *ast_type_name(ASTNodeType type);

#endif // AST_H