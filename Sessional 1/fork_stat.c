/* 	SID: FA18-BSE-006 & FA18-BSE-010
	Name:
		Rimsha Arif
		Arose Niazi
	Section:
		A
*/



/*
	Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

/*
	Prototypes
*/

void getMetaData(char *base, char *path, char *oFile);
void openDir(char *path, char *oFile);
void readDir(char *path, char *oFile);


/*
	Working
*/

int main(int counter, char *values[]) 
{
	if(counter != 2)
		return printf("Kindly enter absolute directory path.");
    
	printf("Process %d Parent %d going to explore %s\n", 
			getpid(),getppid(),values[1]); 
	readDir(values[1],values[0]);
    return 0;
}

void openDir(char *path, char *oFile)
{
	if(fork() <= 0)
		execl(oFile, oFile, path, NULL);
}

void readDir(char *path, char *oFile)
{
	struct dirent *dp;
    DIR *dir = opendir(path);
   
    if (!dir)
	{
		perror("Failed to open directory");
        return;
	}
  	while ((dp = readdir(dir)) != NULL)
    {
        if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
        	continue;
        getMetaData(path, dp->d_name, oFile);
    }
    closedir(dir);
}

void getMetaData(char *base, char *path, char *oFile) 
{
	char *dirPath = (char*) malloc((strlen(base) + strlen(path) + 2) * sizeof(char));
	sprintf(dirPath, "%s/%s",base,path);
	struct stat fstats;
	if(stat(dirPath, &fstats) == -1)
	{
		perror("Failed to get file status");
		return;
	}
	printf("%s size: %ld Inode#: %ld mode: %o modified: %s", 
			path, fstats.st_size, fstats.st_ino, (fstats.st_mode  & (S_IRWXU | S_IRWXG | S_IRWXO)), ctime(&fstats.st_mtime));
	if(S_ISDIR(fstats.st_mode))
		openDir(dirPath, oFile);	
}

