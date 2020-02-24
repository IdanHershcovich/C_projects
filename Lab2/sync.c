#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
// #define SIZE 512

DIR *dir;
DIR *source;
DIR *dest;
struct dirent *ent, *src_ent, *dest_ent;

//gets the ammount of files in a given directory
char countFiles(char *directoryToSearch)
{
	int filesInDir = 0;
	if ((dir = opendir(directoryToSearch)) != NULL)
	{
		printf("\nFiles in directory \"%s\": \n", directoryToSearch);

		/* print all the files and directories within directory, except '.' and '..'*/
		while ((ent = readdir(dir)) != NULL)
		{
			//ignore . and .. 
			if (!(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0))
			{
				printf("%s\n", ent->d_name);
				filesInDir++;
			}
		}
		printf("\nThere are %d files in directory \"%s\" \n", filesInDir, directoryToSearch);
		closedir(dir);
		return filesInDir;
	}
	else
	{
		/* could not open directory */
		printf("can't open directory \"%s\" \n", directoryToSearch);
		exit(1);
	}
}


//Compares two files and returns the one with the latest modified time
char *modifiedTime(char *fp1, char *fp2)
{
	//Initializing vars that will hold the time of each file
	struct stat attrib1, attrib2;
	stat(fp1, &attrib1);
	stat(fp2, &attrib2);

	//associated with fp1
	char static time1[50];
	//associated with fp2
	char static time2[50];
	
	//Formatting the time
	strftime(time1, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib1.st_mtime));
	strftime(time2, 50, "%Y-%m-%d %H:%M:%S", localtime(&attrib2.st_mtime));

	//This calculates time1 - time2 and returns a double representing the difference in seconds. 
	//If it's positive, then time1 is later than time2; if negative, time2 is later;
	if(difftime(attrib1.st_mtime,attrib2.st_mtime) > 0)
	{
		printf("File at %s is the most recent one with a modified time of: %s. Replicating!\n", fp1, time1);
		return fp1;
	}
	else
	{
		printf("File at %s is the most recent one with a modified time of: %s. Replicating!\n", fp2, time2);
		return fp2;
	}
}

//Creates an existing file in a directory without the file. 
//If the file is present in both, it replaces the oldest file with the newest one
char replicate(char *src_dir, char *dst_dir, char *file)
{
	int src_fd, dst_fd, n, err;

	//buffer for the text in the file
	char buffer[4096];
	memset(buffer, 0, 4096);

	//buffers for the filepaths
	char src_filepath[1024];
	char dst_filepath[1024];

	//creating the full filepath of the directory plus the file to replace
	snprintf(src_filepath, sizeof(src_filepath) - 1, "%s/%s", src_dir, file);
	snprintf(dst_filepath, sizeof(dst_filepath) - 1, "%s/%s", dst_dir, file);

	//opening the file in each dir
	src_fd = open(src_filepath, O_RDONLY);
	dst_fd = open(dst_filepath, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);

		//read file into buffer
		err = read(src_fd, buffer, 4096);

		//src dir does not contain the file
		if (err == -1)
		{
			printf("file %s does not exist in directory \"%s\", removing from directory \"%s\".\n", file, src_dir, dst_dir);
			remove(dst_filepath);
			exit(-1);
		}
		n = err;

		//checking if the file exists in the destination directory
		if (dst_fd < 0)
		{
			/* failure */
			if (errno == EEXIST)
			{
				/* the file already existed. Deletes the old copy of the existing file and replaces it with the new one */
				printf("\nFile %s was found in both directories!\n", file);

				//returns the result of the time comparison
				char *latestFile = modifiedTime(src_filepath,dst_filepath);
				if (strcmp(latestFile, src_filepath) == 0) 
				{
					remove(dst_filepath);
					replicate(src_dir, dst_dir, file);
				}
				else if (strcmp(latestFile, dst_filepath) == 0) 
				{
					remove(src_filepath);
					replicate(dst_dir,src_dir, file);
				}
			}
		}
		//file does not exist in destination directory. Writes to the newly created file
		else
		{
			printf("Writing file %s to directory \"%s\" \n.", file, dst_dir);
			err = write(dst_fd, buffer, n);
			if (err == -1)
			{
				printf("Error writing to file.\n");
				exit(1);
			}
		}
	
	close(src_fd);
	close(dst_fd);
	return 0;
}

// source = a    destination = b.
// if file not in source, replicate it in b. If both dirs have the file, use the newest one
//if a file in destination is not in source, delete it
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: 3 arguments. (a) Source dir, (b) Destination dir, filename\n");
		return 0;
	}
	printf("Program initiated\n");
	countFiles(argv[1]);
	countFiles(argv[2]);
	replicate(argv[1], argv[2], argv[3]);

	return (0);
}
