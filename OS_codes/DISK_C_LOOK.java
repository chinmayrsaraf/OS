
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class DISK_C_LOOK {

    // Function to perform C-LOOK disk scheduling
    private static int clook(List<Integer> requests, int head) {
        int n = requests.size();
        int totalSeekOperations = 0;

        // Sort the requests
        Collections.sort(requests);

        // Find the index of the first request greater than the head position
        int index = Collections.binarySearch(requests, head);
        if (index < 0) {
            index = -index - 1; // If not found, wrap around to the beginning
        }

        // Move in the increasing order until the end of the requests
        for (int i = index; i < n; ++i) {
            System.out.println("Servicing request: " + requests.get(i));
            totalSeekOperations += Math.abs(requests.get(i) - head);
            head = requests.get(i);
        }

        // Move to the beginning and continue until the head position
        for (int i = 0; i < index; ++i) {
            System.out.println("Servicing request: " + requests.get(i));
            totalSeekOperations += Math.abs(requests.get(i) - head);
            head = requests.get(i);
        }

        return totalSeekOperations;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input the number of requests and initial head position
        System.out.print("Enter the number of disk requests: ");
        int numRequests = scanner.nextInt();

        System.out.println("Enter the disk requests:");
        List<Integer> requests = new ArrayList<>();
        for (int i = 0; i < numRequests; ++i) {
            System.out.print("Request " + (i + 1) + ": ");
            requests.add(scanner.nextInt());
        }

        System.out.print("Enter the initial head position: ");
        int initialHead = scanner.nextInt();

        // Perform C-LOOK disk scheduling and calculate total seek operations
        System.out.println("C-LOOK Disk Scheduling Sequence:");
        int totalSeekOps = clook(requests, initialHead);

        System.out.println("Total seek operations: " + totalSeekOps);
    }
}
