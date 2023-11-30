/* import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class PRA_FIFO {

    public static int fifoPageFaults(String referenceString, int frameSize) {
        int pageFaults = 0;
        Queue<Character> frames = new LinkedList<>();

        for (char page : referenceString.toCharArray()) {
            if (!frames.contains(page)) {
                if (frames.size() < frameSize) {
                    frames.add(page);
                } else {
                    char removedPage = frames.poll();
                    frames.add(page);
                    System.out.println("Page " + removedPage + " removed. Page " + page + " added. Frames: " + frames);
                    pageFaults++;
                }
            } else {
                System.out.println("Page " + page + " is already in memory. Frames: " + frames);
            }
        }

        return pageFaults;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the reference string: ");
        String referenceString = scanner.nextLine();

        System.out.print("Enter the frame size: ");
        int frameSize = scanner.nextInt();

        int result = fifoPageFaults(referenceString, frameSize);
        System.out.println("Total number of page faults using FIFO: " + result);

        scanner.close();
    }
}
 */

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class PRA_FIFO {

    private static final int MAX_FRAMES = 3;
    private static final int MAX_REFERENCES = 10;

    private int[] referenceString = {0, 1, 2, 3, 2, 4, 3, 4, 5, 3};
    private int[] frames = new int[MAX_FRAMES];
    private Queue<Integer> frameQueue = new LinkedList<>();

    private int pageFaults = 0;

    private void initializeFrames() {
        Arrays.fill(frames, -1); // Initialize frames to -1 indicating empty
    }

    private boolean isPageInFrames(int page) {
        for (int frame : frames) {
            if (frame == page) {
                return true; // Page found in frames
            }
        }
        return false; // Page not found in frames
    }

    private void simulateFIFO() {
        initializeFrames();

        System.out.print("Reference String: ");
        for (int i = 0; i < MAX_REFERENCES; i++) {
            int page = referenceString[i];

            System.out.print(page + " ");

            if (!isPageInFrames(page)) {
                int oldestFrame = frameQueue.poll();
                frameQueue.add(page);
                frames[oldestFrame] = page;
                pageFaults++;

                System.out.print("(Page Fault) ");
            }

            System.out.print("Frames: ");
            for (int frame : frames) {
                if (frame == -1) {
                    System.out.print("  ");
                } else {
                    System.out.print(frame + " ");
                }
            }
            System.out.println();
        }

        System.out.println("Total Page Faults: " + pageFaults);
    }

    public static void main(String[] args) {
        System.out.println("FIFO Page Replacement Algorithm Simulation");

        PRA_FIFO fifoSimulation = new PRA_FIFO();
        fifoSimulation.simulateFIFO();
    }
}
