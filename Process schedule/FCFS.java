import java.util.Comparator;

public class FCFS extends CPUAlgo {

    public FCFS() {
        setAlgorithm("First come first serve");
        setComparator(new CompareProcess());
        selectProcess();
    }

    static class CompareProcess implements Comparator<Process>
    {
        public int compare(Process p1, Process p2)
        {
            return Integer.compare(p1.getArrivalTime(), p2.getArrivalTime());
        }
    }
}
