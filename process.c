#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid, pid1, pid2;

    pid = fork();
    if (pid == 0) {
        printf("Child 1 PID: %d\n", getpid());
        sleep(1);
        exit(0);
    } else if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == 0) {
        printf("Child 2 PID: %d\n", getpid());
        sleep(1);
        exit(0);
    } else if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("Child 3 PID: %d\n", getpid());
        sleep(1);
        exit(0);
    } else if (pid2 < 0) {
        perror("fork failed");
        exit(1);
    }

    printf("Parent PID: %d\n", getpid());
    return 0;
}
