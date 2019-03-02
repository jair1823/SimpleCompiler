#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000
#define MAXBYTES 2048

char str[MAXCHAR];

void escribirEncabezado(FILE *resultado){
    fprintf(resultado, "%%include 'functions.asm'\n");
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

    fprintf(resultado, "section .text\n");
    fprintf(resultado, "\tglobal _start\n\n");
    fprintf(resultado, "_start:\n");

    fprintf(resultado, "\t;___________________________ Macros _________________________\n");
    fprintf(resultado, "\t%%macro suma 3\n");
    fprintf(resultado, "\t\tmov eax, %%1\n");
    fprintf(resultado, "\t\tmov ebx, %%2\n");
    fprintf(resultado, "\t\tadd eax, ebx\n");
    fprintf(resultado, "\t\tmov [%%3], eax\n");
    fprintf(resultado, "\t%%endmacro\n\n");

    fprintf(resultado, "\t%%macro resta 3\n");
    fprintf(resultado, "\t\tmov eax, %%1\n");
    fprintf(resultado, "\t\tmov ebx, %%2\n");
    fprintf(resultado, "\t\tsub eax, ebx\n");
    fprintf(resultado, "\t\tmov [%%3], eax\n");
    fprintf(resultado, "\t%%endmacro\n\n");

    fprintf(resultado, "\t%%macro imprimirMenos 0\n");
    fprintf(resultado, "\t\tmov eax, 4\n");
    fprintf(resultado, "\t\tmov ebx, 1\n");
    fprintf(resultado, "\t\tmov ecx, menos\n");
    fprintf(resultado, "\t\tmov edx, 1\n");
    fprintf(resultado, "\t\tint 80h\n");
    fprintf(resultado, "\t%%endmacro\n\n");

    fprintf(resultado, "\t%%macro leer 1\n");
    fprintf(resultado, "\t\tmov ebp, 0\n");    
    fprintf(resultado, "\t\tmov eax, 3\n");
    fprintf(resultado, "\t\tmov ebx, 0\n");
    fprintf(resultado, "\t\tmov ecx, %%1\n");
    fprintf(resultado, "\t\tmov edx, MAXBYTES\n");
    fprintf(resultado, "\t\tint 80h\n");
    fprintf(resultado, "\t\tcall guardarEntrada\n");
    fprintf(resultado, "\t\tmov [%%1], eax\n");
    fprintf(resultado, "\t%%endmacro\n\n");

    fprintf(resultado, "\t%%macro escribir 1\n");
    fprintf(resultado, "\t\tmov eax, %%1\n");
    fprintf(resultado, "\t\tcall verificarNegativo\n");
    fprintf(resultado, "\t\tcall iprintLF\n");
    fprintf(resultado, "\t%%endmacro\n\n");

    fprintf(resultado, "\t%%macro guardar 2\n");
    fprintf(resultado, "\t\tmov eax, %%1\n");
    fprintf(resultado, "\t\tmov [%%2], eax\n");
    fprintf(resultado, "\t%%endmacro\n\n");

    fprintf(resultado, "\t%%macro salir 0\n");
    fprintf(resultado, "\t\tmov eax, 1\n");
    fprintf(resultado, "\t\tmov ebx, 0\n");
    fprintf(resultado, "\t\tint 80h\n");
    fprintf(resultado, "\t%%endmacro\n\n");
    fprintf(resultado, "\t;___________________________ Código _________________________\n");
}

void escribirResta(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    char *p2 = strtok(NULL, ",");
    char *p3 = strtok(NULL, "\n");

    if (!isdigit(p1[0]) && !isdigit(p2[0])){
        fprintf(resultado, "\tresta [%s], [%s], %s", p1, p2, p3);
    } else if (!isdigit(p1[0]) && isdigit(p2[0])) {
        fprintf(resultado, "\tresta [%s], %s, %s", p1, p2, p3); 
    } else if (isdigit(p1[0]) && !isdigit(p2[0])) {
        fprintf(resultado, "\tresta %s, [%s], %s", p1, p2, p3);
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
        fprintf(resultado, "\tsuma [%s], [%s], %s", p1, p2, p3);
    } else if (!isdigit(p1[0]) && isdigit(p2[0])) {
        fprintf(resultado, "\tsuma [%s], %s, %s", p1, p2, p3);
    } else if (isdigit(p1[0]) && !isdigit(p2[0])) {
        fprintf(resultado, "\tsuma %s, [%s], %s", p1, p2, p3);
    } else {
        fprintf(resultado, "\tsuma %s, %s, %s", p1, p2, p3);
    }
    fprintf(resultado, "\n"); 
}

void escribirRead(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    //char *p1 = strtok(NULL, "\n");
    fprintf(resultado, "\tleer %s", p1);
    fprintf(resultado, "\n");
}

void escribirWrite(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    if (!isdigit(p1[0])){
        fprintf(resultado, "\tescribir [%s]", p1);
    } else {
        fprintf(resultado, "\tescribir %s", p1);
    }
    fprintf(resultado, "\n");
}

void escribirGuardar(FILE *resultado){
    char *p1 = strtok(NULL, ",");
    char *p2 = strtok(NULL, "\n");

    if (!isdigit(p1[0])){
        // Condicional para evaluar - (negativos)
        if (!(p1[0] == '-')){
            fprintf(resultado, "\tguardar [%s], %s", p1, p2);
        } else {
            fprintf(resultado, "\tguardar %s, %s", p1, p2);
        }
    } else {
        fprintf(resultado, "\tguardar %s, %s", p1, p2);
    }
    fprintf(resultado, "\n");
}

void escribirFunciones(FILE *resultado){
    fprintf(resultado, "\t;___________________________ Funciones _________________________\n");
    fprintf(resultado, "\tguardarEntrada:\n");
    fprintf(resultado, "\t\tmov ebp, 0\n");
    fprintf(resultado, "\t\tmov eax, ecx\n");
    fprintf(resultado, "\t\tcall atoi\n");
    fprintf(resultado, "\t\tcmp ebp, 0\n");
    fprintf(resultado, "\t\tje .guardar\n");
    fprintf(resultado, "\t\tneg eax\n");
    fprintf(resultado, "\t\t.guardar:\n");
    fprintf(resultado, "\t\t\tret\n\n");

    fprintf(resultado, "\tverificarNegativo:\n");
    fprintf(resultado, "\t\tcmp eax, 0\n");
    fprintf(resultado, "\t\tjge .return\n");
    fprintf(resultado, "\t\tpush eax\n");
    fprintf(resultado, "\t\timprimirMenos\n");
    fprintf(resultado, "\t\tpop eax\n");
    fprintf(resultado, "\t\tneg eax\n");
    fprintf(resultado, "\t\t.return:\n");
    fprintf(resultado, "\t\t\tret\n");
}

void escribirCuerpo(FILE *resultado, FILE *code){
    char *token;
    while (fgets(str, MAXCHAR, code) != NULL){
        token = strtok(str, " ");

        if (!strcmp(token, "Sub")){
            escribirResta(resultado);
        } else if (!strcmp(token, "Add")){
            escribirSuma(resultado);
        } else if (!strcmp(token, "Read")){
            escribirRead(resultado);
        } else if (!strcmp(token, "Write")){
            escribirWrite(resultado);
        } else if (!strcmp(token, "Store")){
            escribirGuardar(resultado);
        } else {
            fprintf(resultado, "\tsalir\n\n"); 
        }
    }
    escribirFunciones(resultado);
}

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

    fclose(declare);
    fclose(code);
    fclose(resultado);
    return 0;
}


