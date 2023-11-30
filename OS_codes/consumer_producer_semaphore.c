
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 8
#define NUM_CONSUMERS 3

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

sem_t mutex, empty, full;

void* producer(void* arg) {
    int item;
    while(1){
    for (int i = 0; i < BUFFER_SIZE ; i++) {
        item = (rand() % BUFFER_SIZE) + 1; // Generate item between 1 and BUFFER_SIZE (inclusive)
        sem_wait(&empty);
        sem_wait(&mutex);

        // Produce item and add it to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Producer produced item %d (Buffer: %d/%d)\n", item, count, BUFFER_SIZE);
        if (count == BUFFER_SIZE) {
            printf("Buffer is full\n");
        }

        // -------------------------------------

    //    for(int i = 0; i<BUFFER_SIZE; i++){
    //         printf("%d ",buffer[i]);
    //     }
    //     printf("\n");
    //     printf("\n"); 

        // -----------------------------------------

        sem_post(&mutex);
        sem_post(&full);

        usleep(rand() % 1000);
    }

    } 
    return NULL;


}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        while (1)
        {
        
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumer consumed item %d (Buffer: %d/%d)\n", item, count, BUFFER_SIZE);

        if (count == 0) {
            printf("Buffer is empty\n");
        }

        

        sem_post(&mutex);
        sem_post(&empty);

        usleep(rand() % 100);
        }
        
        
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];


    // sem_init is used for initial instalisation of semaphore value
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);//initialisation of semaphore!
    sem_init(&full, 0, 0);
while (1)
{
     for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
        
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    sleep(500);

     // Cancel the threads (optional)
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_cancel(producers[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_cancel(consumers[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    } 

    /* for (int i = 0; i < 10; i++)
    {
        
        pthread_join(consumers[i], NULL);
        pthread_join(producers[i], NULL);
        pthread_create(&consumers[i], NULL, consumer, NULL);
        pthread_create(&producers[i], NULL, producer, NULL);
    } */
     

}

    // sem_destroy is used when use of semaphore is done!
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
