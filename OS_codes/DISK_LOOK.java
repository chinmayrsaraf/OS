
import java.util.Arrays;
import java.util.Scanner;

public class DISK_LOOK {

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

        System.out.print("Enter the direction (0 for left, 1 for right): ");
        int direction = scanner.nextInt();
     
        LOOK look = new LOOK();
        look.runLOOK(requests, initialHead, direction);

        scanner.close();
    }    
}

class LOOK {
    public void runLOOK(int[] requests, int initialHead, int direction) {
        int totalSeekOperations = 0;
        int currentHead = initialHead;

        System.out.println("\nLOOK Sequence Order:");

        // Sort the requests to make it easier to implement LOOK
        Arrays.sort(requests);

        if (direction == 0) { // Left direction
            for (int i = currentHead; i >= 0; i--) {
                if (Arrays.binarySearch(requests, i) >= 0) {
                    System.out.print(i + " ");
                    totalSeekOperations += Math.abs(currentHead - i);
                    currentHead = i;
                }
            }
            // Move back to the right
            for (int i = 1; i < requests.length; i++) {
                System.out.print(requests[i] + " ");
                totalSeekOperations += Math.abs(currentHead - requests[i]);
                currentHead = requests[i];
            }
        } else { // Right direction
            for (int i = currentHead; i <= 200; i++) {
                if (Arrays.binarySearch(requests, i) >= 0) {
                    System.out.print(i + " ");
                    totalSeekOperations += Math.abs(currentHead - i);
                    currentHead = i;
                }
            }
            // Move back to the left
            for (int i = requests.length - 2; i >= 0; i--) {
                System.out.print(requests[i] + " ");
                totalSeekOperations += Math.abs(currentHead - requests[i]);
                currentHead = requests[i];
            }
        }

        System.out.println("\nTotal seek operations (LOOK): " + totalSeekOperations);
    }
}
