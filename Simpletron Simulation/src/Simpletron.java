/*
    Simpletron system developed by @Arose-Niazi
    Started on: 24/9/2020
 */

import javax.xml.soap.SOAPPart;
import java.sql.SQLOutput;
import java.util.Scanner;

public class Simpletron {
    /*
        Input output operations constants.
    */
    private static final int READ = 10;
    private static final int WRITE = 11;

    /*
        Load store operations constants.
    */
    private static final int LOAD = 20;
    private static final int STORE = 21;

    /*
        Calculation operations constants.
    */
    private static final int ADD = 30;
    private static final int SUB = 31;
    private static final int DIV = 32;
    private static final int MUL = 33;

    /*
        Control operations constants.
    */
    private static final int BRANCH = 40;
    private static final int BRANCHN = 41;
    private static final int BRANCHZ = 42;
    private static final int HALT = 43;

    /*
        Customizable Settings
     */
    private static final int END = -9999;
    private static final char IDENTIFIER = '?';
    private static final int SIZE = 46;

    /*
        Variables
     */
    private int memory[];
    private int accumulator;
    private int instructionCounter;
    private int instructionRegister;

    /*
        Working
     */
    public Simpletron() {
        memory = new int[SIZE];
        accumulator = instructionCounter = instructionRegister = 0;
        boot();
        run();
    }

    private void boot() {
        System.out.println("*** Welcome to Simpletron! ***\n" +
                "*** Please enter your program one instruction ***\n" +
                "*** (or data word) at a time. I will display ***\n" +
                "*** the location number and a question mark (" + IDENTIFIER + "). ***\n" +
                "*** You then type the word for that location. ***\n" +
                "*** Type " + END + " to stop entering your program. ***");
    }

    private void run() {
        getInstructions();

        System.out.println("*** Program loading completed ***\n" +
                "*** Program execution begins ***");

        compute();
        memoryDump();
    }

    private void getInstructions() {
        int input = 0;
        Scanner scanner = new Scanner(System.in);
        for (int counter = 0; counter < SIZE && input != END; counter++) {
            System.out.printf("%02d %c ", counter, IDENTIFIER);
            input = scanner.nextInt();
            if(input > 9999 || input < -9999) {
                counter--;
                continue;
            }
            if(input != END)
                memory[counter] = input;
        }
    }

    private void compute() {
        if(instructionCounter >= memory.length) return;
        instructionRegister = memory[instructionCounter];
        if(instructionRegister == 0) return;
        final int operand = instructionRegister % SIZE;

        switch (instructionRegister / SIZE)
        {
            case READ:
                System.out.println("Enter an integer.\n ? ");
                Scanner scanner = new Scanner(System.in);
                int input = scanner.nextInt();
                memory[operand] = input;
                break;
            case WRITE:
                System.out.printf("Memory Location %02d: %+d %n",operand,memory[operand]);
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
                System.out.println("*** Simpletron execution terminated ***");
                return;
        }
        instructionCounter++;
        compute();
    }

    private void memoryDump()
    {
        System.out.println("REGISTERS:");
        System.out.printf("%-20s %+05d%n","accumulator",accumulator);
        System.out.printf("%-22s  %02d%n","instructionCounter",instructionCounter);
        System.out.printf("%-20s %+05d%n%n","instructionRegister",instructionRegister);

        System.out.println("MEMORY:");
        System.out.print("   ");
        for(int i=0; i< ((SIZE+10) % SIZE); i++)
            System.out.printf("    %02d ",i);
        for(int i=0; i<memory.length; i++) {
            if(i % 10 == 0)
                System.out.printf("%n%02d ",i);

            System.out.printf(" %+05d ",memory[i]);
        }

    }

}
