import java.util.Comparator;

public class Priority extends CPUAlgo {

    public Priority() {
        setAlgorithm("Priority");
        setComparator(new CompareProcess());
        selectProcess();
    }

    static class CompareProcess implements Comparator<Process>
    {
        public int compare(Process p1, Process p2)
        {
            int value = Integer.compare(p1.getPriority(), p2.getPriority());
            if(value == 0)
                value = Integer.compare(p1.getArrivalTime(), p2.getArrivalTime());
            return value;
        }
    }
}
