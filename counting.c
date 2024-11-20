#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Shared counter
int counter = 0;

// Semaphore to protect the counter
sem_t counting_semaphore;

// Function to be executed by each thread
void* increment_counter(void* arg) {
    int i;
    for (i = 0; i < 10000; i++) {
        // Wait on the semaphore (decrement count)
        sem_wait(&counting_semaphore); 

        // Critical section: access the shared resource
        counter++;

        // Post to the semaphore (increment count)
        sem_post(&counting_semaphore);
    }
    return NULL;
}

int main() {
    // Initialize the semaphore with an initial value of 1 (counting semaphore)
    if (sem_init(&counting_semaphore, 0, 1) != 0) {
        perror("Semaphore initialization failed");
        return 1;
    }

    pthread_t thread1, thread2;

    // Create two threads
    if (pthread_create(&thread1, NULL, increment_counter, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }
    if (pthread_create(&thread2, NULL, increment_counter, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphore
    sem_destroy(&counting_semaphore);


    printf("Final counter value: %d\n", counter);

    return 0;
}
