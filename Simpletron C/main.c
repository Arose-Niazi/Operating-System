/*
    Simpletron system developed by @Arose-Niazi
    Started on: 28/9/2020
 */

/*
 * Includes
 */
#include <stdio.h>

/*
    Input output operations constants.
*/
#define READ        10
#define WRITE       11

/*
    Load store operations constants.
*/
#define LOAD            20
#define STORE           21

/*
    Calculation operations constants.
*/
#define ADD             30
#define SUB             31
#define DIV             32
#define MUL             33

/*
    Control operations constants.
*/
#define BRANCH          40
#define BRANCHN         41
#define BRANCHZ         42
#define HALT            43

/*
    Customizable Settings
 */
#define END             -9999
#define IDENTIFIER_NAME "question mark"
#define IDENTIFIER      '?'
#define SIZE            100

/*
    Variables
*/
int memory[SIZE];
int accumulator;
int instructionCounter;
int instructionRegister;
int operand;
int operation;

void boot() {
    printf("*** Welcome to Simpletron! ***\n"
           "*** Please enter your program one instruction ***\n"
           "*** (or data word) at a time. I will display ***\n"
           "*** the location number and a %s (%c). ***\n"
           "*** You then type the word for that location. ***\n"
           "*** Type %d to stop entering your program. ***\n",
           IDENTIFIER_NAME, IDENTIFIER, END);
}

void getInstructions() {
    int input = 0;
    for (int counter = 0; counter < SIZE && input != END; counter++) {
        printf("%02d %c ", counter, IDENTIFIER);
        scanf("%d",&input);
        if(input > 9999 || input < -9999) {
            counter--;
            continue;
        }
        if(input != END)
            memory[counter] = input;
    }
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
            printf("Enter an integer.\n ? ");
            int input;
            scanf("%d",&input);
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
    compute();
}

void memoryDump() {
    printf("REGISTERS:\n");
    printf("%-20s %+05d\n","accumulator",accumulator);
    printf("%-22s  %02d\n","instructionCounter",instructionCounter);
    printf("%-20s %+05d\n\n","instructionRegister",instructionRegister);

    printf("MEMORY:\n");
    printf("   ");
    for(int i=0; i< ((SIZE+10) % SIZE); i++)
        printf("    %02d ",i);
    for(int i=0; i<SIZE; i++) {
        if(i % 10 == 0)
            printf("\n%02d ",i);

        printf(" %+05d ",memory[i]);
    }

}

void run() {
    boot();
    getInstructions();

    printf("*** Program loading completed ***\n"
           "*** Program execution begins ***\n");

    compute();
    memoryDump();
}



int main() {
    run();
    return 0;
}
