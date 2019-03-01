%include 'functions.asm'
%define MAXBYTES 2048

section .bss
	A resb MAXBYTES

section .data
	menos db 45

section .text
	global _start

_start:
	mov ebp, 0
	mov eax, 3
	mov ebx, 0
	mov ecx, A
	mov edx, MAXBYTES
	int 80h
	mov eax, ecx
	call atoi
	cmp ebp, 0
	je imprimir
	neg eax

imprimir: 
	call verificarNegativo
	call iprintLF
	mov eax, 1
	mov ebx, 0
	int 80h

verificarNegativo:
	cmp eax, 0
	jge .return
	push eax
	mov eax, 4
	mov ebx, 1
	mov ecx, menos
	mov edx, 1
	int 80h
	pop eax
	neg eax
	.return:
		ret