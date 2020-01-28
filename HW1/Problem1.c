#include <stdio.h>
#include <stdlib.h>

#define SIZE 128
int main(int argc, char *argv[])
{
    char line[SIZE][SIZE];
    char **lines;
    char *fname = argv[1];

    int i = 0;
    int total = 0;

    FILE *fp = fopen(fname, "r");
    if (argc <= 1)
    {
        printf("You did not feed me arguments, I will self destruct now :( ");
        exit(1);
    }
    while (fgets(line[i], SIZE, fp) != NULL)
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }

    total = i;
    printf("\n The content of the file, in reverse, are : \n");
    for (i = 0; i <= total; i++)
    {
        printf(" %s\n", line[total - i]);
    }

    fclose(fp);
    return 0;
}