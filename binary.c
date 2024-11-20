#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared resource (e.g., a counter)
int shared_resource = 0;

// Binary semaphore
sem_t mutex;


// Function to increment the shared resource
void* increment(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {

        // Acquire the semaphore (wait/down/P operation)
        sem_wait(&mutex); // If semaphore is 0, thread blocks here

        // Critical section (accessing shared resource)
        int temp = shared_resource;
        temp++;
        shared_resource = temp;
        printf("Thread %ld: Incrementing. Value: %d\n", pthread_self(), shared_resource);

        // Release the semaphore (signal/up/V operation)
        sem_post(&mutex);

        usleep(100000); // Simulate some work
    }
    return NULL;
}

// Function to decrement the shared resource
void* decrement(void* arg) {
     int i;
    for (i = 0; i < 5; i++) {

        // Acquire the semaphore
        sem_wait(&mutex);

        // Critical section
        int temp = shared_resource;
        temp--;
        shared_resource = temp;
        printf("Thread %ld: Decrementing. Value: %d\n", pthread_self(), shared_resource);


        // Release the semaphore
        sem_post(&mutex);


        usleep(100000); //Simulate some work
    }

    return NULL;

}



int main() {
    // Initialize the semaphore to 1 (binary semaphore)
    if (sem_init(&mutex, 0, 1) != 0) {  // 0 = shared between threads, 1 = initial value
        perror("Semaphore initialization failed");
        return 1;
    }

    pthread_t thread1, thread2;

    // Create two threads
    if (pthread_create(&thread1, NULL, increment, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    if (pthread_create(&thread2, NULL, decrement, NULL) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    // Destroy the semaphore
    sem_destroy(&mutex);

    printf("Final value: %d\n", shared_resource);
    return 0;
}
