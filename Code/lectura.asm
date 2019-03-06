;_______________________________________________ Encabezado ________________________________________________
%define MAXBYTES 2048

section .bss
	B resb MAXBYTES
	A resb MAXBYTES
	_Temp1 resb MAXBYTES

section .data
	menos db 45

section .text
	global _start

;_________________________________________________ Macros __________________________________________________
%macro suma 3
	mov eax, %1
	mov ebx, %2
	add eax, ebx
	mov [%3], eax
%endmacro

%macro resta 3
	mov eax, %1
	mov ebx, %2
	sub eax, ebx
	mov [%3], eax
%endmacro

%macro imprimirMenos 0
	mov eax, 4
	mov ebx, 1
	mov ecx, menos
	mov edx, 1
	int 80h
%endmacro

%macro leer 1
	mov ebp, 0
	mov eax, 3
	mov ebx, 0
	mov ecx, %1
	mov edx, MAXBYTES
	int 80h
	call guardarEntrada
	mov [%1], eax
%endmacro

%macro escribir 1
	mov eax, %1
	call verificarNegativo
	call iprintLF
%endmacro

%macro guardar 2
	mov eax, %1
	mov [%2], eax
%endmacro

%macro skip 1
	mov ebp, %1
	cmp ebp, 0
%endmacro

%macro salir 0
	mov eax, 1
	mov ebx, 0
	int 80h
%endmacro

;_________________________________________________ Código __________________________________________________
_start:
	leer B
	skip [B]
	jz _Condi1
	guardar 4, _Temp1
	jmp _contin1
	_Condi1:
	guardar 10, _Temp1
	jmp _contin1
	_contin1:
	guardar [_Temp1], A
	escribir [A]
	salir

;________________________________________________ Funciones ________________________________________________
guardarEntrada:
	mov ebp, 0
	mov eax, ecx
	call atoi
	cmp ebp, 0
	je .guardar
	neg eax
	.guardar:
		ret

verificarNegativo:
	cmp eax, 0
	jge .return
	push eax
	imprimirMenos
	pop eax
	neg eax
	.return:
		ret

; void iprint(Integer number)
; Función que imprime enteros (itoa)
iprint:
    push    eax             ; guardar el valor de eax en el stack para reincorporarlo después de que la función corra
    push    ecx             ; guardar el valor de ecx en el stack para reincorporarlo después de que la función corra
    push    edx             ; guardar el valor de edx en el stack para reincorporarlo después de que la función corra
    push    esi             ; guardar el valor de esi en el stack para reincorporarlo después de que la función corra
    mov     ecx, 0          ; contador que dice cuantos bytes hay que imprimir al final
divideLoop:
    inc     ecx             ; cuenta cada byte para imprimir - número de caracteres
    mov     edx, 0          ; se vacia edx
    mov     esi, 10         ; mov 10 a esi
    idiv    esi             ; se divide eax entre esi
    add     edx, 48         ; convierte edx a su representación en Ascii - edx mantiene un recordatorio después de realizar la división
    push    edx             ; push edx (representación en string del entero) en el stack
    cmp     eax, 0          ; se pregunta si se puede seguir dividiendo el entero
    jnz     divideLoop      ; si no es cero salta a la etiqueta de divideLoop
printLoop:
    dec     ecx             ; hace una cuenta regresiva de cada byte que se hac puesto en el stack
    mov     eax, esp        ; mov del puntero del stack al eax para imprimir
    call    sprint          ; se llama a la función que imprime strings
    pop     eax             ; se remueve el ultimo caracter del stack para mover el esp hacaia adelante
    cmp     ecx, 0          ; se verifica si ya se han impreso todos los bytes que estaban en el stack
    jnz     printLoop       ; si no es zero se salta a la etiqueta de printLoop
    pop     esi             ; se reestablece el valor de esi que se habia puesto en el stack al inicio
    pop     edx             ; se reestablece el valor de edx que se habia puesto en el stack al inicio
    pop     ecx             ; se reestablece el valor de ecx que se habia puesto en el stack al inicio
    pop     eax             ; se reestablece el valor de eax que se habia puesto en el stack al inicio
    ret

