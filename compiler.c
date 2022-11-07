#include <stdio.h>
#include <stdbool.h>
#include "tokenizer.h"
#include "parser.h"

char *code ="1 + 2 * 3 * (1 + 1)";
//char *code = "1 + 2 * 3";

int main(int argc, char **argv) {
    Tokenizer t;
    t.pos = 0;
    t.stream = code;
    int result = parse_expression(&t);
    printf(" = %d\n", result);
    return 0;
}
