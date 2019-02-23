primero: primero.o
	ld -m elf_i386 primero.o -o primero

primero.o:	primero.asm
	nasm -f elf primero.asm
