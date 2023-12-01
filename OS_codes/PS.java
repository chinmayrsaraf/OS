/* import java.util.Scanner;

public class PS {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of processes:");

        int n = sc.nextInt();

        int[] AT = new int[n];
        int[] BT = new int[n];
        int[] Priority = new int[n];
        int[] CT = new int[n];
        int[] TAT = new int[n];
        int[] WT = new int[n];
        int[] remainingTime = new int[n];

        for (int i = 0; i < n; i++) {
            System.out.println("Enter the Arrival time for process P" + (i + 1) + ":");
            AT[i] = sc.nextInt();
            System.out.println("Enter the Burst time for process P" + (i + 1) + ":");
            BT[i] = sc.nextInt();
            System.out.println("Enter the Priority for process P" + (i + 1) + ":");
            Priority[i] = sc.nextInt();
            remainingTime[i] = BT[i];
        }

        int currentTime = 0;
        int processesCompleted = 0;

        while (processesCompleted < n) {
            int highestPriority = Integer.MIN_VALUE;
            int selectedProcess = -1;

            for (int i = 0; i < n; i++) {
                if (AT[i] <= currentTime && remainingTime[i] > 0 && Priority[i] > highestPriority) {
                    highestPriority = Priority[i];
                    selectedProcess = i;
                }
            }

            if (selectedProcess == -1) {
                currentTime++;
            } else {
                if (remainingTime[selectedProcess] == 1) {
                    processesCompleted++;
                    CT[selectedProcess] = currentTime + 1;
                    TAT[selectedProcess] = CT[selectedProcess] - AT[selectedProcess];
                    WT[selectedProcess] = TAT[selectedProcess] - BT[selectedProcess];
                } else {
                    remainingTime[selectedProcess]--;
                }

                currentTime++;
            }
        }

        System.out.println("P_id" + "\t" + "AT" + "\t" + "BT" + "\t" + "PT" + "\t" + "CT" + "\t" + "TAT" + "\t" + "WT");

        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t" + AT[i] + "\t" + BT[i] + "\t" + Priority[i] + "\t" +
                    CT[i] + "\t" + TAT[i] + "\t" + WT[i]);
        }
    }
}
 */

import java.util.Scanner;

public class PS {
    public static void main(String[] args) {
        preemptivePriority();
    }

    static void preemptivePriority() {
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
        int[] priority = new int[n];
        int i, st = 0, tot = 0;

        for (i = 0; i < n; i++) {
            pid[i] = i + 1;
            System.out.printf("Enter arrival time for process %d: ", i + 1);
            at[i] = scanner.nextInt();
            System.out.printf("Enter burst time for process %d: ", i + 1);
            bt[i] = scanner.nextInt();
            k[i] = bt[i];
            f[i] = 0;
            System.out.printf("Enter priority for process %d: ", i + 1);
            priority[i] = scanner.nextInt();
        }

        while (true) {
            int min = 999, c = -1;
            if (tot == n)
                break;

            for (i = 0; i < n; i++) {
                if (at[i] <= st && f[i] == 0 && priority[i] < min) {
                    min = priority[i];
                    c = i;
                }
            }

            if (c == -1)
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

        System.out.println("\nPid|Arrival| Burst |Complete | Turn|Waiting");
        for (int j = 0; j < n; j++) {
            System.out.printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[j], at[j], k[j], ct[j], ta[j], wt[j]);
        }

        scanner.close();
   }
}
