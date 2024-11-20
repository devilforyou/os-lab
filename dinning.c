#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5 // number of philosophers

pthread_mutex_t forks[N]; // mutexes for forks
pthread_t philosophers[N]; // threads for philosophers

void* philosopher(void* arg) {
    int id = (int)arg;
    int left = id;
    int right = (id + 1) % N;

    // pick up forks
    pthread_mutex_lock(&forks[left]);
    pthread_mutex_lock(&forks[right]);

    // eat
    printf("Philosopher %d is eating\n", id);
    sleep(1); // simulate eating

    // put down forks
    pthread_mutex_unlock(&forks[right]);
    pthread_mutex_unlock(&forks[left]);

    return NULL;
}

int main() {
    int i;
    int philosopher_ids[N];

    // initialize mutexes
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // create threads for philosophers
    for (i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // wait for all philosophers to finish
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // clean up
    for (i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
