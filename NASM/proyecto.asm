;Proyecto de ALU
;Proyecto ALU
;	a. Suma
;;	b. Resta
;	c. AND
;	d. OR
;	e. XOR
;	f. Complemento a 1
;	g. Complemeto a 2
;	h. Shift
;	i. Rotate
;	j. Shift con carry
;	k. Rotate con carry
%include        'functions.asm'
section .data
	;menu
	titulo: db "Proyecto ALU",10
	tituloLen: equ $ - titulo
	aSumar: db "	a. Suma",10
	aSumarLen: equ $ - aSumar
	bRestar: db "	b. Restar",10
	bRestarLen: equ $ - bRestar
	cAnd: db "	c. And",10
	cAndLen: equ $ - cAnd
	dOr: db "	d. OR",10
	dOrLen: equ $ - dOr
	eXor: db "	e. XOR",10
	eXorLen: equ $ - eXor
	fComple1: db "	f. Complemento 1",10
	fComple1Len: equ $ - fComple1
	gComple2: db "	g. Complemento 2",10
	gComple2Len: equ $ - gComple2
	hShift: db "	h. Shift",10
	hShiftLen: equ $ - hShift
	iRotate: db "	i. Rotate",10
	iRotateLen: equ $ - iRotate
	jShiftC: db "	j. Shift con carry",10
	jShiftCLen: equ $ - jShiftC
	kRotateC: db "	k. Rotate con carry",10

	kRotateCLen: equ $ - kRotateC
	opcionSalir: db "	l. salir",10
	opcionSalirLen: equ $ - opcionSalir
	pedirOpcion: db "Seleccione una opcion: ",10
	pedirOpcionLen: equ $ - pedirOpcion
	pedirDeNuevo: db "Opcion no valida, intentelo de nuevo: ",10
	pedirDeNuevoLen: equ $ - pedirDeNuevo
	;menu

	;dato1 y dato2
	dato1: db "Ingrese el primer numero: ",10
	dato1Len: equ $ -  dato1
	dato2: db "Ingrese el segundo numero: ",10
	dato2Len: equ $ -  dato2
	resultado: db "El resultado es:",10
	resultadoLen: equ $ - resultado
	;
	;negativo
	mNeg: db "-"
    mNegLen: equ $ - mNeg
	;negativo

	;opcionesParaShiftRotate
	opcionIzqDer: db "Hacia que lado",10
	opcionIzqDerLen: equ $ - opcionIzqDer

	izquierda: db "	1. Izquierda",10
	izquierdaLen: equ $ - izquierda

	derecha: db "	2. Derecha",10
	derechaLen: equ $ - derecha

	;opcionesParaShiftRotate

    ;saltoDeLinea
    saltoDeLinea: db "",10
    saltoDeLineaLen: equ $ - saltoDeLinea
    ;

    ;banderas
	carry: db "Bandera carry: "
    carryLen: equ $ - carry
    overflow: db "Bandera overflow: "
    overflowLen: equ $ - overflow
    zero: db "Bandera zero: "                   ;Toda esta parte de aquí se tiene que meter en la ALU en section .data
    zeroLen: equ $ - zero
    parity: db "Bandera parity: "
    parityLen: equ $ - parity
    signed: db "Bandera signed: "
    signedLen: equ $ - signed
    fl0: db "0",10
    flL: equ $ - fl0
    fl1: db "1",10
	;banderas

section .bss
	;menu
	opcion resb 1
	;menu
	;dato1 dato2
	num1 resb 16
	num2 resb 16
	;dato1 dato2

	;izqDer solo 1 o 2
	direccion resb 1
	;izqDer solo 1 o 2

section .text
	global _start

_start:

menu:
	mov eax, 4
    mov ebx, 1
    mov ecx, titulo
    mov edx, tituloLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, aSumar
    mov edx, aSumarLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, bRestar
    mov edx, bRestarLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, cAnd
    mov edx, cAndLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, dOr
    mov edx, dOrLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, eXor
    mov edx, eXorLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, fComple1
    mov edx, fComple1Len
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, gComple2
    mov edx, gComple2Len
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, hShift
    mov edx, hShiftLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, iRotate
    mov edx, iRotateLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, jShiftC
    mov edx, jShiftCLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, kRotateC
    mov edx, kRotateCLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, opcionSalir
    mov edx, opcionSalirLen
   	int 80h
   	mov eax, 4
    mov ebx, 1
    mov ecx, pedirOpcion
    mov edx, pedirOpcionLen
   	int 80h


