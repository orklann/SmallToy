#include <stdio.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "parser.h"

char *code ="100 + 20 * 21 * (12 + 23)";
//char *code = "1 + 2 * 3";

int main(int argc, char **argv) {
    Tokenizer t;
    t.pos = 0;
    t.stream = code;
    /*Token token = next_token(&t);
    while (token.type != TOKEN_END) {
        printf("%s ", token.value);
        token = next_token(&t);
    }*/
    int result = parse_expression(&t);
    printf(" = %d\n", result);
    return 0;
}
