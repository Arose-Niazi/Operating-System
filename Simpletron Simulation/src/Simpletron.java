/*
    Simpletron system developed by @Arose-Niazi
    Started on: 24/9/2020
 */

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
    public Simpletron()
    {
        memory = new int[100];
        accumulator= instructionCounter= instructionRegister= 0;
        boot();
        run();
    }

    private void boot()
    {
        System.out.println("*** Welcome to Simpletron! ***\n" +
                "*** Please enter your program one instruction ***\n" +
                "*** (or data word) at a time. I will display ***\n" +
                "*** the location number and a question mark ("+ IDENTIFIER +"). ***\n" +
                "*** You then type the word for that location. ***\n" +
                "*** Type "+ END +" to stop entering your program. ***");
    }

    private void run()
    {
        int input=0;
        Scanner scanner = new Scanner(System.in);
        for(int counter=0; counter<memory.length && input != END; counter++)
        {
            System.out.printf("%02d %c ",counter,IDENTIFIER);
            input = scanner.nextInt();
        }
        System.out.println("*** Program loading completed ***\n" +
                "*** Program execution begins ***");
    }

}
