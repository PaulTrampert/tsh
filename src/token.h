#ifndef TOKEN_H
#define TOKEN_H

enum _tokenType {
    // Primitives
    UQSTRING, SQSTRING, NUMBER,

    // Operators
    AMP, PIPE, BANG, DOLLAR, PLUS, MINUS, GT, LT, EQ, GTE, LTE, EQEQ, FSLASH,

    // Groupers
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACK, RBRACK
};

typedef enum _tokenType TokenType;

struct _token {
    TokenType type;
    int length;
    char *text;
};

typedef struct _token Token;

Token *token_new(TokenType type, const char *text, int length);
void token_free(Token *token);

#endif // TOKEN_H