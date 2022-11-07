#include <stdio.h>

#ifndef _TOKENIZER_H
#define _TOKENIZER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_LEFT_PARENTHESIS,
    TOKEN_RIGHT_PARENTHESIS,
    TOKEN_ADD_OPERATOR,
    TOKEN_MUL_OPERATOR,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    char value[256];
} Token;

typedef struct {
    char *stream;
    unsigned int pos;
} Tokenizer;

char next_char(Tokenizer *tokenizer);
char peek_char(Tokenizer *tokenizer);
Token next_token(Tokenizer *tokenizer);
Token peek_token(Tokenizer *tokenizer);
#endif // _TOKENIZER_H
