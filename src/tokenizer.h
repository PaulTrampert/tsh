#ifndef TOKENIZER_H
#define TOKENIZER_H

enum TokenType {
    // Primitives
    UQSTRING, SQSTRING, NUMBER,

    // Operators
    AMP, PIPE, BANG, DOLLAR, PLUS, MINUS, GT, LT, EQ, GTE, LTE, EQEQ, FSLASH, BSLASH,

    // Groupers
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACK, RBRACK
};

struct _token {
    enum TokenType type;
    int length;
    char *text;
};

typedef struct _token Token;

void *tokenizer_init(char *inputStr, int inputLen);

Token *tokenizer_next(void *tokenizer);

void tokenizer_finalize(void *tokenizer);

#endif // TOKENIZER_H