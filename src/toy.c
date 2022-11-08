#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tokenizer.h"
#include "parser.h"
#include "vm.h"

extern char bytecode[1024];

char *code ="100 + 20 * 21 * (12 + 23)";
//char *code = "1 + 2 + 3 * 2";

int main(int argc, char **argv) {
    Tokenizer t;
    t.pos = 0;
    t.stream = code;
    int result = parse_expression(&t);
    printf(" = %d\n", result);
    strcat(bytecode, "FE");
    printf("Bytecode:\n");
    printf("%s\n", bytecode);
    VM vm;
    vm.pc = 0;
    vm.sp = 0;
    vm.a_register = 0;
    vm.b_register = 0;
    vm_eval(&vm, bytecode);
    return 0;
}
