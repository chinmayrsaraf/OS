#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; 
int in = 0;    
int out = 0;  

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int id = *(int *)arg;
    int min_value = 0;
    int max_value = 5;
    for (int i = 0; i < 10; ++i) {
        // int item = rand() % 100; // Produce a random item
        int item = rand() %(max_value - min_value + 1) + min_value;; // Produce a random item
        
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            // Buffer is full, wait for it to become not full
            printf("Producer %d: Buffer is full. Waiting...\n", id);
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        ++count;

        printf("Producer %d produced: %d\n", id, item);

        if (count == 1) {
            // Buffer was empty, signal consumers
            printf("Producer %d: Signaling consumers...\n", id);
            pthread_cond_signal(&not_empty);
        }

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            // Buffer is empty, wait for it to become not empty
            printf("Consumer %d: Buffer is empty. Waiting...\n", id);
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        --count;

        printf("Consumer %d consumed: %d\n", id, item);

        if (count == BUFFER_SIZE - 1) {
            // Buffer was full, signal producers
            printf("Consumer %d: Signaling producers...\n", id);
            pthread_cond_signal(&not_full);
        }

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producer_threads[3];
    pthread_t consumer_threads[3];

    int producer_ids[3];
    int consumer_ids[3];

    // Initialize producer and consumer thread IDs
    for (int i = 0; i < 3; ++i) {
        producer_ids[i] = i;
        consumer_ids[i] = i;
    }

    // Create producer and consumer threads
    for (int i = 0; i < 3; ++i) {
        pthread_create(&producer_threads[i], NULL, producer, &producer_ids[i]);
        pthread_create(&consumer_threads[i], NULL, consumer, &consumer_ids[i]);
    }

    // Join threads 
    for (int i = 0; i < 3; ++i) {
        pthread_join(producer_threads[i], NULL);
        pthread_join(consumer_threads[i], NULL);
    }

    return 0;
}


