%include        'functions.asm'
section .bss
  result  resw  2

section .text
  global _start

_start:
  ; Guardamos los numeros en los registros eax y ebx
  mov eax, 30
  mov ebx, 5
  add eax, ebx
  jmp terminar

terminar:           ;imprimir el resultado y salir
		pushfd
    call    iprintLF    ; llama a la función print
    popfd
    jmp salir

salir:
    mov eax,1            ; The system call for exit (sys_exit)
    mov ebx,0            ; Exit with return code of 0 (no error)
    int 80h;
