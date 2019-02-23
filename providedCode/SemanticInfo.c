/**************************************************************************/
// Semantic Information

#define MAXIDLEN 33
typedef char string[MAXIDLEN];
char token_buffer[];
typedef struct operator{
	/* for operators */
	enum op { PLUS, MINUS } operator;
} op_rec;

/* expression types */
enum expr { IDEXPR, LITERALEXPR, TEMPEXPR };

/* for <primary> and <expression> */
typedef struct expression{
	enum expr kind;
	union {
		string name;	/* for IDEXPR, TEMPEXPR */
		int val;		/* for LITERALEXPR */
	};
} expr_rec;

/*The specifications of our symbol table routines are:*/
/* Is s in the symbol table? */
extern int lookup(string s);

/* Put s unconditionally into symbol table */
extern void enter(string s);

/*An auxiliary routine used by a number of the semantic routines is check_id*/
void check_id(string s){
	if (! lookup(s)){
		enter(s);
		generate("Declare", s, "Integer", "");
	}
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
	generate("Store", extract(source), target.name, "");
}

op_rec process_op(void){
	/* Produce operator descriptor */
	op_rec o;
	if (current_token == PLUSOP) o.operator = PLUS;
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
	generate(extract(op), extract(el), extract(e2), e_rec.name);
	return e_rec;
}

void read_id(expr_rec in_var){
	/* Generate code for read */
	generate("Read", in_var.name, "Integer", "");
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
	generate("Write", extract(out_expr), "Integer", "");
}

/**************************************************************************/
