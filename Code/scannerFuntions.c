#include <stdio.h>
#include "stdlib.h"
#include "token_types.h"
#include <ctype.h>
extern FILE *archi;
extern void * memset();
extern size_t strlen();
extern int strcmp();
extern int compilerError;
char token_buffer[64];
int lenTokenBuffer = 0;

//limpia el buffer para poder guardar el siguiente token
void clear_buffer(){
	lenTokenBuffer = 0;
	memset(token_buffer, 0, 64);
}

//agrega caracter por caracter del siguiente token al buffer
void buffer_char(int tChar){
	token_buffer[lenTokenBuffer] = tChar;
	token_buffer[lenTokenBuffer + 1] = '\0';
	lenTokenBuffer ++;

}

//se encarga de analizar si en el buffer se encuentra una palabra
//reservada
token check_reserved(){
	if(strcmp(token_buffer,"BEGIN") == 0 || strcmp(token_buffer,"begin") == 0){
		return BEGIN;
	}
	else{
		if(strcmp(token_buffer,"END") == 0 || strcmp(token_buffer,"end") == 0){
			return END;
		}
		else{
			if(strcmp(token_buffer,"READ") == 0 || strcmp(token_buffer,"read") == 0){
				return READ;
			}
			else{
				if(strcmp(token_buffer,"WRITE") == 0 || strcmp(token_buffer,"write") == 0){
					return WRITE;
				}
				else{
					return ID;
				}
			}
		}
	}
}

//muestra un lexical error justo en el char que sucedio
void lexical_error(char tChar){
	printf("lexical error near '%c'\n",tChar);
	exit(1);
	//se encarga de analizar el siguiente token
}


//Funcion principal del scanner, que toma el siguiente token del archivo
token scanner(void){
	int in_char, c;
	clear_buffer();
	while ((in_char = fgetc(archi)) != EOF){
		if (isspace(in_char))
			continue;
		else if (isalpha(in_char)){
			/*
				ID ::= LETTER | ID LETTER
					      | ID DIGIT
					      | ID UNDERSCORE
			*/
			buffer_char(in_char);/**/

			for (c = fgetc(archi); isalnum(c) || c == '_'; c = fgetc(archi)){
					 buffer_char(c);
      }
			if(lenTokenBuffer > 32){
				printf("Nombre de variable %s supera los 32 caracteres\n",token_buffer);
				exit(1);
			}
      ungetc(c, archi);
			return check_reserved();
		}else if (isdigit(in_char)) {
			/*
				INTLITERAL ::= DIGIT |
						INTLITERAL DIGIT
			*/
			buffer_char(in_char);
			for (c = fgetc(archi); isdigit(c); c = fgetc(archi))
				buffer_char(c);
			ungetc(c, archi);
			return INTLITERAL;
		} else if (in_char == '|'){
			return PIPE;
		} else if (in_char == '('){
			return LPAREN;
		}else if (in_char == ')'){
			return RPAREN;
		}else if (in_char == ';'){
			return SEMICOLON;
		}else if (in_char == ','){
			return COMMA;
		}else if (in_char == '+'){
			return PLUSOP;
		}else if (in_char == ':'){
			/* := */
			c = fgetc(archi);
			if ( c == '='){
				return ASSIGNOP;
			}else {
				ungetc(c, archi);
				lexical_error(':');
			}
		} else if (in_char == '-') {
			/*is it -- comment start*/
			c = fgetc(archi);
			if(c == '-'){
				do
					in_char	= fgetc(archi);
				while (in_char != '\n');
			} else {
				ungetc(c, archi);
				return MINUSOP;
			}
		} else
			lexical_error(in_char);
	}
	if(feof(archi)){
		return SCANEOF;
	}
}

void printToken(token t){
  switch (t) {
    case BEGIN:
          printf("BEGIN\n");
          break;
    case END:
          printf("END\n");
          break;
    case READ:
          printf("READ\n");
          break;
    case WRITE:
          printf("WRITE\n");
          break;
    case ID:
          printf("ID\n");
          break;
    case INTLITERAL:
          printf("INTLITERAL\n");
          break;
    case LPAREN:
          printf("LPAREN\n");
          break;
    case RPAREN:
          printf("RPAREN\n");
          break;
    case SEMICOLON:
          printf("SEMICOLON\n");
          break;
    case COMMA:
          printf("COMMA\n");
          break;
    case ASSIGNOP:
          printf("ASSIGNOP\n");
          break;
    case PLUSOP:
          printf("PLUSOP\n");
          break;
    case MINUSOP:
          printf("MINUSOP\n");
          break;
    case SCANEOF:
          printf("SCANEOF\n");
          break;
  }
}
