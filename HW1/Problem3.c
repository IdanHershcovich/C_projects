#include<stdio.h>
int main() {
    //using pointer arithmetic
    long lng[2];
    char *p1;
    char *p2;
    
    p1 = &lng[0];
    p2 = &lng[1]; // incrementing by one to find out the address of where the next long is stored.
    
    //substracting the 2 addresses return the amount of longs that can be stored in memory, which is 1.
    printf("bit size of long = %ld",p2-p1);
    return 0;
}