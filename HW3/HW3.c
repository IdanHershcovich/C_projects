#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define BUFFER_SIZE 1000

DIR *d;
struct dirent *dir;

FILE *fPtr;
FILE *fTemp;
char buffer[BUFFER_SIZE];

char *findReplacePrefix(char *find, char *replace, char *prefix)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int find_len = strlen(find);
    // char find[100], replace[100];

    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL) //Going through all files in current dir
        {
            int length = strlen(dir->d_name);
            if (strncmp(dir->d_name + length - 4, ".txt", 4) == 0) //if the file matches the extension .txt
            {
                fPtr = fopen(dir->d_name, "r");
                fTemp = fopen("replace.tmp", "w");

                while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
                {
                    while ((pos = strstr(buffer, find)) != NULL)
                    {
                        // Bakup current line
                        strcpy(temp, buffer);

                        // Index of current found word
                        index = pos - buffer;

                        // Terminate str after word found index
                        buffer[index] = '\0';

                        // Concatenate str with new word
                        strcat(buffer, replace);

                        // Concatenate str with remaining words after
                        // oldword found index.
                        strcat(buffer, temp + index + find_len);
                    }
                    fputs(buffer, fTemp);
                }
                /* Close all files to release resource */
                fclose(fPtr);
                fclose(fTemp);

                /* Delete original source file */
                remove(dir->d_name);

                /* Rename temp file as original file */
                rename("replace.tmp", dir->d_name);

                printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", find, replace);
                // if (strstr(fileString, first) == NULL)
                // {
                // }
                // printf("%s\n", dir->d_name);
            }
        }
    }
    closedir(d);
}
int main(void)
{
    findReplacePrefix("fall", "waddup", "a");

    return (0);
}
