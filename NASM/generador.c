#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 1000

char str[MAXCHAR];

void escribirEncabezado(FILE *resultado){
    fprintf(resultado, "%%include 'functions.asm'\n\n");
    fprintf(resultado, "section .bss\n");
}

void escribirDeclares(FILE *resultado, FILE *declares){
    char *token;
    while (fgets(str, MAXCHAR, declares) != NULL){
        token = strtok(str, " ");
        token = strtok(NULL, ",");
        fprintf(resultado, "\t%s resb 2048\n", token);
    }
    fprintf(resultado, "\n");
}

void escribirIntermedio(FILE *resultado){
    fprintf(resultado, "section .text\n");
    fprintf(resultado, "\tglobal _start\n\n");
    fprintf(resultado, "_start:\n");
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
    char *p1 = strtok(NULL, "\n");
    fprintf(resultado, "\tleer %s", p1);
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
        fprintf(resultado, "\tguardar [%s], %s", p1, p2);
    } else {
        fprintf(resultado, "\tguardar %s, %s", p1, p2);
    }
    fprintf(resultado, "\n");
}


void escribirCuerpo(FILE *resultado, FILE *cuerpo){
    char *token;
    while (fgets(str, MAXCHAR, cuerpo) != NULL){
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
            fprintf(resultado, "\tsalir"); 
        }
    }
}

int main(){
    FILE *resultado;
    FILE *declares;
    FILE *cuerpo;

    resultado = fopen("resultado.asm", "w");
    if(resultado == NULL){
        fprintf(stderr, "Error al escribir el archivo resultado.");
        return 0;
    }

    declares = fopen("declares.txt", "r");
    if(declares == NULL){
        fprintf(stderr, "Error al abrir el archivo de declaraciones.");
        return 0;
    }

    cuerpo = fopen("cuerpo.txt", "r");
    if(cuerpo == NULL){
        fprintf(stderr, "Error al abrir el archivo con el cuerpo del código.");
        return 0;
    }

    escribirEncabezado(resultado);
    escribirDeclares(resultado, declares);
    escribirIntermedio(resultado);
    escribirCuerpo(resultado, cuerpo);

    fclose(declares);
    fclose(cuerpo);
    fclose(resultado);
    return 0;
}


