#include <string.h>
#include <stdio.h>
#include "stdlib.h"
#include <ctype.h>
int len_table = 0;
#include "token_types.h"
string table_symbol[] =  {"\0"};
extern FILE * code;
/* Is s in the symbol table? */
int lookup(string s){
  printf("lookup\n");

  for(int i = 0; i < len_table; i++){
    //fprintf(code, "ts %s %s",table_symbol[i],s);
    if( strcmp(table_symbol[i],s) == 0){
      printf("lookup\n");
      return 1;
    }
  }
  printf("lookup\n");
  return 0;
}
/* Put s unconditionally into symbol table */

void enter(string s){
    printf("enter\n");
    strcpy(table_symbol[len_table],s);
    printf("%s\n", s);
    printf("%s\n", s);
    printf("enter\n");
    len_table ++;
}
