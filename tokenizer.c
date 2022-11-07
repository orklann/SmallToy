#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tokenizer.h"

char next_char(Tokenizer *t) {
    if (t->pos > strlen(t->stream) - 1) {
        return '\0';
    }
    char ch = *(t->stream + t->pos);
    t->pos++;
    return ch;
}

char peek_char(Tokenizer *t) {
    char ch = *(t->stream + t->pos);
    return ch;
}

bool is_digit(char ch) {
    switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
    }
    return false;
}

Token next_token(Tokenizer *t) {
    Token token;
    bool parsing_number = false;
    char value[256];
    char ch = next_char(t);
    while (true) {
        if (ch == 0) {
            token.type = TOKEN_END;
            token.value[0] = '\0';
            return token;
        }

        if (ch != ' '){
            switch (ch) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (!parsing_number) {
                        parsing_number = true;
                        value[0] = '\0';
                    }
                    char digit_str[2];
                    digit_str[0] = ch;
                    digit_str[1] = '\0';
                    strcat(value, digit_str);
                    if (parsing_number && !is_digit(peek_char(t))) {
                        parsing_number = false;
                        token.type = TOKEN_NUMBER;
                        sprintf(token.value, "%s", value);
                        return token;
                    }
                    break;
                case '+':
                    token.type = TOKEN_ADD_OPERATOR;
                    token.value[0] = '+';
                    token.value[1] = '\0';
                    return token;
                case '*':
                    token.type = TOKEN_MUL_OPERATOR;
                    token.value[0] = '*';
                    token.value[1] = '\0';
                    return token;
                case '(':
                    token.type = TOKEN_LEFT_PARENTHESIS;
                    token.value[0] = '(';
                    token.value[1] = '\0';
                    return token;
                case ')':
                    token.type = TOKEN_RIGHT_PARENTHESIS;
                    token.value[0] = ')';
                    token.value[1] = '\0';
                    return token;
                default:
                    break;
            }
        }

        ch = next_char(t);
    }
}

Token peek_token(Tokenizer *tokenizer) {
    unsigned int saved_pos = tokenizer->pos;
    Token token = next_token(tokenizer);
    tokenizer->pos = saved_pos;
    return token;
}
