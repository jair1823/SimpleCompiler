#include <stdio.h>
#include "token_types.h"
#include "stdlib.h"
FILE *archi;
token current_token;
token next_T;
char token_buffer[];

void syntax_error(token t){
  printf("syntax error %d\n",t);
}

extern token scanner();

void match(token t){
  //  printf("current_token %d next_T %d\n", current_token, next_T);
  if (t == BEGIN){
    next_T = scanner();
    printf("Comparo %d con %d\n",t,next_T);
    if(next_T == BEGIN){
      current_token = next_T;
    //  printf("current_token %d\n",current_token);
      next_T = scanner();
    }else{
      syntax_error(next_T);
    }
  }else{
    printf("Comparo %d con %d\n",t,next_T);

    if(next_T == t){
      current_token = next_T;
    //  printf("current_token %d\n",current_token);
      next_T = scanner();
    }else{

      syntax_error(next_T);
      /*poner o no next aqui
      preguntar al profe*/
    }
  }
}

void add_op(void){
  token tok = next_T;
  /* <addop> ::= PLUSOP | MINUSOP */
  if (tok == PLUSOP || tok == MINUSOP){
    match(tok);
  }else{
    syntax_error(tok);
  }
}

void primary(void){
  token tok = next_T;
  switch (tok) {
    case LPAREN:
          /*<primary> ::= {<expression>}*/
          match(LPAREN); expression();
          match(RPAREN);
          break;
    case ID:
          /*<primary> ::= ID*/
          match(ID);
          break;
    case INTLITERAL:
          /*<primary> ::= INTLITERAL*/
          match(INTLITERAL);
          break;
    default:
          syntax_error(tok);
          break;
  }
}

/*
token next_token(){
  return next_T;
}
*/

void expr_list(void){
  /*<expr_list> ::= <expression> { , <expression>} */
  expression();

  while (next_T == COMMA){
    match(COMMA);
    expression();
  }
}

void id_list(void){
  /*<id list> ::= ID { , ID}*/
  match(ID);

  while (next_T == COMMA){
    match(COMMA);
    match(ID);
  }

}

void expression(void){
  token t;
  /*
    <expression> ::= <primary>
                        { <add op> <primary>}
  */
  primary();
  for (t = next_T; t == PLUSOP || t == MINUSOP; t = next_T){
    add_op();
    primary();
  }
}

void statement(void){
  token tok = next_T;
  switch (tok) {
    case ID:
          /*<statement> ::= ID := <expression> ; */
          match(ID); match(ASSIGNOP);
          expression(); match(SEMICOLON);
          break;
    case READ:
          /*<statement> ::= READ ( <id list> ) ; */
          match(READ); match(LPAREN);
          id_list(); match(RPAREN);
          match(SEMICOLON);
          break;
    case WRITE:
          /*<statement> ::= WRITE (<expr list>) ; */
          match(WRITE); match(LPAREN);
          expr_list(); match(RPAREN);
          match(SEMICOLON);
          break;
    default:
          syntax_error(tok);
          break;
  }
}

void statement_list(void){
  /*
  * <statement_list> ::= <statement>
  *                        {statement}
  */
  statement();
  while (1) {
    switch (next_T) {
      case ID:
      case READ:
      case WRITE:
            statement();
            break;
      default:
              return;
    }
  }
}

void program(void){
  /*<program> ::= BEGIN <statement list> END*/
  match(BEGIN);
  statement_list();
  match(END);
}

void system_goal(void){
  /* <system_goal> ::= <program> SCANEOF*/
  program();
  match(SCANEOF);
}

int main(){
  archi = fopen("lectura","r");
  feof(archi);
  system_goal();
  fclose(archi);
  return 0;
}
