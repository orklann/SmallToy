#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "parser.h"

int parse_expression(Tokenizer *t) {
    unsigned int result;
    result = parse_term(t) + parse_expression2(t);
    return result;
}

int parse_expression2(Tokenizer *t) {
    Token token = peek_token(t);
    if (token.type == TOKEN_ADD_OPERATOR) {
        printf("+");
        token = next_token(t);
        int result = parse_term(t) + parse_expression2(t);
        return result;
    }
    return 0;
}

int parse_term(Tokenizer *t) {
    unsigned int result = parse_factor(t) * parse_term2(t);
    return result;
}

int parse_term2(Tokenizer *t) {
    Token token = peek_token(t);
    if (token.type == TOKEN_MUL_OPERATOR) {
        token = next_token(t);
        printf("*");
        unsigned int result = parse_factor(t) * parse_term2(t);
        return result;
    }
    return 1;
}

int parse_factor(Tokenizer *t) {
    Token token = next_token(t);
    if (token.type == TOKEN_LEFT_PARENTHESIS) {
        printf("(");
        unsigned int result = parse_expression(t);
        next_token(t);
        printf(")");
        return result;
    } else if (token.type == TOKEN_NUMBER) {
        printf("%s", token.value);
        return atoi((const char *)token.value);
    }
}
