#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define BUFFER_SIZE 65525


//initializing variables and buffers
DIR *d;
struct dirent *dir;

FILE *fPtr;
FILE *fTemp;
char line[BUFFER_SIZE];

//used for find and replace
char buffer[BUFFER_SIZE];

//used for prepending
char bufferB[BUFFER_SIZE];

char *findReplacePrefix(char *find, char *replace, char *prefix)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0, numread = 0;

    //keeps track of replacements made in find and replace
    int replaceCounter = 0;
    int prependCounter = 0;

    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL) //Going through all files in current dir
        {
            int length = strlen(dir->d_name);
            if (strncmp(dir->d_name + length - 4, ".txt", 4) == 0) //if the file matches the extension .txt
            {
                //opening the file pointer and a temporary file to store the replaced text
                fPtr = fopen(dir->d_name, "r");
                fTemp = fopen("replace.tmp", "w");
                memset(buffer,0,BUFFER_SIZE);
                //goes through each line of the file
                while ((numread = (fgets(line, BUFFER_SIZE, fPtr))) != NULL)
                {
                    //I was having issues with the buffer leaking over to the next file so this
                    //is used to limit the loop per file
                    strcat(buffer,line);
                }
                //if there is an instance of of the find parameter
                if ((pos = strstr(buffer, find)) != NULL)
                {
                    int find_len = strlen(find);
                    //checks for every instance
                    while ((pos = strstr(buffer, find)) != NULL)
                    {
                        // Bakup current line
                        strcpy(temp, buffer);

                        // Index of current found word
                        index = pos - buffer;

                        // Terminate buffer after word found index
                        buffer[index] = '\0';

                        // Concatenate buffer with new word
                        strcat(buffer, replace);

                        // Concatenate buffer with remaining words after
                        // "find" found index.
                        strcat(buffer, temp + index + find_len);
                    }
                    replaceCounter++;
                }

                // No "find" param found. Look for prefix, prepend find
                else if ((pos = strstr(buffer, prefix)) != NULL)
                {
                    memset(bufferB, '\0', BUFFER_SIZE);
                    
                    //defining and initializing variables to hold lengths and buffers
                    char *tempB = bufferB;
                    int find_len = strlen(prefix);
                    int pfix_len = strlen(find);

                    //holds the whole line
                    char *pos_str = buffer;

                    //holds the prefix word
                    char *pos_word = strstr(buffer, prefix);

                    //goes through the lines. While the word is not null means it still has text ahead
                    while (pos_word != NULL)
                    {
                        char tk421[BUFFER_SIZE];
                        memcpy(tk421, pos_str, (pos_word - pos_str));

                        //every time bufferB is used, I have to add the space that was added into it
                        memcpy(tempB, pos_str, (pos_word - pos_str));
                        tempB += (pos_word - pos_str); 
                        strcat(bufferB, find);
                        tempB += pfix_len;
                        strcat(bufferB, prefix);
                        tempB += find_len;
                        pos_str = pos_word + find_len;
                        pos_word = strstr(pos_str, prefix);

                        //if it reaches the end
                        if (pos_word == NULL) {
                            strcat(bufferB, pos_str);
                            break;
                        }
                    }
                    strcpy(buffer,bufferB);
                    prependCounter ++;
                }
                // else {
                //     printf("Could not find any word to replace, or any word to prepend in file %s\n", dir->d_name);
                // }

                //puts everything onto the temp file
                fputs(buffer, fTemp);

                if (replaceCounter != 0)
                {
                    printf("\nSuccessfully replaced all occurrences of '%s' with '%s' in file '%s'. \n", find, replace, dir->d_name);
                    replaceCounter = 0;
                }
                else if (prependCounter != 0 && replaceCounter == 0)
                {
                    printf("\n No instances of '%s' within file: '%s'. Looking for %s \n", find, dir->d_name, prefix);
                    printf("\nSuccessfully prepended all occurrences of '%s' with '%s' in file '%s'.\n", prefix, find, dir->d_name);
                }
                else if (prependCounter == 0 && replaceCounter == 0)
                {
                    printf("\n No instances of '%s' or '%s' within file: '%s'. Nothing to do \n", find,prefix, dir->d_name);
                }

                /* Close all files to release resource */
                fclose(fPtr);
                fclose(fTemp);

                /* Delete original source file */
                remove(dir->d_name);

                /* Rename temp file as original file */
                rename("replace.tmp", dir->d_name);
            }
        }
    }
    closedir(d);
}
int main(int argc, char *argv[]) {
    if (argc < 1)
    {
        printf("No argument supplied\n");
        return 0;
    }
    printf("Program initiated\n");
    findReplacePrefix(argv[1], argv[2], argv[3]);

    return (0);
}
