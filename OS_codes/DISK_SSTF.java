
import java.util.ArrayList;
import java.util.Scanner;

public class DISK_SSTF {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of disk requests: ");
        int n = scanner.nextInt();

        ArrayList<Integer> requests = new ArrayList<>();
        System.out.println("Enter the disk requests:");
        for (int i = 0; i < n; i++) {
            requests.add(scanner.nextInt());
        }

        System.out.print("Enter the initial head position: ");
        int initialHead = scanner.nextInt();

        DISK_SSTF sstf = new DISK_SSTF();
        sstf.runSSTF(requests, initialHead);

        scanner.close();
    }

    public void runSSTF(ArrayList<Integer> requests, int initialHead) {
        ArrayList<Integer> processedOrder = new ArrayList<>();
        int totalSeekOperations = 0;
        int currentHead = initialHead;

        while (!requests.isEmpty()) {
            int closestRequest = findClosestRequest(requests, currentHead);
            processedOrder.add(closestRequest);
            totalSeekOperations += Math.abs(currentHead - closestRequest);
            currentHead = closestRequest;
            requests.remove(Integer.valueOf(closestRequest));
        }

        System.out.println("\nSSTF Sequence Order:");
        for (int request : processedOrder) {
            System.out.print(request + " ");
        }

        System.out.println("\nTotal seek operations (SSTF): " + totalSeekOperations);
    }

    private int findClosestRequest(ArrayList<Integer> requests, int currentHead) {
        int closestRequest = Integer.MAX_VALUE;
        int minDistance = Integer.MAX_VALUE;

        for (int request : requests) {
            int distance = Math.abs(currentHead - request);
            if (distance < minDistance) {
                minDistance = distance;
                closestRequest = request;
            }
        }

        return closestRequest;
    }
}
