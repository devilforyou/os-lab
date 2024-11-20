#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], priority[n], wt[n], tat[n];

    for (int i = 0; i < n; i++) {
        printf(" P[%d] : Arrival Time ", i + 1);
        scanf("%d", &at[i]);
        printf(" P[%d] : Burst Time ", i + 1);
        scanf("%d", &bt[i]);
        printf(" P[%d] : Priority :", i + 1);
        scanf("%d", &priority[i]);
        
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] < priority[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = priority[j];
                priority[j] = priority[j + 1];
                priority[j + 1] = temp;
            }
        }
    }

    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] > currentTime) {
            currentTime = at[i];
        }
        wt[i] = currentTime - at[i];
        tat[i] = wt[i] + bt[i];
        currentTime += bt[i];
    }

    printf("PID\tBT\tAT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], at[i], priority[i], wt[i], tat[i]);
    }

    int totalWT = 0;
    int totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT / n);

    return 0;
}
