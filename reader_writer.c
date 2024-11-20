#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define NUM_READ_CYCLES 3 // Number of times each reader reads
#define NUM_WRITE_CYCLES 2 // Number of times each writer writes


// Shared resource
int shared_resource = 0;

// Synchronization primitives
sem_t mutex;
sem_t rw_mutex;
int reader_count = 0;


void *reader(void *arg) {
    int reader_id = *(int *)arg;
    for (int i = 0; i < NUM_READ_CYCLES; i++) { // Read multiple times
        // Entry section
        sem_wait(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Critical section (reading)
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);
        usleep(100000); 

        // Exit section
        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        usleep(200000);
    }
    return NULL;
}


void *writer(void *arg) {
    int writer_id = *(int *)arg;
    for (int i = 0; i < NUM_WRITE_CYCLES; i++) { // Write multiple times
        // Entry section
        sem_wait(&rw_mutex);

        // Critical section (writing)
        shared_resource++;
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);
        usleep(200000);

        // Exit section
        sem_post(&rw_mutex);

        usleep(300000);
    }
    return NULL;
}

int main() {
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (wait for them to finish)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);


    printf("Program finished.\n");  // Indicate completion

    return 0;
}
