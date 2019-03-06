#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
#define MAXBYTES 2048

char str[MAXCHAR];

void escribirEncabezado(FILE *resultado){
	fprintf(resultado, ";_______________________________________________ Encabezado ________________________________________________\n");
    fprintf(resultado, "%%define MAXBYTES 2048\n\n");
    fprintf(resultado, "section .bss\n");
}

void escribirDeclare(FILE *resultado, FILE *declare){
    char *token;
    while (fgets(str, MAXCHAR, declare) != NULL){
        token = strtok(str, " ");
        token = strtok(NULL, ",");
        fprintf(resultado, "\t%s resb MAXBYTES\n", token);
    }
    fprintf(resultado, "\n");
}

void escribirIntermedio(FILE *resultado){
    fprintf(resultado, "section .data\n");
    fprintf(resultado, "\tmenos db 45\n\n");
    fprintf(resultado, "\tdosPuntos db 58\n\n");

    fprintf(resultado, "section .text\n");
    fprintf(resultado, "\tglobal _start\n\n");

    fprintf(resultado, ";_________________________________________________ Macros __________________________________________________\n");
    fprintf(resultado, "%%macro suma 3\n");
    fprintf(resultado, "\tmov eax, %%1\n");
    fprintf(resultado, "\tmov ebx, %%2\n");
    fprintf(resultado, "\tadd eax, ebx\n");
    fprintf(resultado, "\tmov [%%3], eax\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro resta 3\n");
    fprintf(resultado, "\tmov eax, %%1\n");
    fprintf(resultado, "\tmov ebx, %%2\n");
    fprintf(resultado, "\tsub eax, ebx\n");
    fprintf(resultado, "\tmov [%%3], eax\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro imprimirMenos 0\n");
    fprintf(resultado, "\tmov eax, 4\n");
    fprintf(resultado, "\tmov ebx, 1\n");
    fprintf(resultado, "\tmov ecx, menos\n");
    fprintf(resultado, "\tmov edx, 1\n");
    fprintf(resultado, "\tint 80h\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro imprimirDosPuntos 0\n");
    fprintf(resultado, "\tmov eax, 4\n");
    fprintf(resultado, "\tmov ebx, 1\n");
    fprintf(resultado, "\tmov ecx, dosPuntos\n");
    fprintf(resultado, "\tmov edx, 1\n");
    fprintf(resultado, "\tint 80h\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro leer 1\n");
    fprintf(resultado, "\timprimirDosPuntos\n");
    fprintf(resultado, "\tmov ebp, 0\n");
    fprintf(resultado, "\tmov eax, 3\n");
    fprintf(resultado, "\tmov ebx, 0\n");
    fprintf(resultado, "\tmov ecx, %%1\n");
    fprintf(resultado, "\tmov edx, MAXBYTES\n");
    fprintf(resultado, "\tint 80h\n");
    fprintf(resultado, "\tcall guardarEntrada\n");
    fprintf(resultado, "\tmov [%%1], eax\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro escribir 1\n");
    fprintf(resultado, "\tmov eax, %%1\n");
    fprintf(resultado, "\tcall verificarNegativo\n");
    fprintf(resultado, "\tcall iprintLF\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro guardar 2\n");
    fprintf(resultado, "\tmov eax, %%1\n");
    fprintf(resultado, "\tmov [%%2], eax\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro skip 1\n");
	fprintf(resultado, "\tmov ebp, %%1\n");
	fprintf(resultado, "\tcmp ebp, 0\n");
    fprintf(resultado, "%%endmacro\n\n");

    fprintf(resultado, "%%macro salir 0\n");
    fprintf(resultado, "\tmov eax, 1\n");
    fprintf(resultado, "\tmov ebx, 0\n");
    fprintf(resultado, "\tint 80h\n");
    fprintf(resultado, "%%endmacro\n\n");
}

