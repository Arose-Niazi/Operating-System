import java.util.Comparator;

public class Process {
    private final int id;
    private int arrivalTime;
    private int burstTime;
    private final int priority;
    private int waitingTime;
    private int processTime;

    private boolean completed;
    private boolean loaded;

    public Process(int id, int arrivalTime, int burstTime, int priority) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.priority = priority;
        waitingTime = processTime = 0;
        loaded = false;
        completed = false;
    }

    public void passTime()
    {
        if(!completed)
        {
            if(loaded)
            {
                processTime++;
                if(--burstTime == 0)
                {
                    completed=true;
                    loaded=false;
                }
            }
            else
            {
                if(arrivalTime > 0)
                    arrivalTime--;
                else
                    waitingTime++;
            }

        }
    }

    public int getId() {
        return id;
    }

    public int getArrivalTime() {
        return arrivalTime;
    }

    public int getBurstTime() {
        return burstTime;
    }

    public int getPriority() {
        return priority;
    }

    public int getWaitingTime() {
        return waitingTime;
    }

    public boolean isLoaded() {
        return loaded;
    }

    public void setLoaded(boolean loaded) {
        this.loaded = loaded;
    }

    public boolean isCompleted() {
        return completed;
    }

    public int getTurnaroundTime() {
        return processTime + waitingTime;
    }

}