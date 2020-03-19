/*
 * hello.c - Pthreads "hello, world" program
 */
#include "csapp.h"
#include "csapp.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *thread(void *vargp);
int main(int argc, char *argv[]) // main with argument
{
    //check for command line arg
    if(argc < 2) 
    {
        printf("Usage: %s N \n", argv[0]); // print usage
        return 0;
    }
    //convert to int
    int n = atoi(argv[1]);

    //thread id
    pthread_t tid;
    
    //create N threads
    for(int i = 0; i < n; i++)
    {
        Pthread_create(&tid, NULL, thread, NULL);
    }
    Pthread_exit(NULL);
    exit(0);
}
void *thread(void *vargp) /* thread routine */
{
   printf("Hello, world!\n");
   return NULL;
}