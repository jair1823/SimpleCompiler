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

    cmp	    bl, 45
    je 	    .flag
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
	stc
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