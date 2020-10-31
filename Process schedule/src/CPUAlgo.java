import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;

public abstract class CPUAlgo {
    private static LinkedList<Process> processInfo;
    private static LinkedList<Process> allProcesses;
    private Process process;

    private static String algorithm;

    public Comparator comparator;

    public static void setValues(LinkedList<Process> pi)
    {
        setProcessInfo(pi);
        allProcesses = new LinkedList<>(pi);
    }

    void passTime()
    {
        if(getProcess() != null)
        {
            if(!getProcess().isLoaded())
            {
                getProcessInfo().remove(getProcess());
                setProcess(null);
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
                        break;
                    }
                }

            }
        }
    }

    public static void printInfo()
    {
        System.out.println(algorithm);
        System.out.println("Total Time waiting: " + getWaitingTime());
        System.out.println("Average turnaround time: " + getTurnAroundAvg());
    }

    public static LinkedList<Process> getProcessInfo() {
        return processInfo;
    }

    public static void setProcessInfo(LinkedList<Process> processInfo) {
        CPUAlgo.processInfo = processInfo;
    }

    private static int getWaitingTime()
    {
        int waitingTime=0;
        for (Process process: allProcesses) {
            waitingTime+=process.getWaitingTime();
        }
        return waitingTime;
    }

    private static int getTurnAroundTime()
    {
        int ptime=0;
        for (Process process: allProcesses) {
            ptime+=process.getTurnaroundTime();
        }
        return ptime;
    }

    private static float getTurnAroundAvg()
    {
        return (float) getTurnAroundTime() / (float) allProcesses.size();
    }

    public Process getProcess() {
        return process;
    }

    public void setProcess(Process process) {
        this.process = process;
    }

    public void setComparator(Comparator comparator) {
        this.comparator = comparator;
        Collections.sort(getProcessInfo(), comparator);
    }

    public static void setAlgorithm(String algorithm) {
        CPUAlgo.algorithm = algorithm;
    }
}
