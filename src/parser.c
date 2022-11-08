#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tokenizer.h"
#include "parser.h"
#include "vm.h"

// Hardcoded bytecode buffer;
char bytecode[1024] = "";

char* to_hex(char *str) {
    char *hex = (char*)malloc(3);
    int i = atoi(str);
    sprintf(hex, "%.2X", i);
    return hex;
}

void emit_code_load_a(char *v) {
    char code[5];
    char *hex = to_hex(v);
    sprintf(code, "01%s", hex);
    strcat(bytecode, code);
    free(hex);
}

void emit_code_push_a() {
    strcat(bytecode, "06");
}

void emit_code_pop_a() {
    strcat(bytecode, "07");
}

void emit_code_push_b() {
    strcat(bytecode, "08");
}

void emit_code_pop_b() {
    strcat(bytecode, "09");
}

void emit_code_add_ab() {
    strcat(bytecode, "0A");
}

void emit_code_multiple_ab() {
    strcat(bytecode, "0B");
}

int parse_expression(Tokenizer *t) {
    unsigned int result;
    emit_code_push_a();

    result = parse_term(t);
    emit_code_push_b();
    result += parse_expression2(t);
    emit_code_pop_a();
    emit_code_add_ab();

    emit_code_push_a();
    emit_code_pop_b();

    emit_code_pop_a();
    return result;
}

int parse_expression2(Tokenizer *t) {
    Token token = peek_token(t);
    if (token.type == TOKEN_ADD_OPERATOR) {
        //printf("+");
        token = next_token(t);
        emit_code_push_a();

        int result = parse_term(t);
        emit_code_push_b();
        result += parse_expression2(t);
        emit_code_pop_a();
        emit_code_add_ab();
        emit_code_push_a();
        emit_code_pop_b();

        emit_code_pop_a();
        return result;
    }
    emit_code_push_a();
    emit_code_load_a("00");
    emit_code_push_a();
    emit_code_pop_b();
    emit_code_pop_a();
    return 0;
}

int parse_term(Tokenizer *t) {
    emit_code_push_a();

    unsigned int result = parse_factor(t);
    emit_code_push_b();
    result *= parse_term2(t);
    emit_code_pop_a();
    emit_code_multiple_ab();
    emit_code_push_a();
    emit_code_pop_b();

    emit_code_pop_a();
    return result;
}

int parse_term2(Tokenizer *t) {
    Token token = peek_token(t);
    if (token.type == TOKEN_MUL_OPERATOR) {
        token = next_token(t);
        //printf("*");
        emit_code_push_a();

        unsigned int result = parse_factor(t);
        emit_code_push_b();
        result *= parse_term2(t);
        emit_code_pop_a();
        emit_code_multiple_ab();
        emit_code_push_a();
        emit_code_pop_b();

        emit_code_pop_a();
        return result;
    }
    emit_code_push_a();
    emit_code_load_a("01");
    emit_code_push_a();
    emit_code_pop_b();
    emit_code_pop_a();
    return 1;
}

int parse_factor(Tokenizer *t) {
    Token token = next_token(t);
    if (token.type == TOKEN_LEFT_PARENTHESIS) {
        //printf("(");
        emit_code_push_a();
        unsigned int result = parse_expression(t);
        emit_code_pop_a();
        next_token(t);
        //printf(")");
        return result;
    } else if (token.type == TOKEN_NUMBER) {
        //printf("%s", token.value);
        emit_code_push_a();
        emit_code_load_a(token.value);
        emit_code_push_a();
        emit_code_pop_b();
        emit_code_pop_a();
        return atoi((const char *)token.value);
    }
}
