// Author : Muhammad Arose Niazi FA18_BSE_010

/*
    Imports
*/
import java.io.File;
import java.util.Scanner;

/*
    Runner Class/ Main Class
*/
public class MatMult {

    public static void main(String[] args) {
        /*
            Variables to store input and output.
        */
        int[][] inputMatrix;
        int[][] result;

        try {
            Scanner input = new Scanner(new File(args[0]));
            int size = input.nextInt();
            inputMatrix = new int[size][size];

            for (int row = 0; row < size; row++)
                for (int column = 0; column < size; column++)
                    inputMatrix[row][column] = input.nextInt(); //reading the matrix

        } catch (Exception e) {
            System.err.println("ERROR in input!");
            System.err.println(e.getMessage());
            return;
        }

        try {
            Matrix[] matrixRows = new Matrix[inputMatrix.length]; //Storing the threads.

            for (int row = 0; row < matrixRows.length; row++)
                matrixRows[row] = new Matrix(inputMatrix[row], inputMatrix); //Making objects for those threads, and running it.

            for (Matrix matrixRow : matrixRows)
                matrixRow.join();//Waiting for threads to end.

            result = new int[inputMatrix.length][inputMatrix.length];

            for (int row = 0; row < matrixRows.length; row++)
                result[row] = matrixRows[row].answer; //Getting the answer.

        } catch (Exception e) {
            System.err.println("Error in threading");
            return;
        }
        /*
            Printing output
        */
        System.out.println("Input Matrix M is ");
        for (int row = 0; row < inputMatrix.length; row++) {
            for (int column = 0; column < inputMatrix[0].length; column++)
                System.out.print(inputMatrix[row][column] + " ");
            System.out.println();
        }
        System.out.println();
        System.out.println("The result of MxM is ");
        for (int row = 0; row < result.length; row++) {
            for (int column = 0; column < result[0].length; column++)
                System.out.print(result[row][column] + " ");
            System.out.println();
        }

    }
}

/*
    Worker Class
    The Multiplication is done here
*/

class Matrix extends Thread{

    /*
        Class Variables
    */
    private final int[] row;
    private final int[][] columns;

    int[] answer;

    public Matrix(int[] row, int[][] matrix) {
        this.row = row;
        this.columns = matrix;

        this.answer = new int[matrix[0].length];

        new Thread(this);//Creating Thread class object.
        start(); //starting the thread.
    }

    @Override
    public void run() {
       for(int rowE=0; rowE<answer.length; rowE++)
           for(int column=0; column<answer.length; column++)
               answer[rowE] += row[column] * columns[column][rowE];
    }
}
