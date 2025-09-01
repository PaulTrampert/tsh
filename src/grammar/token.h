#ifndef TOKEN_H
#define TOKEN_H

enum _tokenType {
    // Primitives
    UQSTRING, SQSTRING,

    // Operators
    AMP, PIPE
};

typedef enum _tokenType TokenType;

struct _token {
    TokenType type;
    int length;
    char *text;
    int position;
};

typedef struct _token Token;

Token *token_new(TokenType type, const char *text, int length, int position);
void token_free(Token *token);

#endif // TOKEN_H