#include <stdio.h>
#include <limits.h> // For INT_MAX

// Define a structure for Process
struct Process {
    int pid;             // Process ID
    int arrival_time;    // Arrival Time of the process
    int burst_time;      // Burst Time of the process
    int remaining_time;  // Remaining Burst Time
    int completion_time; // Completion Time of the process
    int waiting_time;    // Waiting Time of the process
    int turnaround_time; // Turnaround Time of the process
    int is_completed;    // Flag to check if the process is completed
};

// Function to implement SJF Preemptive Scheduling
void SJF_Preemptive(struct Process proc[], int n) {
    int current_time = 0;
    int completed = 0;
    
    // Initialize remaining time for each process and is_completed flag
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
    }
    
    while (completed != n) {
        int shortest_job = -1;
        int min_remaining_time = INT_MAX;
        
        // Find the process with the shortest remaining time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && !proc[i].is_completed) {
                if (proc[i].remaining_time < min_remaining_time) {
                    min_remaining_time = proc[i].remaining_time;
                    shortest_job = i;
                }
            }
        }

        // If a process is found
        if (shortest_job != -1) {
            proc[shortest_job].remaining_time--;
            current_time++;
            
            // Check if the process is completed
            if (proc[shortest_job].remaining_time == 0) {
                proc[shortest_job].completion_time = current_time;
                proc[shortest_job].turnaround_time = proc[shortest_job].completion_time - proc[shortest_job].arrival_time;
                proc[shortest_job].waiting_time = proc[shortest_job].turnaround_time - proc[shortest_job].burst_time;
                proc[shortest_job].is_completed = 1;
                completed++;
            }
        } else {
            // If no process is ready, increment the current time
            current_time++;
        }
    }

    // Display the results
    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes
    struct Process proc[] = {
        {1, 0, 7},  // Process 1 with arrival time 0, burst time 7
        {2, 2, 4},  // Process 2 with arrival time 2, burst time 4
        {3, 4, 1},  // Process 3 with arrival time 4, burst time 1
        {4, 5, 4}   // Process 4 with arrival time 5, burst time 4
    };

    int n = sizeof(proc) / sizeof(proc[0]);

    SJF_Preemptive(proc, n);

    return 0;
}