pedirYrevisar:
	mov eax, 3
	mov ebx, 0
	mov ecx, opcion
	mov edx, 2
	int 80h

	cmp byte[opcion],'a';realiza suma
	je suma

	cmp byte[opcion],'b'
	je resta

	cmp byte[opcion],'c'
	je funAnd

	cmp byte[opcion],'d'
	je funOr

	cmp byte[opcion],'e'
	je funXor

	cmp byte[opcion],'f'
	je complemento1

	cmp byte[opcion],'g'
	je complemento2

	cmp byte[opcion],'h'
	je inicializar

	cmp byte[opcion],'i'
	je inicializar

	cmp byte[opcion],'j'
	je inicializar

	cmp byte[opcion],'k'
	je inicializar

	cmp byte[opcion],'l'
	je salir

	mov eax, 4
    mov ebx, 1
    mov ecx, pedirDeNuevo
    mov edx, pedirDeNuevoLen
   	int 80h

   	jmp pedirYrevisar


correcto:
	mov eax, 4
    mov ebx, 1
    mov ecx, titulo
    mov edx, tituloLen
   	int 80h
   	call impBanderas
   	jmp salir


suma:
		call pedirDatos
		mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, resultado    ;mensaje que queremos imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h
    mov eax, num1     ;movemos n1 al registro eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a decimal
    mov edx, eax    ;movemos n1 a edx
    mov eax, num2     ;movemos n2 a eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a decimal
    add edx, eax    ;agregamos n1 y n2
    mov eax, edx    ;movemos el resultado a eax
    cmp eax, 0      ;compara el numero con cero para saber si es negativo
    jl negativo     ;salta a negativo si el numero es negativo

    jmp terminar

resta:
	call pedirDatos
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, resultado    ;mensaje que queremos imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h

    mov eax, num1     ;movemos n1 al registro eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a decimal
    mov edx, eax    ;movemos n1 a edx
    mov eax, num2     ;movemos n2 a eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a decima
    sub edx, eax    ;restamos n1 con n2
    mov eax, edx    ;movemos el resultado a eax
    jmp terminar

funAnd:
	call pedirDatos
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, resultado    ;mensaje que queremos imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h
    xor ebx,ebx
    mov eax, num1   ;se guarda el número del Buffer2 en el registro eax
	call atoi		   ; y aqui se pasa ese número en Ascii a int
	mov ebx, eax	   ;luego se guarda en el regsitro en el que se necesite que este

	mov eax, num2   ; se guarda el número del Buffer1 en el registro eax
	call atoi		   ; se llama a la función Atoi par pasar el número de Ascii a int

    and eax, ebx ;Función que recibe los dos números como enteros y los compara con un AND
    and eax, ebx
	jmp terminar

funOr:
	call pedirDatos
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, resultado    ;mensaje que queremos imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h
    xor ebx,ebx
    mov eax, num1   ;se guarda el número del Buffer2 en el registro eax
	call atoi		   ; y aqui se pasa ese número en Ascii a int
	mov ebx, eax	   ;luego se guarda en el regsitro en el que se necesite que este

	mov eax, num2   ; se guarda el número del Buffer1 en el registro eax
	call atoi		   ; se llama a la función Atoi par pasar el número de Ascii a int

	or eax, ebx
	jmp terminar

funXor:
	call pedirDatos
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, resultado    ;mensaje que queremos imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h
    xor ebx,ebx
    mov eax, num1   ;se guarda el número del Buffer2 en el registro eax
	call atoi		   ; y aqui se pasa ese número en Ascii a int
	mov ebx, eax	   ;luego se guarda en el regsitro en el que se necesite que este

	mov eax, num2   ; se guarda el número del Buffer1 en el registro eax
	call atoi		   ; se llama a la función Atoi par pasar el número de Ascii a int

	xor eax, ebx
	jmp terminar

complemento1:
	call pedirUnDato
	mov eax, 4       ;se imprime el mensaje sobre el resultado que se ha obtenido
    mov ebx, 1
    mov ecx, resultado
    mov edx, resultadoLen
    int 80h

    mov eax, num1      ;se mueve n1 al registro eax
    call atoi        ;se llama a la función atoi la cual convierte de Ascii a int el n1
    not eax          ;se niega el int obtenido y que se encuentra en eax
    cmp eax, 0       ;Se compara el número con cero para saber si es menor que cero
    jl negativo      ;se salta a la etiqueta negativo si el número es menor que cero.
    jmp terminar

