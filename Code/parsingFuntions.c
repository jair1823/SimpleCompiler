#include <stdio.h>
#include "token_types.h"
#include "stdlib.h"
#include <string.h>

extern token scanner();
extern int lookup(string s);
extern void enter(string s);
extern char token_buffer[];

FILE *archi;
FILE *code;
token current_token;
token next_T;

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
	};
} expr_rec;

void syntax_error(token t){
  printf("syntax error %d\n",t);
}

string * extract_op(op_rec source){
  return (source.operator == PLUS ? "ADD":"SUB");
}

/*An auxiliary routine used by a number of the semantic routines is check_id*/
void check_id(string s){
	if (! lookup(s)){
    enter(s);
		generate("Declare", s, ", Integer", "");
	}
}

void generate(string s1, string s2, string s3, string s4){
  fprintf(code,"%s %s%s%s\n", s1, s2, s3, s4);
	printf("%s %s %s %s\n", s1, s2, s3, s4);
}

char *get_temp(void){
	/* max temporary allocated so far */
	static int max_temp = 0;
	static char tempname[MAXIDLEN];
	max_temp++;
	sprintf(tempname, "Temp&%d", max_temp);
	check_id(tempname);
	return tempname;
}

void start(void){
	/* Semantic initializations, none needed */
}

void finish(void){
	/* Generate the code to finish program */
	generate("Halt", "", "", "");
}

void assign(expr_rec target, expr_rec source){
	/* Generate code for assignment */
  string s;
  if(source.kind == LITERALEXPR){
    sprintf(s,"%d",source.val);
    strcat(s,",");
  }
  else{
      strcpy(s,source.name);
      strcat(s,",");
  }
	generate("Store", s, target.name, "");
}

op_rec process_op(void){
	/* Produce operator descriptor */
	op_rec o;
	if (next_T == PLUSOP) o.operator = PLUS;
	else o.operator = MINUS;
	return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2){
	expr_rec e_rec;
	/* An expr_rec with temp variant set */
	e_rec.kind = TEMPEXPR;

	/* Generate code for infix operation
	 * Get result temp and set up semantic record
	 * for result */
	strcpy(e_rec.name, get_temp());
  //revisar si esto esta bien copiado
  string s1;
  if(e1.kind == LITERALEXPR){
    sprintf(s1,"%d",e1.val);
    strcat(s1,",");
  }
  else{
      strcpy(s1,e1.name);
      strcat(s1,",");
  }
  string s2;
  if(e2.kind == LITERALEXPR){
    sprintf(s2,"%d",e2.val);
    strcat(s2,",");
  }
  else{
      strcpy(s2,e2.name);
      strcat(s2,",");
  }

	generate(extract_op(op), s1, s2, e_rec.name);
	return e_rec;
}

void read_id(expr_rec in_var){
	/* Generate code for read */
	generate("Read", in_var.name, ", Integer", "");
}

expr_rec process_id(void){
	expr_rec t;
	/* Declare ID and build a
	 * corresponding semantic record */
	check_id(token_buffer);
	t.kind = IDEXPR;
	strcpy(t.name, token_buffer);
	return t;
}

expr_rec process_literal(void){
	expr_rec t;
	/* Convert literal to a numeric
	 * representation and build semantic record */
	t.kind = LITERALEXPR;
  (void) sscanf(token_buffer, "%d", & t.val);
	return t;
}

void write_expr(expr_rec out_expr){
  string s1;
  if(out_expr.kind == LITERALEXPR){
    sprintf(s1,"%d",out_expr.val);
    strcat(s1,",");
  }
  else{
      strcpy(s1,out_expr.name);
      strcat(s1,",");
  }
	generate("Write", s1, " Integer", "");
}

void match(token t){
  if (t == BEGIN){

    next_T = scanner();

    if(next_T == BEGIN){
      current_token = next_T;
      next_T = scanner();
    }else{
      syntax_error(next_T);
    }
  }else{

    if(next_T == t){
      current_token = next_T;
      next_T = scanner();
    }else{
      syntax_error(next_T);
      /*poner o no next aqui
      preguntar al profe*/
    }
  }
}

void add_op(op_rec *result){
  token tok = next_T;
  /* <addop> ::= PLUSOP | MINUSOP */
  if (tok == PLUSOP || tok == MINUSOP){
    *result = process_op();
    match(tok);
  }else{
    syntax_error(tok);
  }
}

void expr_list(void){
  /*<expr_list> ::= <expression> { , <expression>} */
  expr_rec source;
  expression(&source);
  write_expr(source);
  while (next_T == COMMA){
		match(COMMA);
    expr_rec source1;
    expression(&source1);
    write_expr(source1);
  }
}

void id_list(void){
  /*<id list> ::= ID { , ID}*/
	if(next_T == ID){
		expr_rec source = process_id();
		read_id(source);
		match(ID);
	}else{
		syntax_error(current_token);
		return;
	}
  while (next_T == COMMA){
    match(COMMA);
		if(next_T == ID){
			expr_rec source = process_id();
			read_id(source);
			match(ID);
		}else{
			syntax_error(current_token);
			return;
		}
  }
}

void primary(expr_rec *result){
  token tok = next_T;
  switch (tok) {
    case LPAREN:
          /*<primary> ::= {<expression>}*/
          match(LPAREN);
          expression(result);
          match(RPAREN);
          break;
    case ID:
          /*<primary> ::= ID*/
          *result = process_id();
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
}

void expression(expr_rec *result){
    expr_rec left_operand, right_operand;
    op_rec op;
    primary(& left_operand);

    while (next_T == PLUSOP || next_T == MINUSOP) {
      add_op(& op);
      primary(& right_operand);
      left_operand = gen_infix(left_operand, op, right_operand);
    }

    *result = left_operand;
}

void statement(void){
  token tok = next_T;
  expr_rec target;
  expr_rec source;
  switch (tok) {
    case ID:
          target = process_id();
          match(ID);
          match(ASSIGNOP);
          expression(&source);
          assign(target, source);
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
  finish();
  match(SCANEOF);
}

int main(){
  archi = fopen("lectura","r");
  code = fopen("code","w");
  feof(archi);
  system_goal();
  fclose(archi);
  fclose(code);
	return 0;
}
