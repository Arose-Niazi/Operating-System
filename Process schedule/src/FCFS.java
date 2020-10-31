import java.util.Collections;
import java.util.Comparator;

public class FCFS extends CPUAlgo {

    public FCFS() {
        setAlgorithm("First come first serve");
        selectProcess();
    }

    @Override
    public void sort() {
        CompareProcess compareProcess = new CompareProcess();
        Collections.sort(getProcessInfo(), compareProcess);
    }

    static class CompareProcess implements Comparator<Process>
    {
        public int compare(Process p1, Process p2)
        {
            if (p1.getArrivalTime() < p2.getArrivalTime()) return -1;
            if (p1.getArrivalTime() > p2.getArrivalTime()) return 1;
            else return 0;
        }
    }
}
