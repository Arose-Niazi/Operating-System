/*
    Util -> The main working of simpletron.
    Started on: 02/10/2020
 */

/*
 * Includes
 */
#include <stdio.h>
#include "simple.h"

/*
    Variables
*/
int memory[SIZE];
int accumulator;
int instructionCounter;
int instructionRegister;
int operand;
int operation;


/*
 * Functions
 */

void boot() {
    printf("*** Welcome to Simpletron! ***\n"
           "*** Please enter your program instructions file ***\n"
           "*** The %s (%c) indicates that Simpletorn expects input ***", IDENTIFIER_NAME,IDENTIFIER);
}
 
FILE * loadFile(const char filename[])
{
	FILE *file;
    file = fopen(filename, "r");
    if(!file)
    {
		printf("\n*** INVALID FILE ****\n"
     			"*** Execution Terminated ***\n");
    }
	return file;
}



void loadInstructions(FILE *file)
{
    printf("\nLoading Integers\n");
    int counter = 0;
    while (fscanf(file, "%d", &memory[counter++]))
    	if(counter == SIZE) break;
}

void memoryDump() {
    printf("REGISTERS:\n");
    printf("%-20s %+05d\n","accumulator",accumulator);
    printf("%-22s  %02d\n","instructionCounter",instructionCounter);
    printf("%-20s %+05d\n","instructionRegister",instructionRegister);
    printf("%-22s  %02d\n","operand",operand);
    printf("%-22s  %02d\n\n","operation",operation);

    printf("MEMORY:\n");
    printf("   ");
    for(int i=0; i< ((SIZE+10) % SIZE); i++)
        printf("    %02d ",i);
    for(int i=0; i<SIZE; i++) {
        if(i % 10 == 0)
            printf("\n%02d ",i);

        printf(" %+05d ",memory[i]);
    }
    printf("\n\n*** Memory Dumped ***\n");

}

void compute() {
    if(instructionCounter >= SIZE) return;
    instructionRegister = memory[instructionCounter];
    if(instructionRegister == 0) return;
    operand = instructionRegister % SIZE;
    operation = instructionRegister / SIZE;

    switch (operation)
    {
        case READ:
            printf("Enter an integer.\n %c ", IDENTIFIER);
            int input;
            scanf("%d",&input);
            if(input > 9999 || input < -9999)
                return compute();
            memory[operand] = input;
            break;
        case WRITE:
            printf("Memory Location %02d: %+d \n",operand,memory[operand]);
            break;

        case LOAD:
            accumulator = memory[operand];
            break;
        case STORE:
            memory[operand] = accumulator;
            break;

        case ADD:
            accumulator += memory[operand];
            break;
        case SUB:
            accumulator -= memory[operand];
            break;
        case DIV:
            accumulator /= memory[operand];
            break;
        case MUL:
            accumulator *= memory[operand];
            break;

        case BRANCH:
            instructionCounter = operand-1;
            break;
        case BRANCHN:
            if(accumulator < 0) instructionCounter = operand-1;
            break;
        case BRANCHZ:
            if(accumulator == 0) instructionCounter = operand-1;
            break;
        case HALT:
            printf("*** Simpletron execution terminated ***\n");
            return;
        default:
            printf("*** INVALID INSTRUCTION ***");
            return;
    }
    instructionCounter++;
    memoryDump();
    compute();
}

void runSimpletron(const char filename[]) {
    boot();

    FILE *file = loadFile(filename);

    if(file == NULL) return;
    loadInstructions(file);

    printf("*** Program loading completed ***\n"
           "*** Program execution begins ***\n");

    compute();
}
