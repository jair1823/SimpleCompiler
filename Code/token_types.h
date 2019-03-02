typedef enum token_types {
    BEGIN, END, READ,WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, SCANEOF, PIPE
} token;
#define MAXIDLEN 33
typedef char string[MAXIDLEN];
