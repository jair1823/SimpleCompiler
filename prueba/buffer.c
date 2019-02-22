#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <ctype.h>

extern char token_buffer[];

void clear_buffer(){
	//printf("clear_buffer Inicio\n");
	memset(token_buffer, 0, 255);
	//printf("clear_buffer Final\n");
}

void buffer_char(int tChar){
	//printf("buffer_char Inicio\n");

	size_t len = strlen(token_buffer);
  token_buffer[len] = tChar;
	token_buffer[len + 1] = '\0';
	//printf("buffer_char Inicio\n");

}
