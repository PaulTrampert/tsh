#ifndef TOKEN_H
#define TOKEN_H

enum _tokenType
{
    // Primitives
    WORD,
    SQSTRING,

    // Operators
    AMP,
    PIPE,
    ASSIGN,
    OUT_AS_VAL
};

typedef enum _tokenType TokenType;

struct _token
{
    TokenType type;
    size_t length;
    char *text;
    size_t position;
};

typedef struct _token Token;

Token *token_new(TokenType type, const char *text, size_t length, size_t position);
void token_free(Token *token);

#endif // TOKEN_H