#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "../../tokenizer.h"
#include "../../esc_map.h"

AstNode *ast_parse_string(void *tokenizer) {
    Token *token = tokenizer_peek(tokenizer);
    if (!token || (token->type != UQSTRING && token->type != SQSTRING)) {
        return NULL;
    }
    token = tokenizer_next(tokenizer);

    char *string = calloc(token->length + 1, sizeof(char));
    if (!string) {
        return NULL;
    }

    int sPos = 0;
    int tPos = token->type == SQSTRING ? 1 : 0;
    int tLen = token->type == SQSTRING ? token->length - 2 : token->length;
    for (; sPos < tLen; sPos++, tPos++) {
        if (token->text[tPos] == '\\') {
            tPos++;
            string[sPos] = esc_map_escape(token->text[tPos]);
        } else {
            string[sPos] = token->text[tPos];
        }
    }
    AstNode *node = ast_create_node(AST_STRING);
    if (!node) {
        free(string);
        return NULL;
    }
    node->string.value = string;
    return node;
}

int ast_print_string(AstNode *node, int depth) {
    if (!node || node->type != AST_STRING) {
        return 1;
    }
    printf("%*sType: %s - %s\n", depth * 2, "", ast_type_name(node->type), node->string.value);
    return 0;
}
