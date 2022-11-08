#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vm.h"


bool is_opcode(char *buf, char* opcode) {
    if (strcmp(buf, opcode) == 0) {
        return true;
    }
    return false;
}

unsigned int vm_get_operand(VM *vm, char *bytecode) {
    char str[3];
    unsigned char a1 = *(bytecode + vm->pc);
    vm->pc++;
    unsigned char a2 = *(bytecode + vm->pc);
    vm->pc++;
    sprintf(str, "%c%c", a1, a2);
    unsigned int operand;
    sscanf(str, "%x", &operand);
    return operand;
}

void vm_eval(VM *vm, char *bytecode) {
    unsigned int len = strlen(bytecode);
    while (vm->pc <= len - 1) {
        char opcode[3];
        unsigned char opcode1 = *(bytecode + vm->pc);
        vm->pc++;
        unsigned char opcode2 = *(bytecode + vm->pc);
        vm->pc++;
        sprintf(opcode, "%c%c", opcode1, opcode2);
        if (is_opcode(opcode, "01")) { // Opcode 01
            unsigned int operand = vm_get_operand(vm, bytecode);
            vm->a_register = operand;
        } else if (is_opcode(opcode, "04")) { // Opcode 04
            unsigned int operand = vm_get_operand(vm, bytecode);
            vm->a_register += operand;
        } else if (is_opcode(opcode, "05")) { // Opcode 05
            unsigned int operand = vm_get_operand(vm, bytecode);
            vm->a_register *= operand;
        } else if (is_opcode(opcode, "FF")) { // Opcode FF
            printf("%d\n", vm->a_register);
        } else if (is_opcode(opcode, "06")) { // Opcode 06
            vm->stack[vm->sp] = vm->a_register;
            vm->sp++;
        } else if (is_opcode(opcode, "07")) { // Opcode 07
            vm->a_register = vm->stack[vm->sp - 1];
            vm->sp--;
        } else if (is_opcode(opcode, "08")) { // Opcode 08
            vm->stack[vm->sp] = vm->b_register;
            vm->sp++;
        } else if (is_opcode(opcode, "09")) { // Opcode 09
            vm->b_register = vm->stack[vm->sp - 1];
            vm->sp--;
        } else if (is_opcode(opcode, "0A")) { // Opcode 0A
            vm->a_register += vm->b_register;
        } else if (is_opcode(opcode, "0B")) { // Opcode 0B
            vm->a_register *= vm->b_register;
        } else if (is_opcode(opcode, "FE")) { // Opcode FE
            printf("%d\n", vm->b_register);
        }
    }
}
