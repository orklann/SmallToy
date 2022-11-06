#include <stdio.h>
#include <stdbool.h>
#include "tokenizer.h"

char *code ="1 + 2 * 3 * (1 + 1)";

int main(int argc, char **argv) {
    Tokenizer t;
    t.pos = 0;
    t.stream = code;
    Token token = next_token(&t);
    while (true) {
        if (token.type != TOKEN_END) {
            printf("token type: %d value:%s\n", token.type, token.value);
        } else {
            break;
        }
        token = next_token(&t);
    }
    return 0;
}
