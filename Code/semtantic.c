// Semantic Information

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "token_types.h"
extern token current_token;


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

string * extract_op(op_rec source){
  printf("extract_op\n");
  return (source.operator == PLUS ? "ADD":"SUB");
  printf("extract_op\n");
}

string * extract_expr(expr_rec source){
  printf("extract_expr\n");
  if(source.kind == LITERALEXPR){
    string result = "ITOA";
    //hacer itoa
    printf("extract_expr\n");extern FILE *archi;
    return result;
  }
  printf("extract_expr\n");
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
  printf("generate\n");
	printf("%s %s %s %s\n", s1, s2, s3, s4);
  printf("generate\n");
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
	generate("Store", extract_expr(source), target.name, "");
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
	(void) sscanf(token_buffer, "%d", & t.val);
  printf("process_literal\n");
	return t;
}

void write_expr(expr_rec out_expr){
  printf("write_expr\n");
	generate("Write", extract_expr(out_expr), "Integer", "");
  printf("write_expr\n");
}
