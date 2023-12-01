import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


class Philosopher extends Thread {
    private int philosopherId;
    private Lock leftChopstick;
    private Lock rightChopstick;

    public Philosopher(int id) {
        this.philosopherId = id;
        this.leftChopstick = new ReentrantLock();
        this.rightChopstick = new ReentrantLock();
    }

    private void pickUpChopsticks() {
        leftChopstick.lock();
        rightChopstick.lock();
    }

    private void putDownChopsticks() {
        leftChopstick.unlock();
        rightChopstick.unlock();
    }

    private void think() throws InterruptedException {
        System.out.println("Philosopher " + philosopherId + " is thinking.");
        Thread.sleep((long) (Math.random() * 1000)); // Simulating thinking time
    }

    private void eat() throws InterruptedException {
        System.out.println("Philosopher " + philosopherId + " is eating.");
        Thread.sleep((long) (Math.random() * 1000)); // Simulating eating time
    }

    @Override
    public void run() {
        try {
            while (true) {
                think();
                pickUpChopsticks();
                eat();
                putDownChopsticks();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class DiningPhilosophers {
    public static void main(String[] args) {
        Philosopher[] philosophers = new Philosopher[5];

        for (int i = 0; i < 5; i++) {
            philosophers[i] = new Philosopher(i);
            philosophers[i].start();
        }
    }
}


//hiii