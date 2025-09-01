#include "../../list.h"
#include "../ast.h"
#include "pipeline.h"
#include "command.h"
#include "../../tokenizer.h"
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
        tokenizer_next(tokenizer); // consume PIPE
        AstNode *next_cmd = ast_parse_command(tokenizer);
        if (!next_cmd) {
            ast_free_node(pipeline_node);
            return NULL;
        }
        list_append(pipeline_node->pipeline.commands, next_cmd);
    }

    // Optionally parse AMP
    Token *tok = tokenizer_peek(tokenizer);
    if (tok && tok->type == AMP) {
        tokenizer_next(tokenizer); // consume AMP
        pipeline_node->pipeline.background = true;
    }

    // If no pipe was found, only one command, still valid
    return pipeline_node;
}

int ast_print_pipeline(AstNode *node, int depth) {
    if (!node || node->type != AST_PIPELINE) return 1;
    printf("%*sType: %s\n", depth * 2, "", ast_type_name(node->type));
    printf("%*sBackground: %s\n", depth * 2, "", node->pipeline.background ? "true" : "false");
    list_for_each(node->pipeline.commands, (int (*)(void *, void *))ast_print, (void *)(depth + 1));
    return 0;
}
