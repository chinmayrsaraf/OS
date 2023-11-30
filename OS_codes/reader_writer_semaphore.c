
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 10

int data = 0;
int reader_count = 0;
sem_t resource, readc;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while(1){
        sem_wait(&readc);
      
        reader_count++;
         printf("Reader %d entering the database\n",reader_id);
        if (reader_count == 1) {
            sem_wait(&resource);
        }
       
        sem_post(&readc);

        printf("Reader %d is reading data\n", reader_id);

        sem_wait(&readc);
        printf("Reader %d leaving the database\n",reader_id);
        reader_count--;
        if (reader_count == 0) {
            printf("All readers left the database\n");
            sem_post(&resource);
        }
        sem_post(&readc);
        
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

 while(1){
        sem_wait(&resource);
        printf("Writer entering the database\n");
      
        printf("Writer %d is writing data\n", writer_id);

        sem_post(&resource);
        printf("Writer leaving the database\n");
        
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&resource, 0, 1);
    // sem_init(&readc, 0, 1);
    sem_init(&readc, 0, NUM_READERS);


    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_id = NUM_WRITERS;
    
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_id);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource);
    sem_destroy(&readc);

    return 0;
}

// -------------------------------
/* 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>

#define NUM_READERS 5
#define NUM_WRITERS 10

int data = 0;
int reader_count = 0;
sem_t readc;
sem_t resource;
pthread_mutex_t read_count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t writer_mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int terminate_program = 0;

void handle_termination(int signum) {
    terminate_program = 1;
}

void cleanup() {
    sem_destroy(&readc);
    sem_destroy(&resource);
    pthread_mutex_destroy(&read_count_mutex);
    pthread_mutex_destroy(&writer_mutex);
}

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (!terminate_program) {
        sem_wait(&readc);
        pthread_mutex_lock(&read_count_mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&resource);
        }
        pthread_mutex_unlock(&read_count_mutex);
        sem_post(&readc);

        printf("Reader %d entering the database\n", reader_id);
        // ... Reading ...
        printf("Reader %d is reading data\n", reader_id);

        sem_wait(&readc);
        pthread_mutex_lock(&read_count_mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&resource);
        }
        pthread_mutex_unlock(&read_count_mutex);
        sem_post(&readc);

        printf("Reader %d leaving the database\n", reader_id);

        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (!terminate_program) {
        pthread_mutex_lock(&writer_mutex);
        sem_wait(&resource);
        pthread_mutex_unlock(&writer_mutex);

        printf("Writer %d entering the database\n", writer_id);
        // ... Writing ...
        printf("Writer %d is writing data\n", writer_id);

        printf("Writer %d leaving the database\n", writer_id);
        sem_post(&resource);

        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&readc, 0, NUM_READERS);
    sem_init(&resource, 0, 1);

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Register signal handler for termination
    signal(SIGINT, handle_termination);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            fprintf(stderr, "Error creating reader thread %d\n", i);
            cleanup();
            return EXIT_FAILURE;
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            fprintf(stderr, "Error creating writer thread %d\n", i);
            cleanup();
            return EXIT_FAILURE;
        }
    }

    // Wait for termination signal
    while (!terminate_program) {
        sleep(1);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        if (pthread_join(readers[i], NULL) != 0) {
            fprintf(stderr, "Error joining reader thread %d\n", i);
            cleanup();
            return EXIT_FAILURE;
        }
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        if (pthread_join(writers[i], NULL) != 0) {
            fprintf(stderr, "Error joining writer thread %d\n", i);
            cleanup();
            return EXIT_FAILURE;
        }
    }

    cleanup();
    return EXIT_SUCCESS;
}
 */