import java.util.Comparator;

public class SJF extends CPUAlgo {

    public SJF() {
        setAlgorithm("Shortest job first");
        setComparator(new CompareProcess());
        selectProcess();
    }

    class CompareProcess implements Comparator<Process>
    {
        public int compare(Process p1, Process p2)
        {
            int value = Integer.compare(p1.getBurstTime(), p2.getBurstTime());
            if(value == 0)
                value = Integer.compare(p1.getArrivalTime(), p2.getArrivalTime());
            return value;
        }
    }
}
