import java.util.ArrayList;
import java.util.Scanner;

public class BankersAlgo{
  
    public static void main(String[] args) {
        BankersAlgo bank = new BankersAlgo();
        Scanner scan = new Scanner(System.in);

        ArrayList<Integer> seq = new ArrayList<Integer>();

        int numProcesses = 0;
        int numResources = 0;

                
        System.out.print("Enter the number of processes: ");
        numProcesses = scan.nextInt();

        System.out.print("Enter the number of resources: ");
        numResources = scan.nextInt();

        int[] total = new int[numResources];
        for(int i = 0; i < numResources; i++){
            System.out.print("Enter the total number of instances for resource " + i + ":");
            total[i] = scan.nextInt();
        }
        System.out.println();

        int [] tempTotalOfAllocatedResources = new int[numResources]; 
        ArrayList<int[]> allocated = new ArrayList<int[]>(numProcesses);
        for(int i = 0; i < numProcesses; i++){
            int[] temp = new int[numResources];
            System.out.println("The Process " + i + " is allocated the following resources: ");
            for(int j = 0; j < numResources; j++){
                System.out.print("The allocated instance of resource " + j + " : ");
            
                temp[j] = scan.nextInt();
                tempTotalOfAllocatedResources[j] += temp[j];
            }
            allocated.add(temp);
        }

        ArrayList<int[]> max = new ArrayList<int[]>(numProcesses);
        for(int i = 0; i < numProcesses; i++){
            int[] temp = new int[numResources];
            System.out.println("The Process " + i + " is Needed the following resources At Max: ");
            for(int j = 0; j < numResources; j++){
                System.out.print("The maximum instance of resource Need " + j + " : ");
                temp[j] = scan.nextInt();
            }
            max.add(temp);
        }

        System.out.println("The Available Resources are: ");
        int[] available = new int[numResources];
        for(int i = 0; i < numResources; i++){
            available[i] = total[i] - tempTotalOfAllocatedResources[i];
            System.out.println("\t Resource " + i + " : " + available[i]);
        }

        ArrayList<int[]> Remainingneed = new ArrayList<int[]>(numProcesses);
        for(int i=0; i<numProcesses; i++) {
            int[] temp = new int[numResources];
            for(int j=0; j<numResources; j++) {
                temp[j] = max.get(i)[j] - allocated.get(i)[j];
            }
            Remainingneed.add(temp);
        }
   
        seq = bank.run(allocated, max, Remainingneed, available, numProcesses, numResources);  

        System.out.println("The Safe Sequence is: ");
        for(int i = 0; i < seq.size(); i++){
            System.out.print("P" + seq.get(i));
            if(i != seq.size() - 1){
                System.out.print(" -> ");
            }
        }
    }

    private ArrayList<Integer> run(ArrayList<int[]> allocated, ArrayList<int[]> max, ArrayList<int[]> remainingneed, int[] available, int numProcesses, int numResources) {
        ArrayList<Integer> seq = new ArrayList<Integer>();
        
        ArrayList<Boolean> safe = new ArrayList<Boolean>(numProcesses);

        for(int i = 0; i < numProcesses; i++){
            safe.add(false);
        }

        int[] work = new int[numResources];

        for(int i = 0; i < numResources; i++){
            work[i] = available[i];
        }

        for(int k =0; k<numProcesses; k++) {
            for(int i=0; i<numProcesses; i++) {
                boolean flag = false;
                for(int j=0; j<numResources; j++) {
                    
                    if(safe.get(i) == false) {
                        if(remainingneed.get(i)[j]<=work[j]) {
                            flag = true;
                        }
                        if(remainingneed.get(i)[j]>work[j]) {
                            flag = false;
                            break;
                        }
                    }
                }

                if(flag) {
                    seq.add(i); 
                    safe.set(i, true);
                    for(int j=0; j<numResources; j++) {
                        work[j] += allocated.get(i)[j];
                    }

                }

            }
        }
        
        return seq;
    }


}
