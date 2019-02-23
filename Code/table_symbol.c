#include <string.h>
#include <stdio.h>
#include "stdlib.h"
#include <ctype.h>
int len_table = 0;
#include "token_types.h"
string table_symbol[];
/*
  string table_symbol[] =  {"\0"};
  esta forma de declarar la table_symbol
  provocaba que no me generara correctamente todos lo Declare

  hacer todos los Declare en un archivo temporal, para luego
  ponerlos todos en ensamblador

*/
extern FILE * code;
/* Is s in the symbol table? */
int lookup(string s){
  if(len_table == 0){
      return 0;
  }
  for(int i = 0; i < len_table; i++){
    if(!strcmp(table_symbol[i],s)){
      return 1;
    }
  }
  return 0;
}
/* Put s unconditionally into symbol table */

void enter(string s){
    strcpy(table_symbol[len_table],s);
    len_table ++;
}
