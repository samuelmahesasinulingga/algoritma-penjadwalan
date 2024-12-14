#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int id;             // ID proses, digunakan untuk mengidentifikasi proses.
    int burstTime;      // Burst time asli, yaitu total waktu eksekusi proses.
    int remainingTime;  // Waktu burst tersisa, yaitu waktu eksekusi yang masih diperlukan.
    int waitingTime;    // Waktu tunggu, dihitung sebagai total waktu proses menunggu giliran eksekusi.
    int turnaroundTime; // Turnaround time, yaitu waktu sejak proses dimulai hingga selesai eksekusi.
    char type;          // Jenis proses, 'S' untuk proses sistem dan 'U' untuk proses pengguna.
} Process;

void calculateRoundRobin(Process processes[], int n, int quantumSystem, int quantumUser)
{
    int time = 0, completed = 0;
    while (completed < n)
    {
        bool processExecuted = false;

        // Prioritas proses sistem
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remainingTime > 0 && processes[i].type == 'S')
            {
                processExecuted = true;
                int quantum = quantumSystem;

                if (processes[i].remainingTime <= quantum)
                {
                    time += processes[i].remainingTime;
                    processes[i].waitingTime = time - processes[i].burstTime;
                    processes[i].turnaroundTime = time;
                    processes[i].remainingTime = 0;
                    completed++;
                }
                else
                {
                    time += quantum;
                    processes[i].remainingTime -= quantum;
                }
            }
        }

        // Proses pengguna jika tidak ada proses sistem
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remainingTime > 0 && processes[i].type == 'U')
            {
                processExecuted = true;
                int quantum = quantumUser;

                if (processes[i].remainingTime <= quantum)
                {
                    time += processes[i].remainingTime;
                    processes[i].waitingTime = time - processes[i].burstTime;
                    processes[i].turnaroundTime = time;
                    processes[i].remainingTime = 0;
                    completed++;
                }
                else
                {
                    time += quantum;
                    processes[i].remainingTime -= quantum;
                }
            }
        }

        // Jika tidak ada proses yang dapat dieksekusi, waktu idle
        if (!processExecuted)
        {
            time++;
        }
    }
}

void printResults(Process processes[], int n)
{
    float totalWaiting = 0, totalTurnaround = 0;
    printf("\nID\tType\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%c\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].type, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
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
        printf("Enter Burst Time and Type (S for system, U for user) for Process %d: ", i + 1);
        scanf("%d %c", &processes[i].burstTime, &processes[i].type);
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    calculateRoundRobin(processes, n, 5, 2);
    printResults(processes, n);

    return 0;
}