void escribirResta(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    char *p2 = strtok(NULL, ",");
    char *p3 = strtok(NULL, "\n");

    if (!isdigit(p1[0]) && !isdigit(p2[0])){
		if 		(!(p1[0] == '-') && !(p1[0] == '-'))	fprintf(resultado, "\tresta [%s], [%s], %s", p1, p2, p3);
		else if (!(p1[0] == '-') && (p1[0] == '-'))		fprintf(resultado, "\tresta [%s], %s, %s", p1, p2, p3);
		else if ((p1[0] == '-') && !(p1[0] == '-'))		fprintf(resultado, "\tresta %s, [%s], %s", p1, p2, p3);
		else 											fprintf(resultado, "\tresta %s, %s, %s", p1, p2, p3);
    } else if (!isdigit(p1[0]) && isdigit(p2[0])) {
		if 		(!(p1[0] == '-'))						fprintf(resultado, "\tresta [%s], %s, %s", p1, p2, p3);
		else 											fprintf(resultado, "\tresta %s, %s, %s", p1, p2, p3);
    } else if (isdigit(p1[0]) && !isdigit(p2[0])) {
		if 		(!(p2[0] == '-'))						fprintf(resultado, "\tresta %s, [%s], %s", p1, p2, p3);
		else 											fprintf(resultado, "\tresta %s, %s, %s", p1, p2, p3);
    } else {
        												fprintf(resultado, "\tresta %s, %s, %s", p1, p2, p3);
    }
    fprintf(resultado, "\n");
}

void escribirSuma(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    char *p2 = strtok(NULL, ",");
    char *p3 = strtok(NULL, "\n");

    if (!isdigit(p1[0]) && !isdigit(p2[0])){
		if 		(!(p1[0] == '-') && !(p1[0] == '-'))	fprintf(resultado, "\tsuma [%s], [%s], %s", p1, p2, p3);
		else if (!(p1[0] == '-') && (p1[0] == '-'))		fprintf(resultado, "\tsuma [%s], %s, %s", p1, p2, p3);
		else if ((p1[0] == '-') && !(p1[0] == '-'))		fprintf(resultado, "\tsuma %s, [%s], %s", p1, p2, p3);
		else 											fprintf(resultado, "\tsuma %s, %s, %s", p1, p2, p3);
    } else if (!isdigit(p1[0]) && isdigit(p2[0])) {
		if 		(!(p1[0] == '-'))						fprintf(resultado, "\tsuma [%s], %s, %s", p1, p2, p3);
		else 											fprintf(resultado, "\tsuma %s, %s, %s", p1, p2, p3);
    } else if (isdigit(p1[0]) && !isdigit(p2[0])) {
		if 		(!(p2[0] == '-'))						fprintf(resultado, "\tsuma %s, [%s], %s", p1, p2, p3);
		else 											fprintf(resultado, "\tsuma %s, %s, %s", p1, p2, p3);
    } else {
        												fprintf(resultado, "\tsuma %s, %s, %s", p1, p2, p3);
    }
    fprintf(resultado, "\n");
}

void escribirRead(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    fprintf(resultado, "\tleer %s", p1);
    fprintf(resultado, "\n");
}

void escribirWrite(FILE *resultado){
    char *p1 = strtok(NULL, ",");

	if (!isdigit(p1[0])){
        if 		(!(p1[0] == '-'))	fprintf(resultado, "\tescribir [%s]", p1);
        else 						fprintf(resultado, "\tescribir %s", p1);
    } else {
        fprintf(resultado, "\tescribir %s", p1);
    }
    fprintf(resultado, "\n");
}

void escribirGuardar(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    char *p2 = strtok(NULL, "\n");

    if (!isdigit(p1[0])){
        if 		(!(p1[0] == '-'))	fprintf(resultado, "\tguardar [%s], %s", p1, p2);
        else 						fprintf(resultado, "\tguardar %s, %s", p1, p2);
    } else {
        fprintf(resultado, "\tguardar %s, %s", p1, p2);
    }
    fprintf(resultado, "\n");
}

void escribirJumpNotZero(FILE *resultado){
    char *p1 = strtok(NULL, "\n");
    fprintf(resultado, "\tjz %s\n", p1);
}

void escribirJump(FILE *resultado){
    char *p1 = strtok(NULL, "\n");
    fprintf(resultado, "\tjmp %s\n", p1);
}

void escribirSkip(FILE *resultado){
	char *p1 = strtok(NULL, "\n");
	if (!isdigit(p1[0])){
		if (!(p1[0] == '-')) fprintf(resultado, "\tskip [%s]", p1);
		else								 fprintf(resultado, "\tskip %s", p1);
	}else{
			fprintf(resultado, "\tskip %s", p1);
	}
	fprintf(resultado, "\n");
}

