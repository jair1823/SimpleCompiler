#include <stdio.h>
/*macros*/
#include <ctype.h>

extern char token_buffer[];

typedef enum token_types {
    BEGIN, END, READ,WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, SCANEOF
} token;

token scanner(void){
	int in_char, c;
	clear_buffer();
	if(feof(stdin)){
		return SCANEOF;
	}
	while ((in_char = getchar()) != EOF){
		if (isspace(in_char))
			continue;
		else if (isalpha(in_char)){
			/*
				ID ::= LETTER | ID LETTER
					      | ID DIGIT
					      | ID UNDERSCORE
			*/
			buffer_char(in_char);/**/
			for (c = getchar(); isalnum(c) || c == '_'; c = getchar())
				buffer_char(c);
			ungetc(c, stdin);
			return check_reserved();
		}else if (isdigit(in_char)) {
			/*
				INTLITERAL ::= DIGIT |
						INTLITERAL DIGIT
			*/
			buffer_char(in_char);
			for (c = getchar; isdigit(c); c = getchar())
				buffer_char(c);
			ungetc(c, stdin);
			return INTLITERAL;
		} else if (in_char == '(')
			return LPAREN;
		else if (in_char == ')')
			return RPAREN;
		else if (in_char == ';')
			return SEMICOLON;
		else if (in_char == ',')
			return COMMA;
		else if (in_char == '+')
			return PLUSOP;
		else if (in_char == ':'){
			/* := */
			c = getchar();
			if ( c == '=')
				return ASSIGNOP;
			else {
				ungetc(c, stdin);
				lexical_error(in_char);
			}
		} else if (in_char == '-') {
			/*is it -- comment start*/
			c = getchar();
			if(c == '-'){
				do
					in_char	= getchar();
				while (in_char != '\n');
			} else {
				ungetc(c, stdin);
				return MINUSOP;
			}
		} else
			lexical_error(in_char);
	}
}
