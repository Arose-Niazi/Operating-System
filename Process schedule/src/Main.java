import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main {

    private static File file;
    private static int algorithm;

    private static int cores;
    private static int processes;
    private static LinkedList<Process> processInfo;

    public static void main(String[] args)
    {
        if(args.length != 2)
        {
            System.err.println("Please enter filename and algorithm type as command line argument."
                    + "\n1 - First Come First Serve\n2 - Shortest Job First\n3 - Priority Based");
            return;
        }

        file = new File(args[0]);
        algorithm = Integer.parseInt(args[1]);

        if(!file.canRead())
        {
            System.err.println("Can not read the file.");
            return;
        }

        readFile();
        simulate();
    }

    private static void readFile()
    {
        try
        {
            Scanner input = new Scanner(file);
            cores = input.nextInt();
            processes = input.nextInt();
            System.out.println("Cores: " + cores + "\nProcesses: " + processes);
            processInfo = new LinkedList<>();
            for(int i=0; i<processes; i++)
            {
                Process process = new Process(input.nextInt(), input.nextInt(), input.nextInt(), input.nextInt());
                processInfo.add(process);
                System.out.println("Process ID: " + process.getId());
                System.out.println("\tArrival Time: " + process.getArrivalTime());
                System.out.println("\tBurst Time: " + process.getBurstTime());
                System.out.println("\tPriority: " + process.getPriority());
            }
        }
        catch (FileNotFoundException e)
        {
            System.err.println("File not found.");
        }
        catch (NoSuchElementException e)
        {
            System.err.println("File format incorrect, please recheck the file."
                    + "\nFormat should be: \n\tCores\n\tProcesses\n\tProcess ID\tArrival Time\tBurst Time\tPriority");
        }
    }

    private static void simulate()
    {
        CPUAlgo.setValues(processes, processInfo);
        LinkedList<CPUAlgo> myCores = new LinkedList<>();
        switch (algorithm)
        {
            case 1:
            {
                for(int i = 0; i<cores; i++)
                    myCores.add(new FCFS());
                break;
            }
            case 2:
            {
                for(int i = 0; i<cores; i++)
                    myCores.add(new SJF());
                break;
            }
            case 3:
            {
                for(int i = 0; i<cores; i++)
                    myCores.add(new Priority());
                break;
            }
            default:
            {
                System.err.println("Invalid algorithm option."
                            + "\n1 - First Come First Serve\n2 - Shortest Job First\n3 - Priority Based");
                return;
            }
        }
        myCores.get(0).sort(); //Sorting
        for(Process x : CPUAlgo.getProcessInfo())
        {
            System.out.println(x.getId());
        }
        while (CPUAlgo.getProcesses() > 0)
        {
            for(Process process: CPUAlgo.getProcessInfo()) {
                process.passTime();
            }
            System.out.println("----------- Time " + (CPUAlgo.getTime()) + "----------------");
            CPUAlgo.addTime();
            for (CPUAlgo core : myCores) {
                core.passTime();
                core.selectProcess();
            }
        }
        CPUAlgo.printInfo();
    }
}
