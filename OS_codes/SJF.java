
// non preemtive SJF
import java.util.Scanner;
import java.util.Arrays;

public class SJF {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of processes:");

        int n = sc.nextInt();

        int[] AT = new int[n];
        int[] BT = new int[n];
        int[] CT = new int[n];
        int[] TAT = new int[n];
        int[] WT = new int[n];
        boolean[] completed = new boolean[n];

        for (int i = 0; i < n; i++) {
            System.out.println("Enter the arrival time for process P" + (i + 1) + ":");
            AT[i] = sc.nextInt();
            System.out.println("Enter the burst time for process P" + (i + 1) + ":");
            BT[i] = sc.nextInt();
        }

        int currentTime = 0;
        int completedProcesses = 0;

        while (completedProcesses < n) {
            int shortestJob = -1;
            int shortestTime = Integer.MAX_VALUE;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && AT[i] <= currentTime && BT[i] < shortestTime) {
                    shortestJob = i;
                    shortestTime = BT[i];
                }
            }

            
            if (shortestJob == -1) {
                currentTime++;
            } else {
                CT[shortestJob] = currentTime + BT[shortestJob];
                currentTime = CT[shortestJob];
                TAT[shortestJob] = CT[shortestJob] - AT[shortestJob];
                WT[shortestJob] = TAT[shortestJob] - BT[shortestJob];
                completed[shortestJob] = true;
                completedProcesses++;
            }
        }

        System.out.println("P_id\tAT\tBT\tCT\tTAT\tWT");

        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t" + AT[i] + "\t" + BT[i] + "\t" +
                    CT[i] + "\t" + TAT[i] + "\t" + WT[i]);
        }
    }
}
 