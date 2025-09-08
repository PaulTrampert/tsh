#include "string.h"

#include "dqstring.h"
#include "sqstring.h"
#include "var_string.h"
#include "word.h"

AstNode *ast_parse_string(void *tokenizer)
{
    AstNode *childNode = ast_parse_var_string(tokenizer);
    if (!childNode) childNode = ast_parse_dqstring(tokenizer);
    if (!childNode) childNode = ast_parse_sqstring(tokenizer);
    if (!childNode) childNode = ast_parse_word(tokenizer);
    if (childNode)
    {
        AstNode *node = ast_create_node(AST_STRING);
        if (!node)
        {
            ast_free_node(childNode);
            return NULL;
        }
        node->string.childNode = childNode;
        return node;
    }
    return NULL;
}

int ast_print_string(AstNode *node, int outFd)
{
    if (!node || node->type != AST_STRING || !node->string.childNode)
    {
        return 1;
    }
    return ast_print(node->string.childNode, outFd);
}
