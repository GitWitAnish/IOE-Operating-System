// First-Come, First-Served (FCFS) Scheduling Algorithm in C


#include <stdio.h>

int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], wt[n], tat[n]; // burst, arrival, waiting, turnaround
    char pname[n]; // process names like A, B, C...

    // Input process info
    for (i = 0; i < n; i++) {
        pname[i] = 'A' + i; // Assign names A, B, C...
        printf("\nProcess %c\n", pname[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
    }

    // Calculate waiting time
    wt[0] = 0; // first process has 0 waiting time
    for (i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1]; // previous waiting + previous burst
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
