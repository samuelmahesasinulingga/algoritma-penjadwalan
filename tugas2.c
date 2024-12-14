#include <stdio.h>
#include <limits.h>

typedef struct
{
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void calculateSJFPreemptive(Process processes[], int n)
{
    int time = 0, completed = 0;
    while (completed < n)
    {
        int shortest = -1;
        int minRemainingTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minRemainingTime)
            {
                shortest = i;
                minRemainingTime = processes[i].remainingTime;
            }
        }

        if (shortest == -1)
        {
            time++;
            continue;
        }

        processes[shortest].remainingTime--;
        time++;

        if (processes[shortest].remainingTime == 0)
        {
            completed++;
            processes[shortest].turnaroundTime = time - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
        }
    }
}

void printResults(Process processes[], int n)
{
    float totalWaiting = 0, totalTurnaround = 0;
    printf("\nID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
        totalWaiting += processes[i].waitingTime;
        totalTurnaround += processes[i].turnaroundTime;
    }
    printf("Average Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    calculateSJFPreemptive(processes, n);
    printResults(processes, n);

    return 0;
}
