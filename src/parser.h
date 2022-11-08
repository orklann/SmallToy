#include "tokenizer.h"

#ifndef _PARSER_H
#define _PARSER_H

int parse_expression(Tokenizer *t);
int parse_term(Tokenizer *t);
int parse_expression2(Tokenizer *t);
int parse_term2(Tokenizer *t);
int parse_factor(Tokenizer *t);
char* to_hex(char *str);
#endif // _PARSER_H
