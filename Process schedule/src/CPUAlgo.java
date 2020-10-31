import java.util.LinkedList;

public abstract class CPUAlgo {
    private static int processes;
    private static LinkedList<Process> processInfo;

    private static int time;
    private Process process;

    private static String algorithm = "";

    public static void setValues(int p, LinkedList<Process> pi)
    {
        setProcesses(p);
        setProcessInfo(pi);
        setTime(0);
    }

    public abstract void sort();

    public static void run(int c, int p, LinkedList<Process> pi)
    {


    }


    void passTime()
    {

        if(getProcess() != null)
        {
            if(!getProcess().isLoaded())
            {
                System.out.println("Process Complete: " + getProcess().getId());
                System.out.println("AT: " + getProcess().getArrivalTime() + "-> " + getProcess().getId());
                System.out.println("BT: " + getProcess().getBurstTime() + "-> " + getProcess().getId());
                System.out.println("WT: " + getProcess().getWaitingTime() + "-> " + getProcess().getId());
                System.out.println("PT: " + getProcess().getProcessTime() + "-> " + getProcess().getId());

                setProcess(null);
                setProcesses(getProcesses()-1);
            }
        }
    }

    public void selectProcess()
    {
        if(getProcess() == null)
        {
            for(Process process: getProcessInfo()) {
                if(!process.isCompleted() && !process.isLoaded())
                {
                    if(process.getArrivalTime() == 0)
                    {
                        process.setLoaded(true);
                        setProcess(process);
                        System.out.println("Loaded process: " + process.getId());
                        break;
                    }
                }

            }
        }
    }

    public static void printInfo()
    {
        System.out.println("\n-------> OUTPUT <---------");
        System.out.println("Algorithm: " + algorithm);
        System.out.println("Total Time Taken: " + getTotalTime());
        System.out.println("Total Time waiting: " + getWaitingTime());
        System.out.println("Average turnaround time: " + getTurnAroundAvg());
    }

    public static int getProcesses() {
        return processes;
    }

    public static void setProcesses(int processes) {
        CPUAlgo.processes = processes;
    }

    public static LinkedList<Process> getProcessInfo() {
        return processInfo;
    }

    public static void setProcessInfo(LinkedList<Process> processInfo) {
        CPUAlgo.processInfo = processInfo;
    }

    public static int getTime() {
        return time;
    }

    public static void setTime(int time) {
        CPUAlgo.time = time;
    }

    public static void addTime() {
        CPUAlgo.time++;
    }


    public Process getProcess() {
        return process;
    }

    public void setProcess(Process process) {
        this.process = process;
    }

    public static int getTotalTime()
    {
        return time-1; //Fixing my offset
    }

    public static int getWaitingTime()
    {
        int wtime=0;
        for (Process process: processInfo) {
            wtime+=process.getWaitingTime();
        }
        return wtime;
    }

    private static int getTurnAroundTime()
    {
        int ptime=0;
        for (Process process: processInfo) {
            ptime+=process.getTurnaroundTime();
        }
        return ptime;
    }

    public static float getTurnAroundAvg()
    {
        return (float) getTurnAroundTime() / (float) processInfo.size();
    }

    public static void setAlgorithm(String algorithm) {
        CPUAlgo.algorithm = algorithm;
    }
}
