typedef struct {
    unsigned int a_register;
    unsigned int pc;
} VM;

void vm_eval(VM *vm, char *bytecode);
