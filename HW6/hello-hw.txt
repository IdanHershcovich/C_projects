#include "csapp.h"
#include "csapp.c"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUM_THREADS 8

//initializing the struct holding the parameters we want
struct th_info
{
    int taskid, sum;
    char *hello_msg;
};

char *messages[NUM_THREADS];
void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;
    //initialize struct to thread
    struct th_info *th_info = (struct th_info *)threadarg;

    //assigning the values from the struct to the variables
    taskid = th_info->taskid;
    sum = th_info->sum;
    hello_msg = th_info->hello_msg;
    printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
    Pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc, t, sum;
    sum = 0;
    messages[0] = "Hello-0";
    messages[1] = "Hello-1";
    messages[2] = "Hello-2";
    messages[3] = "Hello-3";
    messages[4] = "Hello-4";
    messages[5] = "Hello-5";
    messages[6] = "Hello-6";
    messages[7] = "Hello-7";
    for (t = 0; t < NUM_THREADS; t++)
    {
        struct th_info thr;
        sum = sum + t;
        thr.taskid = t;
        thr.sum = sum;
        thr.hello_msg = messages[t];

        /* ... */
        printf("Creating thread %d\n", t);
        Pthread_create(&threads[t], NULL, PrintHello, &thr);
        Pthread_join(threads[t], NULL);
        /* ... */
    }
    pthread_exit(NULL);
}