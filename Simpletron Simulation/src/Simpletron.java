/*
    Simpletron system developed by @Arose-Niazi
    Started on: 24/9/2020
 */

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

    private static final int END = -9999;

    /*
        Variables
     */
    private int memory[];
    private int accumulator;
    private int instructionCounter;
    private int instructionRegister;

    
}
