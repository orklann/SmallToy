default: toyvm
CC=gcc
SRC=src

toyvm: $(SRC)/vm.c $(SRC)/toyvm.c
	mkdir -p build
	$(CC) -c -o build/vm.o $(SRC)/vm.c
	$(CC) -c -o build/toyvm.o $(SRC)/toyvm.c
	$(CC) -o build/toyvm build/toyvm.o build/vm.o

compiler: $(SRC)/compiler.c  $(SRC)/tokenizer.c  $(SRC)/parser.c $(SRC)/vm.c
	mkdir -p build
	$(CC) -c -o build/tokenizer.o  $(SRC)/tokenizer.c
	$(CC) -c -o build/parser.o  $(SRC)/parser.c
	$(CC) -c -o build/vm.o  $(SRC)/vm.c
	$(CC) -c -o build/compiler.o  $(SRC)/compiler.c
	$(CC) -o build/compiler build/compiler.o build/tokenizer.o build/parser.o build/vm.o
