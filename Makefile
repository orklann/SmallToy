default: toyvm
CC=gcc

toyvm: vm.c toyvm.c
	mkdir -p build
	$(CC) -c -o build/vm.o vm.c
	$(CC) -c -o build/toyvm.o toyvm.c
	$(CC) -o build/toyvm build/toyvm.o build/vm.o

compiler: compiler.c tokenizer.c parser.c
	mkdir -p build
	$(CC) -c -o build/tokenizer.o tokenizer.c
	$(CC) -c -o build/parser.o parser.c
	$(CC) -c -o build/compiler.o compiler.c
	$(CC) -o build/compiler build/compiler.o build/tokenizer.o build/parser.o
