/* #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define NUM_READERS 3
#define NUM_WRITERS 1

int data = 0;
int reader_count = 0;
pthread_mutex_t mutex, resource;

void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        reader_count++;
         printf("Reader %d entering the database\n",reader_id);
        if (reader_count == 1) {
            pthread_mutex_lock(&resource);
        }
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading data\n", reader_id);

        pthread_mutex_lock(&mutex);
        reader_count--;
        printf("Reader %d leaving the database\n",reader_id);
        if (reader_count == 0) {
            printf("All readers left the database\n");
            pthread_mutex_unlock(&resource);
        }
        pthread_mutex_unlock(&mutex);

       
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (1) {
        pthread_mutex_lock(&resource);
        printf("Writer entering the database\n");
        printf("Writer %d is writing data\n", writer_id);

        pthread_mutex_unlock(&resource);
        printf("Writer leaving the database\n");
        
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_id = 1;

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_id);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&resource);

    return 0;
}
 */


// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <unistd.h>

// #define NUM_READERS 4
// #define NUM_WRITERS 10

// int data = 0;
// int readerCount = 0;
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t readCondition = PTHREAD_COND_INITIALIZER;
// pthread_cond_t writeCondition = PTHREAD_COND_INITIALIZER;

// void* reader(void* arg) {
//     int readerId = *(int*)arg;
//     while (1) {
//         pthread_mutex_lock(&mutex);
//         readerCount++;
//         if (readerCount == 1) {
//             pthread_cond_wait(&writeCondition, &mutex);
//         }
//         pthread_mutex_unlock(&mutex);

//         printf("Reader %d entering the database\n", readerId);
//         // Read data

//         // sleep(2000);

//         pthread_mutex_lock(&mutex);
//         printf("Reader %d leaving the database\n", readerId);
//         readerCount--;
//         if (readerCount == 0) {
//             pthread_cond_signal(&readCondition);
//         }
//         pthread_mutex_unlock(&mutex);

//         // usleep(2000);
//         usleep(rand() % 2);
//     }
//     return NULL;
// }

// void* writer(void* arg) {
//     int writerId = *(int*)arg;
//     while (1) {
//         pthread_mutex_lock(&mutex);
//         pthread_cond_wait(&readCondition, &mutex);
//         printf("Writer %d entering the database\n", writerId);
//         // Write data

//         printf("Writer %d leaving the database\n", writerId);
//         pthread_cond_signal(&writeCondition);
//         pthread_mutex_unlock(&mutex);

//         // usleep(2000);
//         usleep(rand() % 2);
//     }
//     return NULL;
// }

// int main() {
//     pthread_t readers[NUM_READERS];
//     pthread_t writers[NUM_WRITERS];
//     int readerIds[NUM_READERS];
//     int writerIds[NUM_WRITERS];

//     for (int i = 0; i < NUM_READERS; i++) {
//         readerIds[i] = i + 1;
//         pthread_create(&readers[i], NULL, reader, &readerIds[i]);
//     }

//     for (int i = 0; i < NUM_WRITERS; i++) {
//         writerIds[i] = i + 1;
//         pthread_create(&writers[i], NULL, writer, &writerIds[i]);
//     }

//     for (int i = 0; i < NUM_READERS; i++) {
//         pthread_join(readers[i], NULL);
//     }

//     for (int i = 0; i < NUM_WRITERS; i++) {
//         pthread_join(writers[i], NULL);
//     }

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 4
#define NUM_WRITERS 10

int data = 0;
int readerCount = 0;
pthread_mutex_t mutex;
pthread_cond_t readCondition;
pthread_cond_t writeCondition;

void* reader(void* arg) {
    int readerId = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (readerCount == -1) {
            pthread_cond_wait(&readCondition, &mutex);
        }
        readerCount++;
        pthread_mutex_unlock(&mutex);

        printf("Reader %d entering the database\n", readerId);
        // Read data

        pthread_mutex_lock(&mutex);
        printf("Reader %d leaving the database\n", readerId);
        readerCount--;
        if (readerCount == 0) {
            pthread_cond_signal(&writeCondition);
        }
        pthread_mutex_unlock(&mutex);

        // usleep(rand() % 2);
        usleep(100000); // sleep for 100ms
    }
    return NULL;
}

void* writer(void* arg) {
    int writerId = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (readerCount != 0) {
            pthread_cond_wait(&writeCondition, &mutex);
        }
        readerCount = -1; // Block readers
        pthread_mutex_unlock(&mutex);

        printf("Writer %d entering the database\n", writerId);
        // Write data

        printf("Writer %d leaving the database\n", writerId);

        pthread_mutex_lock(&mutex);
        readerCount = 0; // Unblock readers
        pthread_cond_broadcast(&readCondition);
        pthread_cond_signal(&writeCondition);
        pthread_mutex_unlock(&mutex);

        // usleep(rand() % 2);
        usleep(100000); // sleep for 100ms
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int readerIds[NUM_READERS];
    int writerIds[NUM_WRITERS];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&readCondition, NULL);
    pthread_cond_init(&writeCondition, NULL);

    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&readCondition);
    pthread_cond_destroy(&writeCondition);

    return 0;
}
