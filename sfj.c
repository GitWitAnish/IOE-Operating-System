// Shortest Job First (SJF) Scheduling Algorithm in C

#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], wt[n], tat[n], temp;
    char pname[n];

    // Input burst and arrival times
    for (i = 0; i < n; i++) {
        pname[i] = 'A' + i; // process names A, B, C...
        printf("\nProcess %c\n", pname[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
    }

    // Sort processes based on burst time (simple SJF)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                // Swap burst times
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                // Swap process names
                char tname = pname[i];
                pname[i] = pname[j];
                pname[j] = tname;
                // Swap arrival times too
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
            }
        }
    }

    // Calculate waiting time
    wt[0] = 0; // first process waits 0
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }

    // Display results
    printf("\nProcess\tBT\tAT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%c\t%d\t%d\t%d\t%d\n", pname[i], bt[i], at[i], wt[i], tat[i]);
    }

    // Calculate averages
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
