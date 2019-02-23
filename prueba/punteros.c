#include <stdio.h>
#include <string.h>

typedef char string[33];

typedef struct operator{
  string name;
  enum op{ PLUS, MINUS } operator;
} op_rec;

void expression(op_rec *result){
  op_rec op1;
  strcpy(op1.name, "Hello world");
  op1.operator = PLUS;
  *result = op1;
}

void buffer(char * result){
    char token_buffer[] = {'\0'};
    *result = token_buffer;
}


int main() {
  /* code */
  /*op_rec  opMain;
  printf("cambio nombre a opMain\n");
  strcpy(opMain.name, "opMain");
  printf("%s\n", opMain.name);
  printf("entre a expression\n");
  expression(&opMain);
  printf("sali de expression\n");
  printf("%s\n", opMain.name);*/
  return 0;
}