complemento2:
	call pedirUnDato
	mov eax, 4					;se imprime el mensaje sobre el resultado que se ha obtenido
    mov ebx, 1
    mov ecx, resultado
    mov edx, resultadoLen
    int 80h
    mov eax, num1 				;se mueve n1 al registro eax
    call atoi					;se llama a la función atoi la cual convierte de Ascii a int el n1
    neg eax						;se le hace el neg a eax y de esta forma se le hace el complemento a 2
    cmp eax, 0					;Se compara el número con cero para saber si es menor que cero
    jl negativo					;se salta a la etiqueta negativo si el número es menor que cero
    jmp terminar

inicializar:
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, opcionIzqDer  ;mensaje a imprimir
    mov edx, opcionIzqDerLen  ;largo del mensaje
    int 80h

    mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, izquierda     ;mensaje a imprimir
    mov edx, izquierdaLen  ;largo del mensaje
    int 80h

    mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, derecha    ;mensaje a imprimir
    mov edx, derechaLen ;largo del mensaje
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, pedirOpcion
    mov edx, pedirOpcionLen
   	int 80h

    mov eax, 3      ;comandos para leer
    mov ebx, 0
    mov ecx, direccion     ;se guarda en n1
    mov edx, 16
    int 80h

    mov eax, direccion     ;se mueve n1 a eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a decimal

    cmp eax, 1      ;comparamos eax con 1
    je pedirDatoSR        ;se salta a la funcion pedir si cumple que son iguales
    cmp eax, 2      ;comparamos eax con 2
    je pedirDatoSR        ;se salta a la funcion pedir si cumple que son iguales

    jmp inicializar  ;se salta a la funcion Inicializacion

pedirDatoSR:
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, dato1     ;mensaje que queremos imprimir
    mov edx, dato1Len  ;largo del mensaje
    int 80h

    mov eax, 3      ;comandos para leer input
	mov ebx, 0
	mov ecx, num1     ;se guarda el input en n1
	mov edx, 16
	int 80h

	cmp byte[opcion],'h'
	je shiftSinCarry

    cmp byte[opcion],'i'
    je roteteSinCarry

    cmp byte[opcion],'j'
    je shiftConCarry

    cmp byte[opcion],'k'
    je rotateConCarry


shiftSinCarry:
	mov eax, 4      ;comandos para escribir
    mov ebx, 1
    mov ecx, resultado    ;mensaje a imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h

    mov eax, direccion     ;mover n1 a eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a deciaml
    cmp eax, 1      ;comparar eax con 1
    je shIzq        ;saltar a shDer si son iguales

    cmp eax, 2      ;comparar eax con 2
    je shDer        ;saltar a shIzq si son iguales

shDer:
    mov eax, num1         ;mover n2 a eax
    call atoi
    shr eax, 1          ;le hacemos shift a la derecha por 1 a eax
    jmp negativo?       ;salta a negativo?

shIzq:
    mov eax, num1         ;mueve n2 a eax
    call atoi
    shl eax, 1          ;shift a la izquierda de eax por 1
    jmp negativo?       ;salto a negativo?

roteteSinCarry:
    mov eax, 4      ;comandos para escribir
    mov ebx, 1
    mov ecx, resultado    ;mensaje a imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h

    mov eax, direccion     ;movemos n1 a eax
    call atoi
    cmp eax, 1      ;comparamos eax con 1
    je roIzq        ;salta a roDer si son iguales
    cmp eax, 2      ;compara eax con 2
    je roDer        ;salta a roIzq si son iguales

roDer:
    mov eax, num1     ;mueve n2 a eax
    call atoi
    ror eax, 1      ;rota a la derecha a eax por 1
    jmp negativo?   ;salto a negativo?

roIzq:
    mov eax, num1     ;mueve n2 a eax
    call atoi
    rol eax, 1      ;rota a la izquierda a eax por 1
    jmp negativo?

shiftConCarry:
    mov eax, 4      ;comandos para escribir
    mov ebx, 1
    mov ecx, resultado    ;mensaje a imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h

    mov eax, direccion     ;mover n1 a eax
    call atoi       ;llamamos a la funcion para cambiar de ascii a deciaml
    cmp eax, 1      ;comparar eax con 1
    je shCIzq        ;saltar a shDer si son iguales
    cmp eax, 2      ;comparar eax con 2
    je shCDer        ;saltar a shIzq si son iguales

