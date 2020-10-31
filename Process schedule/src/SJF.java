import java.util.Collections;
import java.util.Comparator;

public class SJF extends CPUAlgo {

    public SJF() {
        setAlgorithm("Shortest job first");
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
            if (p1.getBurstTime() < p2.getBurstTime()) return -1;
            if (p1.getBurstTime() > p2.getBurstTime()) return 1;
            else
            {
                if (p1.getArrivalTime() < p2.getArrivalTime()) return -1;
                if (p1.getArrivalTime() > p2.getArrivalTime()) return 1;
                else return 0;
            }
        }
    }
}
