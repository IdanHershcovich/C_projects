#include <stdio.h>
//assigned value to y
int foo (x)
int x;
 {
  if(x < 10)
   {
    printf("x is less than 10\n");
   }
 }

int main()
 {
  int y = 5;
  foo(y);
 }
