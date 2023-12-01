/* import java.util.Scanner;

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

 */

 import java.util.Scanner;

public class SJFPreemptive {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        int[] pid = new int[n];
        int[] at = new int[n];
        int[] bt = new int[n];
        int[] ct = new int[n];
        int[] ta = new int[n];
        int[] wt = new int[n];
        int[] f = new int[n];
        int[] k = new int[n];
        int i, st = 0, tot = 0;

        for (i = 0; i < n; i++) {
            pid[i] = i + 1;
            System.out.printf("Enter arrival time for process %d: ", i + 1);
            at[i] = scanner.nextInt();
            System.out.printf("Enter burst time for process %d: ", i + 1);
            bt[i] = scanner.nextInt();
            k[i] = bt[i];
            f[i] = 0;
        }

        while (true) {
            int min = 999, c = n;
            if (tot == n)
                break;

            for (i = 0; i < n; i++) {
                if (at[i] <= st && f[i] == 0 && bt[i] < min) {
                    min = bt[i];
                    c = i;
                }
            }

            if (c == n)
                st++;
            else {
                bt[c]--;
                st++;
                if (bt[c] == 0) {
                    ct[c] = st;
                    f[c] = 1;
                    tot++;
                }
            }
        }

        for (i = 0; i < n; i++) {
            ta[i] = ct[i] - at[i];
            wt[i] = ta[i] - k[i];
        }

        System.out.println("\nPidAT\\tBT\\tCT\\tTAT\\tWT");
        for (int j = 0; j < n; j++) {
            System.out.printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[j], at[j], k[j], ct[j], ta[j], wt[j]);
        }

        scanner.close();
}
}
