#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

void calculateWaitingAndTurnaroundTimes(Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int completed = 0, current_time = 0;

    while (completed < n) {
        int idx = -1;
        int min_remaining_time = 9999;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].remaining_time < min_remaining_time) {
                min_remaining_time = proc[i].remaining_time;
                idx = i;
            }
        }

        if (idx != -1) {
            proc[idx].remaining_time--;
            current_time++;

            if (proc[idx].remaining_time == 0) {
                proc[idx].turnaround_time = current_time - proc[idx].arrival_time;
                proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
                total_waiting_time += proc[idx].waiting_time;
                total_turnaround_time += proc[idx].turnaround_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[MAX_PROCESSES];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].id = i + 1;
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
    }

    calculateWaitingAndTurnaroundTimes(proc, n);

    return 0;
}
