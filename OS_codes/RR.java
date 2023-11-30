/* 
import java.util.Scanner;
import java.util.Queue;
import java.util.LinkedList;

public class RR {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of processes:");
        int n = sc.nextInt();

        int[] AT = new int[n];
        int[] BT = new int[n];
        int[] CT = new int[n];
        int[] TAT = new int[n];
        int[] WT = new int[n];
        int[] remainingBT = new int[n];

        for (int i = 0; i < n; i++) {
            System.out.println("Enter the arrival time for process P" + (i + 1) + ":");
            AT[i] = sc.nextInt();
            System.out.println("Enter the burst time for process P" + (i + 1) + ":");
            BT[i] = sc.nextInt();
            remainingBT[i] = BT[i];
        }

        System.out.println("Enter the time quantum:");
        int quantum = sc.nextInt();

        Queue<Integer> queue = new LinkedList<>();
        int currentTime = 0;

        while (true) {
            boolean allProcessesDone = true;

            for (int i = 0; i < n; i++) {
                if (AT[i] <= currentTime && remainingBT[i] > 0) {
                    allProcessesDone = false;
                    if (remainingBT[i] > quantum) {
                        queue.add(i);
                        currentTime += quantum;
                        remainingBT[i] -= quantum;
                    } else {
                        queue.add(i);
                        currentTime += remainingBT[i];
                        remainingBT[i] = 0;
                        CT[i] = currentTime;
                        TAT[i] = CT[i] - AT[i];
                        WT[i] = TAT[i] - BT[i];
                    }
                }
            }

            if (allProcessesDone)
                break;

            int nextProcess = queue.poll();

            if (remainingBT[nextProcess] > 0) {
                if (AT[nextProcess] > currentTime) {
                    currentTime = AT[nextProcess];
                }
                queue.add(nextProcess);
            }
        }

        System.out.println("P_id\tAT\tBT\tCT\tTAT\tWT");

        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t" + AT[i] + "\t" + BT[i] + "\t" +
                    CT[i] + "\t" + TAT[i] + "\t" + WT[i]);
        }
    }
}

  */

/* 
  import java.util.Scanner;
import java.util.Queue;
import java.util.LinkedList;

public class RR {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of processes:");
        int n = sc.nextInt();

        int[] AT = new int[n];
        int[] BT = new int[n];
        int[] CT = new int[n];
        int[] TAT = new int[n];
        int[] WT = new int[n];
        int[] remainingBT = new int[n];

        for (int i = 0; i < n; i++) {
            System.out.println("Enter the arrival time for process P" + (i + 1) + ":");
            AT[i] = sc.nextInt();
            System.out.println("Enter the burst time for process P" + (i + 1) + ":");
            BT[i] = sc.nextInt();
            remainingBT[i] = BT[i];
        }

        System.out.println("Enter the time quantum:");
        int quantum = sc.nextInt();

        Queue<Integer> queue = new LinkedList<>();
        int currentTime = 0;

        System.out.println("\nGantt Chart:");
        System.out.print("|");

        while (true) {
            boolean allProcessesDone = true;

            for (int i = 0; i < n; i++) {
                if (AT[i] <= currentTime && remainingBT[i] > 0) {
                    allProcessesDone = false;
                    int executionTime = Math.min(quantum, remainingBT[i]);

                    for (int j = 0; j < executionTime; j++) {
                        System.out.print(" P" + (i + 1) + " |");
                    }

                    currentTime += executionTime;
                    remainingBT[i] -= executionTime;

                    if (remainingBT[i] == 0) {
                        CT[i] = currentTime;
                        TAT[i] = CT[i] - AT[i];
                        WT[i] = TAT[i] - BT[i];
                    }
                }
            }

            if (allProcessesDone)
                break;

            int nextProcess = -1;
            for (int i = 0; i < n; i++) {
                if (AT[i] <= currentTime && remainingBT[i] > 0) {
                    nextProcess = i;
                    break;
                }
            }

            if (nextProcess != -1) {
                if (AT[nextProcess] > currentTime) {
                    currentTime = AT[nextProcess];
                }
            }
        }

        System.out.println("|");

        System.out.println("\nP_id\tAT\tBT\tCT\tTAT\tWT");

        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t" + AT[i] + "\t" + BT[i] + "\t" +
                    CT[i] + "\t" + TAT[i] + "\t" + WT[i]);
        }

        // Calculate and display average turnaround time and waiting time
        double avgTurnaroundTime = 0, avgWaitingTime = 0;
        for (int i = 0; i < n; i++) {
            avgTurnaroundTime += TAT[i];
            avgWaitingTime += WT[i];
        }
        avgTurnaroundTime /= n;
        avgWaitingTime /= n;

        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);
    }
}
 */

 import java.util.Scanner;
import java.util.Queue;
import java.util.LinkedList;

public class RR {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of processes:");
        int n = sc.nextInt();

        int[] AT = new int[n];
        int[] BT = new int[n];
        int[] CT = new int[n];
        int[] TAT = new int[n];
        int[] WT = new int[n];
        int[] remainingBT = new int[n];

        for (int i = 0; i < n; i++) {
            System.out.println("Enter the arrival time for process P" + (i + 1) + ":");
            AT[i] = sc.nextInt();
            System.out.println("Enter the burst time for process P" + (i + 1) + ":");
            BT[i] = sc.nextInt();
            remainingBT[i] = BT[i];
        }

        System.out.println("Enter the time quantum:");
        int quantum = sc.nextInt();

        Queue<Integer> queue = new LinkedList<>();
        int currentTime = 0;

        System.out.println("\nGantt Chart:");
        System.out.print("|");

        while (true) {
            boolean allProcessesDone = true;

            for (int i = 0; i < n; i++) {
                if (AT[i] <= currentTime && remainingBT[i] > 0) {
                    allProcessesDone = false;
                    int executionTime = Math.min(quantum, remainingBT[i]);

                    for (int j = 0; j < executionTime; j++) {
                        System.out.print(" P" + (i + 1) + " |");
                        currentTime++;
                        remainingBT[i]--;

                        if (remainingBT[i] == 0) {
                            CT[i] = currentTime;
                            TAT[i] = CT[i] - AT[i];
                            WT[i] = TAT[i] - BT[i];
                        }
                    }
                }
            }

            if (allProcessesDone)
                break;
        }

        System.out.println("|");

        System.out.println("\nP_id\tAT\tBT\tCT\tTAT\tWT");

        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t" + AT[i] + "\t" + BT[i] + "\t" +
                    CT[i] + "\t" + TAT[i] + "\t" + WT[i]);
        }

        // Calculate and display average turnaround time and waiting time
        double avgTurnaroundTime = 0, avgWaitingTime = 0;
        for (int i = 0; i < n; i++) {
            avgTurnaroundTime += TAT[i];
            avgWaitingTime += WT[i];
        }
        avgTurnaroundTime /= n;
        avgWaitingTime /= n;

        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);
    }
}

