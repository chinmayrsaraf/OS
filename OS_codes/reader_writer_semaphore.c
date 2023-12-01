/* 
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
 */
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


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
int N = 3; 
sem_t db, mutex;  
int rc = 0; 
void read_db(int i)  
{
    printf("\nreader %d is reading", i);
    // printf("\nreader %d: %d %d %d", i, h, m, s);
}
void use_data() 
{
    printf("\nuse read data");
}
void reader(void *i)
{
    while (1) 
    {

        sem_wait(&mutex); 
        printf("\nreader %d is trying to enter into database", i);
        rc = rc + 1;
        if (rc == 1)
        {
            sem_wait(&db); 
        }
        printf("\nreader %d entered", i);
        sem_post(&mutex); 
        read_db(((int)i));
        sem_wait(&mutex);
        rc = rc - 1;
        printf("\nreader %d is exiting database", i);
        if (rc == 0)
        {
            sem_post(&db);  
        }
        sem_post(&mutex); 
        
        sleep(2); 
    }
}
void think_up_data(int i)
{
    printf("\nwriter %d thinking data", i);
}
void write_database(int i)
{
    printf("\nwriter %d writing database", i);

}
void writer(void *i)
{
    while (1)
    {
        think_up_data((int)i);
        printf("\nwriter %d trying to enter into database", i);
        sem_wait(&db);
        printf("\nwriter %d is entered into database", i);
        write_database((int)i);
        printf("\nwriter %d is exiting database", i);
        sem_post(&db);
        sleep(2);
    }
}
int main()
{
    pthread_t r[N], w[N];
    sem_init(&db, 0, 1);
    sem_init(&mutex, 0, 1);
    void *status;
    for (int i = 0; i < N; i++)
    {
        pthread_create(&w[i], NULL, (void *)&writer, (void *)i);
        pthread_create(&r[i], NULL, (void *)&reader, (void *)i);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(r[i], status);
        pthread_join(w[i], status);
    }
    for (int i = 0; i < N; i++)
    {
        sem_destroy(&db);
        sem_destroy(&mutex);
    }
}
