
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
// #include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS]; // Array to hold thread IDs for philosophers
sem_t forks[NUM_PHILOSOPHERS];            // Array of semaphores, one for each fork

void *philosopher(void *arg)
{
    int id = *((int *)arg); // Extract philosopher's ID from the argument
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS; // Calculate the ID of the right fork

    while (1)
    {
        // Philosopher is thinking
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 5); // Sleep for a random amount of time (simulating thinking)

        // Philosopher is hungry
        printf("Philosopher %d is hungry\n", id);

        // Pick up the left fork
        sem_wait(&forks[left_fork]);
        printf("Philosopher %d picked up left fork %d\n", id, left_fork);

        // Pick up the right fork
        sem_wait(&forks[right_fork]);
        printf("Philosopher %d picked up right fork %d\n", id, right_fork);

        // Philosopher is eating
        printf("Philosopher %d is eating\n", id);
        sleep(rand() % 5); // Sleep for a random amount of time (simulating eating)

        // Put down the right fork
        sem_post(&forks[right_fork]);
        printf("Philosopher %d put down right fork %d\n", id, right_fork);

        // Put down the left fork
        sem_post(&forks[left_fork]);
        printf("Philosopher %d put down left fork %d\n", id, left_fork);
    }
}

int main()
{
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1); // Initialize each fork semaphore with a value of 1 (unlocked)
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]); // Create a philosopher thread
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL); // Wait for each philosopher thread to finish
    }

    // Destroy semaphores for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]); // Clean up semaphores
    }

    return 0;
}