void escribirEtiqueta(FILE *resultado){
    char *p1 = strtok(NULL, "\n");
	fprintf(resultado, "\t%s\n", p1);
}

void escribirCuerpo(FILE *resultado, FILE *code){
    fprintf(resultado, ";_________________________________________________ Código __________________________________________________\n");
    fprintf(resultado, "_start:\n");

    char *token;
    while (fgets(str, MAXCHAR, code) != NULL){
        token = strtok(str, " ");

        if 			(!strcmp(token, "Sub"))				escribirResta(resultado);
        else if 	(!strcmp(token, "Add"))				escribirSuma(resultado);
        else if 	(!strcmp(token, "Read"))			escribirRead(resultado);
        else if 	(!strcmp(token, "Write"))			escribirWrite(resultado);
        else if 	(!strcmp(token, "Store"))			escribirGuardar(resultado);
 		else if 	(!strcmp(token, "JumpNotZero"))		escribirJumpNotZero(resultado);
        else if 	(!strcmp(token, "Jump"))			escribirJump(resultado);
        else if 	(!strcmp(token, "Skip"))			escribirSkip(resultado);
        else if 	(!strcmp(token, "Etiqueta"))		escribirEtiqueta(resultado);
        else 											fprintf(resultado, "\tsalir\n\n");
    }
}