; void iprintLF(Integer number)
; Función que imprime enteros desde una línea de avance(itoa)
iprintLF:
    call    iprint          ; llama a la función que imprime enteros
    push    eax             ; guarda eax en el stack para guradar su valor mientras se usa el registro eax en la función
    mov     eax, 0Ah        ; mov 0Ah a eax - 0Ah es el caracter Ascii para una línea de avance
    push    eax             ; push de la linea de avance al stack para así obtener la dirección
    mov     eax, esp        ; se mueve la dirección del actual puntero del stack a eax para sprint
    call    sprint          ; se llama a la función sprint
    pop     eax             ; se remueve el caracter de la linea de avance del stack
    pop     eax             ; se reestablece el valor original que tenía eax antes de que se llamara a la función
    ret

; int slen(mensaje en string)
; Función que calcula el largo de un string
slen:
    push    ebx
    mov     ebx, eax
nextchar:
    cmp     byte [eax], 0
    jz      finished
    inc     eax
    jmp     nextchar
finished:
    sub     eax, ebx
    pop     ebx
    ret

; void sprint(String message)
; Función que imprime string
sprint:
    push    edx
    push    ecx
    push    ebx
    push    eax
    call    slen
    mov     edx, eax
    pop     eax
    mov     ecx, eax
    mov     ebx, 1
    mov     eax, 4
    int     80h
    pop     ebx
    pop     ecx
    pop     edx
    ret

; int atoi(Integer number)
; Función que convierte de Ascii a entero(atoi)
atoi:
    push    ebx             ; guardar el valor de ebx en el stack para reincorporarlo después de que la función corra
    push    ecx             ; guardar el valor de ecx en el stack para reincorporarlo después de que la función corra
    push    edx             ; guardar el valor de edx en el stack para reincorporarlo después de que la función corra
    push    esi             ; guardar el valor de esi en el stack para reincorporarlo después de que la función corra
    mov     esi, eax        ; mueve el puntero que esta en eax a esi(el número a convertir)
    mov     eax, 0          ; inicializa el registro eax con el valor decimal de cero
    mov     ecx, 0          ; inicializa el registro ecx con el valor decimal de cero
.multiplyLoop:
    xor     ebx, ebx        ; reinicia los bytes más bajos y altos de ebx para que sean cero
    mov     bl, [esi+ecx]   ; mueve un solo byte a la mitad de abajo del registro ebx
    cmp     bl, 45
    je      .flag
    cmp     bl, 48          ; compara la mitad de abajo del registro ebx con el valor ascii 48(char value 0)
    jl      .finished       ; salta si es menor a la etiqueta del final
    cmp     bl, 57          ; compara el valor de la parte baja del registro ebx con el valor ascii 57(char value 9)
    jg      .finished       ; salta si es mayor a la etiqueta del final
    cmp     bl, 10          ; compara el valor de la parte baja del registro ebx con el valor ascii 10 (caracter de la linea de avance)
    je      .finished       ; salta si es igual, a la etiqueta del final
    cmp     bl, 0           ; ccompara el valor de la parte baja del registro ebx  con el valor ascii 0 (final del string)
    jz      .finished       ; salta si es cero a la etiqueta del fnal
    sub     bl, 48          ; convierte la mitad menor del registro ebx a la representación deciaml del valor ascii
    add     eax, ebx        ; add ebx al valor entero en eax
    mov     ebx, 10         ; mueve el valor decimal 10 al ebx
    mul     ebx             ; multiplica eax por ebx para obtener un valor de campo
    inc     ecx             ; incrementar ecx (el registro de contador)
    jmp     .multiplyLoop   ; se continua en el ciclo de multiplicación
.flag:
    mov     ebp, 1
    inc     ecx             ; incrementar ecx (el registro de contador)
    jmp     .multiplyLoop   ; se continua en el ciclo de multiplicación
.finished:
    mov     ebx, 10         ; se mueve le valor decimal 10 a ebx
    div     ebx             ; se divide eax entre el valor en ebx (en este caso 10)
    pop     esi             ; se reestablece el valor de esi que se habia puesto en el stack al inicio
    pop     edx             ; se reestablece el valor de edx que se habia puesto en el stack al inicio
    pop     ecx             ; se reestablece el valor de ecx que se habia puesto en el stack al inicio
    pop     ebx             ; se reestablece el valor de ebx que se habia puesto en el stack al inicio
    ret