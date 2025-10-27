// Online C compiler to run C program online
#include <stdio.h>
struct Process
{
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int pid;
    
};
int main() {
    int n;
    printf("Enter the no of processes : ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes\n");
        return 1;
    }

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time for process %d : ", i);
        scanf("%d", &p[i].at);
        printf("Enter the burst time for process %d : ", i);
        scanf("%d", &p[i].bt);
        p[i].pid = i;
    }

    // sort by arrival time (stable enough for small n)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time1 = 0;
    for (int i = 0; i < n; i++) {
        if (time1 < p[i].at) {
            time1 = p[i].at;
        }
        p[i].ct = time1 + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        time1 += p[i].bt;
    }

    // print header and rows, while computing totals
    int total_tat = 0;
    int total_wt = 0;
    printf("\n\tPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    double avg_tat = (double)total_tat / n;
    double avg_wt = (double)total_wt / n;
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    printf("Average Waiting Time    = %.2f\n", avg_wt);

    // print simple Gantt-like timeline
    printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("\tp[%d]\t|", p[i].pid);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("\t\t%d", p[i].ct);
    }
    printf("\n\n");
    return 0;
}