/* 12.17 A.
    It doesn't print because the exit() happens while the peer thread is asleep.This terminates the process and all of its threads

    12.17 B.
    Pthread_exit() or  Pthread_join().
 */


/*
 * hellobug.c - "hello, world" program with a bug
 */
#include "csapp.h"
#include "csapp.c"
#include <pthread.h>


void *thread(void *vargp);
int main()
{
   pthread_t tid;
   Pthread_create(&tid, NULL, thread, NULL);
   pthread_exit(NULL);
}
/* thread routine */
void *thread(void *vargp)
{
   Sleep(1);
   printf("Hello, world!\n");
   return NULL;
}
      