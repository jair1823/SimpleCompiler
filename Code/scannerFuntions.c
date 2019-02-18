#include <stdio.h>
#include "stdlib.h"
#include "token_types.h"
#include <ctype.h>
extern FILE *archi;
extern void * memset();
extern size_t strlen();
extern int strcmp();
extern char token_buffer[] = {'\0'};


void clear_buffer(){
	//printf("clear_buffer Inicio\n");

	memset(token_buffer, 0,sizeof(token_buffer));
	//printf("clear_buffer Final\n");
}

void buffer_char(int tChar){
	//printf("buffer_char Inicio\n");

	size_t len = strlen(token_buffer);
  token_buffer[len] = tChar;
	token_buffer[len + 1] = '\0';
	//printf("buffer_char Inicio\n");

}

token check_reserved(){
	if(strcmp(token_buffer,"BEGIN") == 0 || strcmp(token_buffer,"begin") == 0)
		return BEGIN;
	else if(strcmp(token_buffer,"END") == 0 || strcmp(token_buffer,"end") == 0)
		return END;
	else if(strcmp(token_buffer,"READ") == 0 || strcmp(token_buffer,"read") == 0)
		return READ;
	else if(strcmp(token_buffer,"WRITE") == 0 || strcmp(token_buffer,"write") == 0)
		return WRITE;
	else
		return ID;
}

void lexical_error(char tChar){
	printf("Error in %c\n",tChar);
}

token scanner(void){
	int in_char, c;
	clear_buffer();




	if(feof(archi)){
		return SCANEOF;
	}

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
      ungetc(c, archi);
			//printf("letra\n");
			return check_reserved();
		}else if (isdigit(in_char)) {
			/*
				INTLITERAL ::= DIGIT |
						INTLITERAL DIGIT
			*/
			buffer_char(in_char);
			for (c = fgetc(archi); isdigit(c); c = fgetc(archi))
				buffer_char(c);
        //printf("is digit%c\n", c);
			ungetc(c, archi);
			//printf("numero\n");
			return INTLITERAL;
		} else if (in_char == '('){
			//printf("(\n");
			return LPAREN;
		}else if (in_char == ')'){
		//	printf(")\n");
			return RPAREN;
		}else if (in_char == ';'){
		//	printf(";\n");
			return SEMICOLON;
		}else if (in_char == ','){
		//	printf(",\n");
			return COMMA;
		}else if (in_char == '+'){
		//	printf("+\n");
			return PLUSOP;
		}else if (in_char == ':'){

			/* := */
			c = fgetc(archi);
			if ( c == '='){
				//printf(":=\n");
				return ASSIGNOP;
			}else {
				ungetc(c, archi);
				lexical_error(in_char);
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
				//printf("MINUSOP\n");
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
