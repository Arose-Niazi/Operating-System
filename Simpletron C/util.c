/*
    Util to load file
    Started on: 02/10/2020
 */

/*
 * Includes
 */
#include <stdio.h>


/*
 * Functions
 */
 
FILE * loadFile(const char filename[])
{
	FILE *file;
    	file = fopen(filename, "r");
    	if(!file)
    	{
        	printf("\n*** INVALID FILE ****\n"
              		"*** Execution Terminated ***\n");
        	return NULL;
    	}
	return file;
}
	
