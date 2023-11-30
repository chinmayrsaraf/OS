import java.util.Scanner;

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
