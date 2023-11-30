import java.util.Scanner;

public class SJFPreemptive {
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
            completed[i] = false;
        }

        int currentTime = 0;
        int completedCount = 0;

        System.out.println("Gantt Chart:\n");

        while (completedCount < n) {
            int shortestJobIndex = -1;
            int shortestTime = Integer.MAX_VALUE;

            for (int i = 0; i < n; i++) {
                if (!completed[i] && AT[i] <= currentTime && BT[i] < shortestTime) {
                    shortestJobIndex = i;
                    shortestTime = BT[i];
                }
            }

            if (shortestJobIndex == -1) {
                currentTime++;
            } else {
                BT[shortestJobIndex]--;

                System.out.print("P" + (shortestJobIndex + 1) + " | ");
                currentTime++;

                if (BT[shortestJobIndex] == 0) {
                    completedCount++;
                    CT[shortestJobIndex] = currentTime;
                    completed[shortestJobIndex] = true;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            TAT[i] = CT[i] - AT[i];
            WT[i] = TAT[i] - BT[i];
        }

        System.out.println("\nProcess\tAT\tBT\tCT\tTAT\tWT");

        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t" + AT[i] + "\t" + BT[i] + "\t" +
                    CT[i] + "\t" + TAT[i] + "\t" + WT[i]);
        }
    }
}

