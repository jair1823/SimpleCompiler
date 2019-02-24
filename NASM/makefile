resultado: resultado.o
	ld -m elf_i386 resultado.o -o resultado

resultado.o:	resultado.asm
	nasm -f elf resultado.asm
