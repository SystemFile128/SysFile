#include <stdio.h>

int main() {
    int n, i, at[20], bt[20], wt[20], tat[20], avwt = 0, avtat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1] - at[i] + at[i - 1];
        avwt += wt[i];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avtat += tat[i];
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    avwt /= n;
    avtat /= n;

    printf("Average Waiting Time: %d\n", avwt);
    printf("Average Turnaround Time: %d\n", avtat);

    return 0;
}