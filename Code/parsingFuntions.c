#include <stdio.h>
#include "token_types.h"
#include "stdlib.h"
#include <string.h>
#define _OPEN_SYS_ITOA_EXT
FILE *archi;
FILE *code;
token current_token;

token next_T;

void syntax_error(token t){
  printf("syntax error %d\n",t);
}

extern token scanner();


extern char token_buffer[];


enum expr { IDEXPR, LITERALEXPR, TEMPEXPR };

typedef struct operator{
	/* for operators */
	enum op { PLUS, MINUS } operator;
} op_rec;

typedef struct expression{
	enum expr kind;
	union {
		string name;	/* for IDEXPR, TEMPEXPR */
		int val;		/* for LITERALEXPR */
    string sval;		/* for LITERALEXPR */
	};
} expr_rec;

string * extract_op(op_rec source){
  printf("extract_op\n");
  return (source.operator == PLUS ? "ADD":"SUB");
  printf("extract_op\n");
}

char* Itoa(int value, char* str, int radix) {
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;
    if (radix == 10 && value < 0) {
        value = -value;
        neg = 1;
    }
    v = value;
    do {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    if (neg)
        str[n++] = '-';
    str[n] = '\0';
    for (p = str, q = p + n/2; p != q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}

string * extract_expr(expr_rec source){
  printf("extract_expr\n");
  if(source.kind == LITERALEXPR){
    string s;
    sprintf(s,"%d",source.val);
    printf("%s\n", s);
    printf("%s\n", s);
    //printf("%c\n", result);
    printf("extract_expr1\n");
    return "mal";
  }
  printf("extract_expr2\n");
  return source.name;
}

//extern int lookup(string s);

//extern void enter(string s);

/*An auxiliary routine used by a number of the semantic routines is check_id*/
void check_id(string s){
  printf("check_id\n");
	if (! lookup(s)){

    enter(s);

		generate("Declare", s, "Integer", "");
	}
  printf("check_id\n");
}

void generate(string s1, string s2, string s3, string s4){
  printf("***********\n");
  fprintf(code,"%s %s %s %s\n", s1, s2, s3, s4);
	printf("%s %s %s %s\n", s1, s2, s3, s4);
  printf("***********\n");
}

char *get_temp(void){
  printf("get_temp\n");
	/* max temporary allocated so far */
	static int max_temp = 0;
	static char tempname[MAXIDLEN];
	max_temp++;
	sprintf(tempname, "Temp&%d", max_temp);
	check_id(tempname);
  printf("get_temp\n");
	return tempname;
}

void start(void){
	/* Semantic initializations, none needed */
}

void finish(void){
  printf("finish\n");
	/* Generate the code to finish program */
	generate("Halt", "", "", "");
  printf("finish\n");
}

void assign(expr_rec target, expr_rec source){
	/* Generate code for assignment */
  printf("assign\n");
  string s;
  if(source.kind == LITERALEXPR){
    string s;
    sprintf(s,"%d",source.val);
  }
  else{
      strcpy(s,source.name);
  }
	generate("Store", s, target.name, "");
  printf("assign\n");
}

op_rec process_op(void){
  printf("process_op\n");
	/* Produce operator descriptor */
	op_rec o;
	if (current_token == PLUSOP) o.operator = PLUS;
	else o.operator = MINUS;
  printf("process_op\n");
	return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2){
  printf("gen_infix\n");
	expr_rec e_rec;
	/* An expr_rec with temp variant set */
	e_rec.kind = TEMPEXPR;

	/* Generate code for infix operation
	 * Get result temp and set up semantic record
	 * for result */
	strcpy(e_rec.name, get_temp());
  //revisar si esto esta bien copiado
	generate(extract_op(op), extract_expr(e1), extract_expr(e2), e_rec.name);
  printf("gen_infix\n");
	return e_rec;
}

void read_id(expr_rec in_var){
  printf("read_id\n");
	/* Generate code for read */
	generate("Read", in_var.name, "Integer", "");
  printf("read_id\n");
}

expr_rec process_id(void){
  printf("process_id\n");
	expr_rec t;
	/* Declare ID and build a
	 * corresponding semantic record */
	check_id(token_buffer);
	t.kind = IDEXPR;
	strcpy(t.name, token_buffer);
  printf("process_id\n");
	return t;
}

expr_rec process_literal(void){
  printf("process_literal\n");
	expr_rec t;
	/* Convert literal to a numeric
	 * representation and build semantic record */
	t.kind = LITERALEXPR;
  strcpy(t.sval, token_buffer);
  (void) sscanf(token_buffer, "%d", & t.val);
  printf("process_literal\n");
	return t;
}

void write_expr(expr_rec out_expr){
  printf("write_expr\n");
	generate("Write", extract_expr(out_expr), "Integer", "");
  printf("write_expr\n");
}


void match(token t){
  printf("match\n");
  if (t == BEGIN){

    printf("break\n");
    next_T = scanner();

    printf("Comparo %d con %d\n",t,next_T);

    if(next_T == BEGIN){
      current_token = next_T;
      next_T = scanner();
    }else{
      syntax_error(next_T);
    }
  }else{
    printf("Comparo %d con %d\n",t,next_T);
    if(next_T == t){
      current_token = next_T;
      next_T = scanner();
    }else{
      syntax_error(next_T);
      /*poner o no next aqui
      preguntar al profe*/
    }
  }
  printf("match\n");
}

void add_op(op_rec *result){
  printf("add_op\n");
  token tok = next_T;
  /* <addop> ::= PLUSOP | MINUSOP */
  if (tok == PLUSOP || tok == MINUSOP){
    match(tok);
  }else{
    syntax_error(tok);
  }
  printf("add_op\n");
}

void expr_list(void){
  /*<expr_list> ::= <expression> { , <expression>} */
  printf("expr_list\n");
  expression();
  while (next_T == COMMA){
    match(COMMA);
    expression();
  }
  printf("expr_list\n");
}

void id_list(void){
  /*<id list> ::= ID { , ID}*/
  printf("id_list\n");
  match(ID);
  while (next_T == COMMA){
    match(COMMA);
    match(ID);
  }
  printf("id_list\n");

}

void primary(expr_rec *result){
  printf("primary\n");
  token tok = next_T;
  switch (tok) {
    case LPAREN:
          /*<primary> ::= {<expression>}*/
          match(LPAREN);
          expression();
          match(RPAREN);
          break;
    case ID:
          /*<primary> ::= ID*/
          match(ID);
          //process_id();
          break;
    case INTLITERAL:
          /*<primary> ::= INTLITERAL*/
          *result = process_literal();
          match(INTLITERAL);
          break;
    default:
          syntax_error(tok);
          break;
  }
  printf("primary\n");
}

void expression(expr_rec *result){
    printf("expression\n");
    expr_rec left_operand, right_operand;
    op_rec op;
    primary(& left_operand);
    while (next_T == PLUSOP || next_T == MINUSOP) {
      add_op(& op);
      primary(& right_operand);
      left_operand = gen_infix(left_operand, op, right_operand);
    }
    *result = left_operand;
    printf("expression\n");
}

void statement(void){
  printf("statement\n");
  token tok = next_T;
  expr_rec target;
  expr_rec source;
  switch (tok) {
    case ID:
          target = process_id();
          match(ID);
          match(ASSIGNOP);
          expression(&source);//creo
          assign(target, source);//creo
          match(SEMICOLON);
          break;
    case READ:
          /*<statement> ::= READ ( <id list> ) ; */
          match(READ);
          match(LPAREN);
          id_list();
          match(RPAREN);
          match(SEMICOLON);
          break;
    case WRITE:
          /*<statement> ::= WRITE (<expr list>) ; */
          match(WRITE);
          match(LPAREN);
          expr_list();
          match(RPAREN);
          match(SEMICOLON);
          break;
    default:
          syntax_error(tok);
          break;
  }
  printf("statement\n");
}

void statement_list(void){
  /*
  * <statement_list> ::= <statement>
  *                        {statement}
  */
  printf("statement_list\n");
  statement();
  while (1) {
    switch (next_T) {
      case ID:
      case READ:
      case WRITE:
            statement();
            break;
      default:
              printf("statement_list\n");
              return;
    }
  }
}

void program(void){
  /*<program> ::= BEGIN <statement list> END*/
  printf("program\n");
  match(BEGIN);
  statement_list();
  match(END);
  printf("program\n");
}

void system_goal(void){
  /* <system_goal> ::= <program> SCANEOF*/
  printf("system_goal\n");
  program();
  match(SCANEOF);
  printf("system_goal\n");
}

int main(){
  printf("main\n");
  archi = fopen("lectura","r");
  code = fopen("code","w");
  feof(archi);
  system_goal();
  fclose(archi);
  fclose(code);
  printf("main\n");
  return 0;
}
