import java.util.Scanner;

public class DISK_FCFS {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of disk requests: ");
        int n = scanner.nextInt();

        int[] requests = new int[n];
        System.out.println("Enter the disk requests:");
        for (int i = 0; i < n; i++) {
            requests[i] = scanner.nextInt();
        }

        System.out.print("Enter the initial head position: ");
        int initialHead = scanner.nextInt();

        DISK_FCFS fcfs = new DISK_FCFS();
        fcfs.runFCFS(requests, initialHead);

        scanner.close();
    }

    public void runFCFS(int[] requests, int initialHead) {
        int totalSeekOperations = 0;
        int currentHead = initialHead;

        System.out.println("Sequence Order:");

        for (int i = 0; i < requests.length; i++) {
            int distance = Math.abs(currentHead - requests[i]);
            totalSeekOperations += distance;
            
            System.out.print(requests[i] + " ");
            
            currentHead = requests[i];
        }

        System.out.println("\nTotal seek operations: " + totalSeekOperations);
    }
}
