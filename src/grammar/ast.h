#ifndef AST_H
#define AST_H
#include <stdbool.h>
#include "../list.h"
#include "token.h"

typedef enum
{
    AST_PIPELINE,
    AST_COMMAND,
    AST_STRING,
    AST_SQSTRING,
    AST_WORD,
    AST_VAR_STRING,
    AST_VAR_ASSIGN
} ASTNodeType;

struct _astNode
{
    ASTNodeType type;
    union
    {
        struct
        {
            List *commands; // List of AstNode of type AST_COMMAND
            bool background;
        } pipeline;

        struct
        {
            List *var_assigns; // List of AstNode of type AST_VAR_ASSIGN
            List *strings; // List of AstNode of type AST_STRING
        } command;

        struct
        {
            struct _astNode *childNode;
        } string;

        struct
        {
            Token *idWord; // Token of type WORD without the leading $
        } var_string;

        struct
        {
            Token *sqStringToken; // Token of type SQSTRING
        } sqstring;

        struct
        {
            Token *wordToken; // Token of type WORD
        } word;

        struct
        {
            Token *varWord; // Token of type WORD
            struct _astNode *stringNode; // AstNode of type AST_STRING
        } var_assign;
    };
};

typedef struct _astNode AstNode;

AstNode *ast_create_node(ASTNodeType type);
void ast_free_node(AstNode *node);

AstNode *ast_parse(void *tokenizer);

int ast_print(AstNode *node, int outFd);

char *ast_type_name(ASTNodeType type);

#endif // AST_H