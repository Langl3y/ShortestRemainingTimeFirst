#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completed;
};

void srtf_scheduling(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int shortest_job = -1;
        int shortest_burst_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < shortest_burst_time) {
                    shortest_job = i;
                    shortest_burst_time = processes[i].remaining_time;
                }
            }
        }

        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        processes[shortest_job].remaining_time--;
        current_time++;

        if (processes[shortest_job].start_time == -1)
            processes[shortest_job].start_time = current_time - 1;

        if (processes[shortest_job].remaining_time == 0) {
            processes[shortest_job].finish_time = current_time;
            processes[shortest_job].waiting_time = processes[shortest_job].finish_time - processes[shortest_job].burst_time - processes[shortest_job].arrival_time;
            processes[shortest_job].turnaround_time = processes[shortest_job].finish_time - processes[shortest_job].arrival_time;

            processes[shortest_job].completed = 1;
            completed_processes++;
        }
    }
}

void display_process_details(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nSRTF Scheduling Simulator:\n");

    for (int i = 0; i < n; i++) {
        printf("PID: %d\tArrival Time: %d\tBurst Time: %d\tStart Time: %d\tFinish Time: %d\tWaiting Time: %d\tTurnaround Time: %d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].start_time,
               processes[i].finish_time, processes[i].waiting_time, processes[i].turnaround_time);

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    double average_waiting_time = (double) total_waiting_time / n;
    double average_turnaround_time = (double) total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2lf\n", average_waiting_time);
    printf("Average Turnaround Time: %.2lf\n", average_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process %d's Burst time and Arrival time: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].arrival_time);
        processes[i].pid = i + 1;
        processes[i].start_time = -1;
        processes[i].finish_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }

    srtf_scheduling(processes, n);

    display_process_details(processes, n);

    return 0;
}