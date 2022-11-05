#include <stdio.h>
#include "vm.h"

int main(int argc, char **argv) {
    char bytecode[256];
    FILE *f = fopen(argv[1], "rb");
    fread(bytecode, 256, 1, f);
    fclose(f);
    VM vm;
    vm.pc = 0;
    vm_eval(&vm, bytecode);
    return 0;
}
