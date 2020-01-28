#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int dec = atoi(argv[1]);
    int bin[32];
    int binzeroes[32] = {0};
    int i = 0;

    if (argc <= 1)
    {
        printf("You did not feed me arguments, I will self destruct now :( ... \n");
        exit(1);
    }

    for (i = 0; dec > 0; i++)
    {
        bin[i] = dec % 2;
        dec = dec / 2;
    }

    printf("\n 32bit Binary is=");
    
    //padding 
    for(int j = 31; j>=i; j--)
    {
        printf("%d", binzeroes[j]);
    }

    //binary
    for (i = i - 1; i >= 0; i--)
    {
        printf("%d", bin[i]);
    }
}
