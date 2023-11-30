import java.util.Scanner;

public class FCFS {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = sc.nextInt();

        int[] AT = new int[n];
        int[] BT = new int[n];
        int[] CT = new int[n];
        int[] TAT = new int[n];
        int[] WT = new int[n];

        // Input arrival time and burst time for each process
        for (int i = 0; i < n; i++) {
            System.out.print("Enter Arrival Time for Process P" + (i + 1) + ": ");
            AT[i] = sc.nextInt();
            System.out.print("Enter Burst Time for Process P" + (i + 1) + ": ");
            BT[i] = sc.nextInt();
        }

        // Calculate finish time, turnaround time, and waiting time
        int currentTime = 0;
        for (int i = 0; i < n; i++) {
            if (currentTime < AT[i]) {
                currentTime = AT[i];
            }
            CT[i] = currentTime + BT[i];
            TAT[i] = CT[i] - AT[i];
            WT[i] = TAT[i] - BT[i];
            currentTime = CT[i];
        }

        // Display results
        System.out.println("\nP_ID\t\tAT\t\tBT\t\tCT\t\tTAT\t\tWT");
        for (int i = 0; i < n; i++) {
            System.out.println("P" + (i + 1) + "\t\t" + AT[i] + "\t\t" + BT[i] + "\t\t" +
                    CT[i] + "\t\t" + TAT[i] + "\t\t" + WT[i]);
        }

        // Calculate and display average turnaround time and waiting time
        double avgTAT = 0, avgWT = 0;
        for (int i = 0; i < n; i++) {
            avgTAT += TAT[i];
            avgWT += WT[i];
        }

        // Draw Gantt Chart
        System.out.println("\nGantt Chart:");
        System.out.print("|");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < BT[i]; j++) {
                System.out.print(" P" + (i + 1) + " |");
            }
            if (i < n - 1) {
                System.out.print("|");
            }
        }
        System.out.println();

        avgTAT /= n;
        avgWT /= n;

        System.out.println("\nAverage Turnaround Time: " + avgTAT);
        System.out.println("Average Waiting Time: " + avgWT);
    }
}
