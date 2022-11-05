default: toyvm
CC=gcc

toyvm: vm.c toyvm.c
	$(CC) -c -o build/vm.o vm.c
	$(CC) -c -o build/toyvm.o toyvm.c
	$(CC) -o build/toyvm build/toyvm.o build/vm.o
