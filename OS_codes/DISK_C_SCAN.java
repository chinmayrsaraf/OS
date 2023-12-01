/* import java.util.Arrays;
import java.util.Scanner;

public class DISK_C_SCAN {

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

    
        DISK_C_SCAN cScan = new DISK_C_SCAN();
        cScan.runCSCAN(requests, initialHead, direction);

        scanner.close();
    }    
}


class C_SCAN {
    public void runCSCAN(int[] requests, int initialHead, int direction) {
        int totalSeekOperations = 0;
        int currentHead = initialHead;

        System.out.println("\nC-SCAN Sequence Order:");

        // Sort the requests to make it easier to implement C-SCAN
        Arrays.sort(requests);

        if (direction == 0) { // Left direction
            for (int i = currentHead; i >= 0; i--) {
                if (Arrays.binarySearch(requests, i) >= 0) {
                    System.out.print(i + " ");
                    totalSeekOperations += Math.abs(currentHead - i);
                    currentHead = i;
                }
            }
            // Move to the leftmost end
            totalSeekOperations += currentHead;
            System.out.print("0 ");
            currentHead = 0;

            // Move to the rightmost end
            totalSeekOperations += (200 - 0);
            System.out.print("200 ");
            currentHead = 200;

            // Move back to the left
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
            // Move to the rightmost end
            totalSeekOperations += (200 - currentHead);
            System.out.print("200 ");
            currentHead = 200;

            // Move back to the leftmost end
            totalSeekOperations += (200 - 0);
            System.out.print("0 ");
            currentHead = 0;

            // Move back to the left
            for (int i = requests.length - 2; i >= 0; i--) {
                System.out.print(requests[i] + " ");
                totalSeekOperations += Math.abs(currentHead - requests[i]);
                currentHead = requests[i];
            }
        }

        System.out.println("\nTotal seek operations (C-SCAN): " + totalSeekOperations);
    }
}
 */
/* 
 import java.util.Arrays;
import java.util.Scanner;

public class DISK_C_SCAN {

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

        C_SCAN cScan = new C_SCAN(); // Corrected class name here
        cScan.runCSCAN(requests, initialHead, direction);

        scanner.close();
    }    
}

class C_SCAN {
    public void runCSCAN(int[] requests, int initialHead, int direction) {
        int totalSeekOperations = 0;
        int currentHead = initialHead;

        System.out.println("\nC-SCAN Sequence Order:");

        // Sort the requests to make it easier to implement C-SCAN
        Arrays.sort(requests);

        if (direction == 0) { // Left direction
            for (int i = currentHead; i >= 0; i--) {
                if (Arrays.binarySearch(requests, i) >= 0) {
                    System.out.print(i + " ");
                    totalSeekOperations += Math.abs(currentHead - i);
                    currentHead = i;
                }
            }
            // Move to the leftmost end
            totalSeekOperations += currentHead;
            System.out.print("0 ");
            currentHead = 0;

            // Move to the rightmost end
            totalSeekOperations += (200 - 0);
            System.out.print("200 ");
            currentHead = 200;

            // Move back to the left
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
            // Move to the rightmost end
            totalSeekOperations += (200 - currentHead);
            System.out.print("200 ");
            currentHead = 200;

            // Move back to the leftmost end
            totalSeekOperations += (200 - 0);
            System.out.print("0 ");
            currentHead = 0;

            // Move back to the left
            for (int i = requests.length - 2; i >= 0; i--) {
                System.out.print(requests[i] + " ");
                totalSeekOperations += Math.abs(currentHead - requests[i]);
                currentHead = requests[i];
            }
        }

        System.out.println("\nTotal seek operations (C-SCAN): " + totalSeekOperations);
    }
}
 */

// ----------------------------------------------------------------------------------------------
import java.util.Arrays;
import java.util.Scanner;

public class DISK_C_SCAN {
    static int max = 199, min = 0;

    static void sort(int[] arr, int n) {
        Arrays.sort(arr, 0, n);
    }

    static void cScan(int[] arr, int head, int n) {
        int index = 0;
        sort(arr, n);

        // Calculate head position
        for (int i = 0; i < n; i++) {
            if (arr[i] == head) {
                index = i;
                break;
            }
        }

        // C-Scan:-
        for (int i = index; i < n - 1; i++) {
            System.out.printf("\nHead moved from %d to %d", arr[i], arr[i + 1]);
        }
        System.out.printf("\nHead moved from %d to %d", arr[n - 1], max);
        System.out.printf("\nHead moved from %d to %d", max, min);
        System.out.printf("\nHead moved from %d to %d", min, arr[0]);
        for (int i = 0; i < index - 1; i++) {
            System.out.printf("\nHead moved from %d to %d", arr[i], arr[i + 1]);
        }

        int seek = Math.abs(max - head) + Math.abs(max - min) + Math.abs(min - arr[index - 1]);
        System.out.printf("\nC-Scan Seek time= %d", seek);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] arr = new int[25];
        int n = 0;
        System.out.print("Enter no. of requests: ");
        n = scanner.nextInt();

        System.out.println("\nEnter requests: ");
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }

        int head = 0;
        System.out.print("\nEnter head: ");
        head = scanner.nextInt();
        arr[n] = head;
        cScan(arr, head, n + 1);
    }
}

