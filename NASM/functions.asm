;___________________________ Funciones _________________________

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


;------------------------------------------
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


;------------------------------------------
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


;------------------------------------------
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


;------------------------------------------
; void sprintLF(String message)
; Función que imprime Strings mediante una línea de avance ??
sprintLF:
    call    sprint

    push    eax
    mov     eax, 0AH
    push    eax
    mov     eax, esp
    call    sprint
    pop     eax
    pop     eax
    ret


;------------------------------------------
; void exit()
; Se sale del programa y se restauran recursos(resultados)
quit:
    mov     ebx, 0
    mov     eax, 1
    int     80h
    ret

;------------------------------------------
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

;------------------------------------------
;  Decimal to Binary function
;
dTB:                        ;necesita a huevo que sea un int(NO esta completamente probado)
    push    ebx             ; preserve ebx on the stack to be restored after function runs
    push    ecx             ; preserve ecx on the stack to be restored after function runs
    push    edx             ; preserve edx on the stack to be restored after function runs
    push    esi             ; preserve esi on the stack to be restored after function runs
    push    esp             ; preserve esp on the stack to be restored after function runs
    mov     edx, 0          ;Le movemos un 10 a ebx
    mov     esp, 0          ;usaremos esp como contador comenzando en 0

.divisionLoop:
    cmp     edx, 32         ;compara eax(cociente de la division) con 0(si ya no se puede dividir mas)
    je      .inic           ;si son iguales se salta a .inic

    bt      eax, edx        ;pone a la carry flag 0 o 1 del bit correspondiente a el contador
    inc     edx             ;incrementa el contador
    jc      .push1          ;salta a .push1 si la carry flag es 1
    jnc     .push0          ;si no salta a .push0

.push1:
    mov ebx, 1b             ;mueve un 1 a ebx y lo mete en el stack
    push ebx
    jmp .divisionLoop       ;salta a .divisionLoop

.push0:
    mov ebx, 0b             ;mueve un 0 a ebx y lo mete en el stack
    push ebx
    jmp .divisionLoop       ;salta a .divisionLoop

.inic:
    mov eax, 0b             ;mover eax un 0
    jmp .siguiente          ;salta a .siguiente

.siguiente:
    cmp edx, 0              ;compara  edx con 0
    je .terminamos          ;salta a .terminamos si es igual a 0
    pop ebx                 ;sacamos el top del stack
    add eax, ebx            ;sumamos eax con ebx
    shl eax, 1              ;le hacemos un shift a la izquierda a eax

    dec edx                 ;decrementamos el contador
    jmp .siguiente          ;saltamos a .siguiente

.terminamos:
    pop     esp             ; restore esp from the value we pushed onto the stack at the start
    pop     esi             ; restore esi from the value we pushed onto the stack at the start
    pop     edx             ; restore edx from the value we pushed onto the stack at the start
    pop     ecx             ; restore ecx from the value we pushed onto the stack at the start
    pop     ebx             ; restore ebx from the value we pushed onto the stack at the start

    ret