shCDer:
    mov eax, num1         ;mover n2 a eax
    call atoi
    shr eax, 1          ;le hacemos shift a la derecha por 1 a eax
     pushf           ;guarda las banderas en el stack
    jmp negativo2?       ;salta a negativo?

shCIzq:
    mov eax, num1         ;mueve n2 a eax
    call atoi
    cmp eax, 10000000000000000000000000000000b ;compara eax con el numero en binario
    jge shIzqCarr       ;salta a shIzqCarr si eax es mayor o igual
    shl eax, 1          ;hace shift a eax por 1
     pushf           ;guarda las banderas en el stack
    jmp negativo2?       ;salta a negativo?

shIzqCarr:
    mov eax, num1         ;mueve n2 a eax
    call atoi
    shl eax, 1          ;le hace shift a la izquierda a eax
    stc                 ;setea la bandera de carry
     pushf           ;guarda las banderas en el stack
    jmp negativo2?       ;salta a negativo?

rotateConCarry:
    mov eax, 4      ;comandos para escribir
    mov ebx, 1
    mov ecx, resultado    ;mensaje a imprimir
    mov edx, resultadoLen ;largo del mensaje
    int 80h

    mov eax, direccion     ;movemos n1 a eax
    call atoi
    cmp eax, 1      ;comparamos eax con 1
    je roCIzq        ;salta a roDer si son iguales
    cmp eax, 2      ;compara eax con 2
    je roCDer       ;salta a roIzq si son iguales

roCDer:
    mov eax, num1     ;mover n2 a eax
    call atoi
    clc             ;limpia el carry
    rcr eax, 1      ;rota eax a la derecha por 1
     pushf           ;guarda las banderas en el stack
    jmp negativo2?   ;salta a negativo?

roCIzq:
    mov eax, num1     ;mover n2 a eax
    call atoi
    clc
    rcl eax, 1      ;rota eax a la izquierda por 1
     pushf           ;guarda las banderas en el stack
    jmp negativo2?
;;
negativo2?:
    cmp eax, 0      ;comparar eax con 0
    jl negativo2     ;saltar a negativo si eax es menor que 0
    jmp impNumero    ;de no ser asi saltar a terminar


impNumero:
    call iprintLF   ;llama a la funcion para imprimir
    popf            ;saca las banderas guardadas en el stack
    call saltarLinea
    call impBanderas
    jmp menu ;llamada a la funcion de terminacion

negativo2:
    neg eax         ;niega eax
    push eax        ;guarda eax en el stack

    mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, mNeg   ;mensaje a imprimir
    mov edx, mNegLen    ;largo del mensaje
    int 80h

    pop eax         ;saca el eax guardado
    jmp impNumero   ;salta a impNumero

;;

negativo?:
    cmp eax, 0      ;comparar eax con 0
    jl negativo     ;saltar a negativo si eax es menor que 0
    jmp terminar    ;de no ser asi saltar a terminar

terminar:           ;imprimir el resultado y salir
		pushfd
    call    iprintLF    ; llama a la función print
    popfd

negativo:           ;imprime un caracter de negado y vuelve el numero positivo para imprimir
    neg eax         ;complemento a 2 del elemento
    push eax        ;se mete al stack el eax
    mov eax, 4
    mov ebx, 1
    mov ecx, mNeg
    mov edx, mNegLen
    int 80h
    pop eax         ;se saca el eax del stack
    jmp terminar    ;se salta a terminar

pedirDatos:
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, dato1     ;mensaje que queremos imprimir
    mov edx, dato1Len  ;largo del mensaje
    int 80h

	mov eax, 3      ;comandos para leer input
	mov ebx, 0
	mov ecx, num1     ;se guarda el input en n1
	mov edx, 16
	int 80h

    mov eax, 4      ;comando para imprimir
    mov ebx, 1
    mov ecx, dato2     ;mensaje que queremos imprimir
    mov edx, dato2Len  ;largo del mensaje
    int 80h

	mov eax, 3      ;comandos para leer input
	mov ebx, 0
	mov ecx, num2     ;se guarda el input en n2
	mov edx, 16
	int 80h
	ret

pedirUnDato:
	mov eax, 4      ;comandos para imprimir
    mov ebx, 1
    mov ecx, dato1     ;mensaje que queremos imprimir
    mov edx, dato1Len  ;largo del mensaje
    int 80h

    mov eax, 3      ;comandos para leer input
	mov ebx, 0
	mov ecx, num1     ;se guarda el input en n1
	mov edx, 16
	int 80h
	ret

