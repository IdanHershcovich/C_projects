// #include "csapp.h"
// #include "csapp.c"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUMTHRDS 4
#define VECLEN 100000
pid_t pid;
void handler1(int sig)
 {
  printf("three ");
  fflush(stdout);
  kill(pid, SIGUSR1);
 }
void handler2(int sig)
 {
  printf("one ");
  exit(0);
}
int main()
 {
  signal(SIGUSR1, handler1);
  if ((pid = fork()) == 0)
   {
    signal(SIGUSR1, handler2);
    kill(getppid(), SIGUSR1);
    while(1) ;
} else
{
pid_t p;
int status;
if ((p = wait(&status)) > 0)
     printf("two ");
   }
}