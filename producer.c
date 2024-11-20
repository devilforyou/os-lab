#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 3
#define NUM_ITEMS 10

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Semaphores for synchronization
sem_t empty; // Counts empty slots in the buffer
sem_t full;  // Counts full slots in the buffer
pthread_mutex_t mutex; // Protects access to the buffer


void *producer(void *arg) {
    int item;
    for (item = 0; item < NUM_ITEMS; item++) {
        // Produce an item
        int produced_item = item;

        // Wait for an empty slot in the buffer
        sem_wait(&empty);
        // Acquire the lock to protect the buffer
        pthread_mutex_lock(&mutex);

        // Add the item to the buffer
        buffer[in] = produced_item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer produced: %d\n", produced_item);

        // Release the lock
        pthread_mutex_unlock(&mutex);
        // Signal that a full slot is now available
        sem_post(&full);

        // Simulate production time
        usleep(100000); // 0.1 seconds
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (item = 0; item < NUM_ITEMS; item++) {
        // Wait for a full slot in the buffer
        sem_wait(&full);
        // Acquire the lock to protect the buffer
        pthread_mutex_lock(&mutex);

        // Remove an item from the buffer
        int consumed_item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer consumed: %d\n", consumed_item);

        // Release the lock
        pthread_mutex_unlock(&mutex);
        // Signal that an empty slot is now available
        sem_post(&empty);

        // Simulate consumption time
        usleep(200000); // 0.2 seconds
    }
    return NULL;
}


int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);          // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy the semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
