#include <stdio.h>
#include <string.h>

// Define a struct for process
struct Process {
    char name[10];
    int arrivalTime, burstTime, remainingTime, waitingTime, turnaroundTime, completionTime;
};

int main() {
    int n, timeQuantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter name, arrival time, burst time for process %d: ", i + 1);
        scanf("%s %d %d", p[i].name, &p[i].arrivalTime, &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
        p[i].completionTime = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    int t = 0; // current time
    int done;
    int index = 0; // Gantt chart position

    char gantt[200][10];  // To store names of processes executed (max 200 segments)
    int timeLine[200];    // To store corresponding time instants

    printf("\nGantt Chart:\n");

    while (1){
        done = 1;
        int found = 0; // track if any process is ready at this time

        // Go through each process
        for (int i = 0; i < n; i++) {
            if (p[i].remainingTime > 0 && p[i].arrivalTime <= t) {
                found = 1;
                done = 0;

                strcpy(gantt[index], p[i].name);
                timeLine[index] = t;
                index++;

                if (p[i].remainingTime > timeQuantum) {
                    t += timeQuantum;
                    p[i].remainingTime -= timeQuantum;
                } else {
                    t += p[i].remainingTime;
                    p[i].waitingTime = t - p[i].burstTime - p[i].arrivalTime;
                    p[i].completionTime = t;
                    p[i].remainingTime = 0;
                }
            }
        }

        // If CPU is idle (no ready process found)
        if (!found) {
            int earliestArrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (p[i].remainingTime > 0 && p[i].arrivalTime < earliestArrival) {
                    earliestArrival = p[i].arrivalTime;
                }
            }
            if (earliestArrival != 1e9 && earliestArrival > t) {
                // CPU is idle till the next process arrives
                strcpy(gantt[index], "idle");
                timeLine[index] = t;
                index++;
                t = earliestArrival; // jump to next arrival time
            }
        }

        // Check if all processes are done
        int allDone = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remainingTime > 0) {
                allDone = 0;
                break;
            }
        }
        if (allDone==1) {
            timeLine[index] = t; // final time
            break;
        }
    }

    // Print Gantt chart
    for (int i = 0; i < index; i++) {
        printf("\t| %s ", gantt[i]);
    }
    printf("\t|\n");

    for (int i = 0; i <= index; i++) {
        printf("\t%-5d", timeLine[i]);
    }
    printf("\n");

    // Calculate turnaround times
    for (int i = 0; i < n; i++) {
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
    }

    // Display results
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t\t%d\n",
               p[i].name, p[i].arrivalTime, p[i].burstTime,
               p[i].waitingTime, p[i].turnaroundTime, p[i].completionTime);
    }

    return 0;
}
