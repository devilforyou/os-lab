#include <stdio.h>
#include <stdlib.h> // For qsort

#define MAX_PROCESSES 100

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;


// Comparison function for qsort (to sort by arrival time)
int compareByArrival(const void *a, const void *b) {
    return ((Process *)a)->arrival_time - ((Process *)b)->arrival_time;
}


void calculateWaitingAndTurnaroundTimes(Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    int completed = 0, current_time = 0;

    // Sort processes by arrival time
    qsort(proc, n, sizeof(Process), compareByArrival);



    while (completed < n) {
        int shortest_job_index = -1;
        int shortest_burst_time = 9999; // Initialize with a large value

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0 && proc[i].remaining_time < shortest_burst_time) {
                shortest_burst_time = proc[i].remaining_time;
                shortest_job_index = i;
            }
        }



        if (shortest_job_index != -1) {

            // Run the selected process to completion
            current_time += proc[shortest_job_index].remaining_time;
            proc[shortest_job_index].remaining_time = 0;
            proc[shortest_job_index].turnaround_time = current_time - proc[shortest_job_index].arrival_time;
            proc[shortest_job_index].waiting_time = proc[shortest_job_index].turnaround_time - proc[shortest_job_index].burst_time;


            total_waiting_time += proc[shortest_job_index].waiting_time;
            total_turnaround_time += proc[shortest_job_index].turnaround_time;
            completed++;


        } else {

           current_time++; // Increment time if no process is available


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