impBanderas:                ;Un procedimiento que se encarga de imprimir los estados de todas las banderas
    mov eax, 4              ;Se inicializa el modo de escritura
    mov ebx, 1              ;Se declara como salida la pantalla
    mov ecx, carry
    mov edx, carryLen
    int 80h

    jc .carry           ;Se salta a la etiqueta carry si el bit de carry está activo
    jnc .noCarry        ;Se salta a la etiqueta noCarry si el bit de carry no está activo

.carry:                 ;imprime que hay carry
    mov eax, 4          ;eax en modo escritura
    mov ebx, 1          ;output de pantalla
    mov ecx, fl1        ;imprime un 1
    mov edx, flL        ;el largo del mensaje
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, overflow
    mov edx, overflowLen
    int 80h

    jo .overflow        ;Se salta a la etiqueta overflow si la bandera está activa
    jno .noverflow      ;Se salta a la etiqueta noverflow si la bandera no está activa

.noCarry:               ;imprime que no hay un carry
    mov eax, 4
    mov ebx, 1
    mov ecx, fl0        ;imprime un 0
    mov edx, flL        ;el largo del mensaje
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, overflow
    mov edx, overflowLen
    int 80h

    jo .overflow        ;Se salta a la etiqueta overflow si la bandera está activa
    jno .noverflow      ;Se salta a la etiqueta noverflow si la bandera no está activa

.overflow:              ;imprime que hay overflow
    mov eax, 4
    mov ebx, 1
    mov ecx, fl1
    mov edx, flL
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, zero
    mov edx, zeroLen
    int 80h

    jz .zero            ;Se salta a la etiqueta zero si la bandera está activa
    jnz .nozero         ;Se salta a la etiqueta nozero si la bandera no está activa

.noverflow:             ;imprime que no hay overflow
    mov eax, 4
    mov ebx, 1
    mov ecx, fl0
    mov edx, flL
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, zero
    mov edx, zeroLen
    int 80h

    jz .zero            ;Se salta a la etiqueta zero si la bandera está activa
    jnz .nozero         ;Se salta a la etiqueta nozero si la bandera no está activa

.zero:                  ;imprime que se enciende un zero de bandera
    mov eax, 4
    mov ebx, 1
    mov ecx, fl1
    mov edx, flL
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, parity
    mov edx, parityLen
    int 80h

    jp .parity          ;Se salta a la etiqueta parity si la bandera está activa
    jnp .noparity       ;Se salta a la etiqueta noparity si la bandera no está activa

.nozero:                ;imprime que no se enciende un zero de bandera
    mov eax, 4
    mov ebx, 1
    mov ecx, fl0
    mov edx, flL
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, parity
    mov edx, parityLen
    int 80h

    jp .parity          ;Se salta a la etiqueta parity si la bandera está activa
    jnp .noparity       ;Se salta a la etiqueta noparity si la bandera no está activa

.parity:                ;imprime que se enciende la bandera de paridad
    mov eax, 4
    mov ebx, 1
    mov ecx, fl1
    mov edx, flL
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, signed
    mov edx, signedLen
    int 80h

    js .signed          ;Se salta a la etiqueta signed si la bandera está activa
    jns .nosigned       ;Se salta a la etiqueta nosigned si la bandera no está activa

.noparity:              ;imprime que no se enciende la bandera de paridad
    mov eax, 4
    mov ebx, 1
    mov ecx, fl0
    mov edx, flL
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, signed
    mov edx, signedLen
    int 80h

    js .signed          ;Se salta a la etiqueta signed si la bandera está activa
    jns .nosigned       ;Se salta a la etiqueta nosigned si la bandera no está activa

.signed:                ;imprime que se enciende la bandera de signo
    mov eax, 4
    mov ebx, 1
    mov ecx, fl1
    mov edx, flL
    int 80h
    call saltarLinea

    ret                 ;retorna a la función en donde se llamó el procedimiento

.nosigned:              ;imprime que no se enciende la bandera de signo
    mov eax, 4
    mov ebx, 1
    mov ecx, fl0
    mov edx, flL
    int 80h
    call saltarLinea

    ret                 ;retorna a la función en donde se llamó el procedimiento

salir:;sale del programa
    call quit

saltarLinea:
    mov eax, 4
    mov ebx, 1
    mov ecx, saltoDeLinea
    mov edx, saltoDeLineaLen
    int 80h
    ret
