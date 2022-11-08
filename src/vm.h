typedef struct {
    unsigned int a_register;
    unsigned int b_register;
    unsigned int pc;
    unsigned int stack[256];
    unsigned int sp;
} VM;

void vm_eval(VM *vm, char *bytecode);
