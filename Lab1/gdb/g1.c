#include <ctype.h> 
#include <stdio.h> 

// added brackets to the while loop
int main () 
 {
  char c;
  c = fgetc (stdin) ;
  while (c != EOF) 
  {
	  if (isalnum (c) ) 
			printf ("%c\n", c) ;
  	  c = fgetc (stdin) ;
  }

  return(1);
 }