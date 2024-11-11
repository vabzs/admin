#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void RoundRobin(struct Process proc[], int n, int quantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    
    // Initialize remaining_time for each process to burst_time
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (completed < n) {
        int process_run = 0; // Track if any process ran in this iteration

        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= time) {
                // Process is ready to execute
                process_run = 1;
                
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].remaining_time = 0;
                    proc[i].completion_time = time;
                    proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                    completed++;
                }
            }
        }

        // If no process ran, increment time
        if (process_run == 0) {
            time++;
        }
    }

    printf("Round Robin Schedule:\n");
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    struct Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 3;

    RoundRobin(proc, n, quantum);

    return 0;
}