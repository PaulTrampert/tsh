#include "../../list.h"
#include "../ast.h"
#include "pipeline.h"
#include "command.h"
#include "../tokenizer.h"
#include <stdio.h>

AstNode *ast_parse_pipeline(void *tokenizer) {
    AstNode *pipeline_node = ast_create_node(AST_PIPELINE);
    if (!pipeline_node) return NULL;

    // Parse first command
    AstNode *cmd = ast_parse_command(tokenizer);
    if (!cmd) {
        ast_free_node(pipeline_node);
        return NULL;
    }
    list_append(pipeline_node->pipeline.commands, cmd);

    while (1) {
        Token *tok = tokenizer_peek(tokenizer);
        if (!tok || tok->type != PIPE) break;
        tok = tokenizer_next(tokenizer); // consume PIPE
        AstNode *next_cmd = ast_parse_command(tokenizer);
        if (!next_cmd) {
            ast_free_node(pipeline_node);
            fprintf(stderr, "Missing command after '|' at position %d\n", tok->position);
            token_free(tok);
            return NULL;
        }
        list_append(pipeline_node->pipeline.commands, next_cmd);
    }

    // Optionally parse AMP
    Token *tok = tokenizer_peek(tokenizer);
    if (tok && tok->type == AMP) {
        token_free(tokenizer_next(tokenizer)); // consume AMP
        pipeline_node->pipeline.background = true;
    }

    // If no pipe was found, only one command, still valid
    return pipeline_node;
}

int ast_print_pipeline(AstNode *node, int outFd) {
    if (!node || node->type != AST_PIPELINE) return 1;
    
    ListIterator *it = list_iterator_create(node->pipeline.commands);
    bool first = true;
    while (list_iterator_has_next(it)) {
        if (!first) {
            dprintf(outFd, " | ");
        }
        AstNode *childNode = list_iterator_next(it);
        ast_print(childNode, outFd);
        first = false;
    }

    list_iterator_destroy(it);
    if (node->pipeline.background) {
        dprintf(outFd, " &");
    }

    return 0;
}
