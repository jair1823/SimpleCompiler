#include <stdio.h>
#include "stdlib.h"
#include <ctype.h>
char token_buffer[] = {'\0'};
extern void buffer_char();
extern void clear_buffer();
int main(int argc, char const *argv[]) {
  /* code */
  for(int i = 0;i<900;i++){
    buffer_char(92);
  }
  buffer_char(92);
  buffer_char(92);
  buffer_char(92);
  buffer_char(92);
  buffer_char(92);
  printf("%s\n", token_buffer);
  clear_buffer();
  buffer_char(65);
  buffer_char(65);
  buffer_char(65);
  buffer_char(65);
  buffer_char(65);
  printf("%s\n", token_buffer);
  return 0;
}
