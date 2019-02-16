
typedef enum token_types {
    BEGIN, END, READ,WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, SCANEOF
} token;


void clear_buffer(){
	memset(token_buffer, 0, sizeof token_buffer);
}
void buffer_char(int tChar){
	int len = sizeof(token_buffer)/sizeof(int);
	token_buffer[len] = tChar;
	token_buffer[len + 1] = '\0';
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
