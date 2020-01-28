#include <stdio.h> 
#include <stdlib.h> 


// changed int to unsigned int in l9
int main () 
 {
  char * buf;
  unsigned int num;
  num = 1 << 31;
  buf = malloc(num) ;
  fgets (buf, 1024, stdin) ;
  printf ("%s\n", buf) ;
  return(1);
 }