void escribirFunciones(FILE *resultado){
    fprintf(resultado, ";________________________________________________ Funciones ________________________________________________\n");
    fprintf(resultado, "guardarEntrada:\n");
    fprintf(resultado, "\tmov ebp, 0\n");
    fprintf(resultado, "\tmov eax, ecx\n");
    fprintf(resultado, "\tcall atoi\n");
    fprintf(resultado, "\tcmp ebp, 0\n");
    fprintf(resultado, "\tje .guardar\n");
    fprintf(resultado, "\tneg eax\n");
    fprintf(resultado, "\t.guardar:\n");
    fprintf(resultado, "\t\tret\n\n");

    fprintf(resultado, "verificarNegativo:\n");
    fprintf(resultado, "\tcmp eax, 0\n");
    fprintf(resultado, "\tjge .return\n");
    fprintf(resultado, "\tpush eax\n");
    fprintf(resultado, "\timprimirMenos\n");
    fprintf(resultado, "\tpop eax\n");
    fprintf(resultado, "\tneg eax\n");
    fprintf(resultado, "\t.return:\n");
    fprintf(resultado, "\t\tret\n\n");

	fprintf(resultado, "; void iprint(Integer number)\n");
	fprintf(resultado, "; Función que imprime enteros (itoa)\n");
	fprintf(resultado, "iprint:\n");
	fprintf(resultado, "    push    eax             ; guardar el valor de eax en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    push    ecx             ; guardar el valor de ecx en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    push    edx             ; guardar el valor de edx en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    push    esi             ; guardar el valor de esi en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    mov     ecx, 0          ; contador que dice cuantos bytes hay que imprimir al final\n");
	fprintf(resultado, "divideLoop:\n");
	fprintf(resultado, "    inc     ecx             ; cuenta cada byte para imprimir - número de caracteres\n");
	fprintf(resultado, "    mov     edx, 0          ; se vacia edx\n");
	fprintf(resultado, "    mov     esi, 10         ; mov 10 a esi\n");
	fprintf(resultado, "    idiv    esi             ; se divide eax entre esi\n");
	fprintf(resultado, "    add     edx, 48         ; convierte edx a su representación en Ascii - edx mantiene un recordatorio después de realizar la división\n");
	fprintf(resultado, "    push    edx             ; push edx (representación en string del entero) en el stack\n");
	fprintf(resultado, "    cmp     eax, 0          ; se pregunta si se puede seguir dividiendo el entero\n");
	fprintf(resultado, "    jnz     divideLoop      ; si no es cero salta a la etiqueta de divideLoop\n");
	fprintf(resultado, "printLoop:\n");
	fprintf(resultado, "    dec     ecx             ; hace una cuenta regresiva de cada byte que se hac puesto en el stack\n");
	fprintf(resultado, "    mov     eax, esp        ; mov del puntero del stack al eax para imprimir\n");
	fprintf(resultado, "    call    sprint          ; se llama a la función que imprime strings\n");
	fprintf(resultado, "    pop     eax             ; se remueve el ultimo caracter del stack para mover el esp hacaia adelante\n");
	fprintf(resultado, "    cmp     ecx, 0          ; se verifica si ya se han impreso todos los bytes que estaban en el stack\n");
	fprintf(resultado, "    jnz     printLoop       ; si no es zero se salta a la etiqueta de printLoop\n");
	fprintf(resultado, "    pop     esi             ; se reestablece el valor de esi que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    pop     edx             ; se reestablece el valor de edx que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    pop     ecx             ; se reestablece el valor de ecx que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    pop     eax             ; se reestablece el valor de eax que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    ret\n\n");

	fprintf(resultado, "; void iprintLF(Integer number)\n");
	fprintf(resultado, "; Función que imprime enteros desde una línea de avance(itoa)\n");
	fprintf(resultado, "iprintLF:\n");
	fprintf(resultado, "    call    iprint          ; llama a la función que imprime enteros\n");
	fprintf(resultado, "    push    eax             ; guarda eax en el stack para guradar su valor mientras se usa el registro eax en la función\n");
	fprintf(resultado, "    mov     eax, 0Ah        ; mov 0Ah a eax - 0Ah es el caracter Ascii para una línea de avance\n");
	fprintf(resultado, "    push    eax             ; push de la linea de avance al stack para así obtener la dirección\n");
	fprintf(resultado, "    mov     eax, esp        ; se mueve la dirección del actual puntero del stack a eax para sprint\n");
	fprintf(resultado, "    call    sprint          ; se llama a la función sprint\n");
	fprintf(resultado, "    pop     eax             ; se remueve el caracter de la linea de avance del stack\n");
	fprintf(resultado, "    pop     eax             ; se reestablece el valor original que tenía eax antes de que se llamara a la función\n");
	fprintf(resultado, "    ret\n\n");

	fprintf(resultado, "; int slen(mensaje en string)\n");
	fprintf(resultado, "; Función que calcula el largo de un string\n");
	fprintf(resultado, "slen:\n");
	fprintf(resultado, "    push    ebx\n");
	fprintf(resultado, "    mov     ebx, eax\n");
	fprintf(resultado, "nextchar:\n");
	fprintf(resultado, "    cmp     byte [eax], 0\n");
	fprintf(resultado, "    jz      finished\n");
	fprintf(resultado, "    inc     eax\n");
	fprintf(resultado, "    jmp     nextchar\n");
	fprintf(resultado, "finished:\n");
	fprintf(resultado, "    sub     eax, ebx\n");
	fprintf(resultado, "    pop     ebx\n");
	fprintf(resultado, "    ret\n\n");

	fprintf(resultado, "; void sprint(String message)\n");
	fprintf(resultado, "; Función que imprime string\n");
	fprintf(resultado, "sprint:\n");
	fprintf(resultado, "    push    edx\n");
	fprintf(resultado, "    push    ecx\n");
	fprintf(resultado, "    push    ebx\n");
	fprintf(resultado, "    push    eax\n");
	fprintf(resultado, "    call    slen\n");
	fprintf(resultado, "    mov     edx, eax\n");
	fprintf(resultado, "    pop     eax\n");
	fprintf(resultado, "    mov     ecx, eax\n");
	fprintf(resultado, "    mov     ebx, 1\n");
	fprintf(resultado, "    mov     eax, 4\n");
	fprintf(resultado, "    int     80h\n");
	fprintf(resultado, "    pop     ebx\n");
	fprintf(resultado, "    pop     ecx\n");
	fprintf(resultado, "    pop     edx\n");
	fprintf(resultado, "    ret\n\n");

	fprintf(resultado, "; int atoi(Integer number)\n");
	fprintf(resultado, "; Función que convierte de Ascii a entero(atoi)\n");
	fprintf(resultado, "atoi:\n");
	fprintf(resultado, "    push    ebx             ; guardar el valor de ebx en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    push    ecx             ; guardar el valor de ecx en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    push    edx             ; guardar el valor de edx en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    push    esi             ; guardar el valor de esi en el stack para reincorporarlo después de que la función corra\n");
	fprintf(resultado, "    mov     esi, eax        ; mueve el puntero que esta en eax a esi(el número a convertir)\n");
	fprintf(resultado, "    mov     eax, 0          ; inicializa el registro eax con el valor decimal de cero\n");
	fprintf(resultado, "    mov     ecx, 0          ; inicializa el registro ecx con el valor decimal de cero\n");
	fprintf(resultado, ".multiplyLoop:\n");
	fprintf(resultado, "    xor     ebx, ebx        ; reinicia los bytes más bajos y altos de ebx para que sean cero\n");
	fprintf(resultado, "    mov     bl, [esi+ecx]   ; mueve un solo byte a la mitad de abajo del registro ebx\n");
	fprintf(resultado, "    cmp     bl, 45\n");
	fprintf(resultado, "    je      .flag\n");
	fprintf(resultado, "    cmp     bl, 48          ; compara la mitad de abajo del registro ebx con el valor ascii 48(char value 0)\n");
	fprintf(resultado, "    jl      .finished       ; salta si es menor a la etiqueta del final\n");
	fprintf(resultado, "    cmp     bl, 57          ; compara el valor de la parte baja del registro ebx con el valor ascii 57(char value 9)\n");
	fprintf(resultado, "    jg      .finished       ; salta si es mayor a la etiqueta del final\n");
	fprintf(resultado, "    cmp     bl, 10          ; compara el valor de la parte baja del registro ebx con el valor ascii 10 (caracter de la linea de avance)\n");
	fprintf(resultado, "    je      .finished       ; salta si es igual, a la etiqueta del final\n");
	fprintf(resultado, "    cmp     bl, 0           ; ccompara el valor de la parte baja del registro ebx  con el valor ascii 0 (final del string)\n");
	fprintf(resultado, "    jz      .finished       ; salta si es cero a la etiqueta del fnal\n");
	fprintf(resultado, "    sub     bl, 48          ; convierte la mitad menor del registro ebx a la representación deciaml del valor ascii\n");
	fprintf(resultado, "    add     eax, ebx        ; add ebx al valor entero en eax\n");
	fprintf(resultado, "    mov     ebx, 10         ; mueve el valor decimal 10 al ebx\n");
	fprintf(resultado, "    mul     ebx             ; multiplica eax por ebx para obtener un valor de campo\n");
	fprintf(resultado, "    inc     ecx             ; incrementar ecx (el registro de contador)\n");
	fprintf(resultado, "    jmp     .multiplyLoop   ; se continua en el ciclo de multiplicación\n");
	fprintf(resultado, ".flag:\n");
	fprintf(resultado, "    mov     ebp, 1\n");
	fprintf(resultado, "    inc     ecx             ; incrementar ecx (el registro de contador)\n");
	fprintf(resultado, "    jmp     .multiplyLoop   ; se continua en el ciclo de multiplicación\n");
	fprintf(resultado, ".finished:\n");
	fprintf(resultado, "    mov     ebx, 10         ; se mueve le valor decimal 10 a ebx\n");
	fprintf(resultado, "    div     ebx             ; se divide eax entre el valor en ebx (en este caso 10)\n");
	fprintf(resultado, "    pop     esi             ; se reestablece el valor de esi que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    pop     edx             ; se reestablece el valor de edx que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    pop     ecx             ; se reestablece el valor de ecx que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    pop     ebx             ; se reestablece el valor de ebx que se habia puesto en el stack al inicio\n");
	fprintf(resultado, "    ret");
}
/*
int main(){
    FILE *resultado;
    FILE *declare;
    FILE *code;

    resultado = fopen("resultado.asm", "w");
    if(resultado == NULL){
        fprintf(stderr, "Error al escribir el archivo resultado.");
        return 0;
    }

    declare = fopen("declare.tmp", "r");
    if(declare == NULL){
        fprintf(stderr, "Error al abrir el archivo de declaraciones.");
        return 0;
    }

    code = fopen("code.tmp", "r");
    if(code == NULL){
        fprintf(stderr, "Error al abrir el archivo con el cuerpo del código.");
        return 0;
    }

    escribirEncabezado(resultado);
    escribirDeclare(resultado, declare);
    escribirIntermedio(resultado);
    escribirCuerpo(resultado, code);
    escribirFunciones(resultado);

    fclose(declare);
    fclose(code);
    fclose(resultado);
    return 0;
}
*/
