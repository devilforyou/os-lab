#include <stdio.h>
int main() {
    int n, i, bt[10], at[10], wt[10], tat[10], temp[10], total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the burst time and arrival time for each process:\n");
    for (i = 0; i < n; i++) {
        printf(" P[%d] : Arrival Time ", i + 1);
        scanf("%d", &at[i]);
        printf(" P[%d] : Burst Time ", i + 1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }
    int time = 0, flag = 0;
    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);
    while (1) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (bt[i] > 0) {
                flag = 1;
                if (at[i] <= time) {
                    if (bt[i] > quantum) {
                        bt[i] -= quantum;
                        time += quantum;
                    } else {
                        time += bt[i];
                        bt[i] = 0;
                    }
                }
            }
        }
        if (flag == 0)
            break;
        time++;
    }
    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + temp[i - 1];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + temp[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, temp[i], at[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    return 0;
}
