// Implement Round Robin CPU scheduling algorithm.
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int processId, arrivalTime, burstTime, completionTime, waitingTime, turnAroundTime;
} process;

int compare(const void *a, const void *b)
{
    process *p = (process *)a;
    process *q = (process *)b;
    if (p->arrivalTime != q->arrivalTime)
        return (p->arrivalTime - q->arrivalTime);
    return (p->processId - q->processId);
}

void updateQueue(int queue[], int timer, process processes[], int n, int maxProccessIndex)
{
    int zeroIndex;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] == 0)
        {
            zeroIndex = i;
            break;
        }
    }
    queue[zeroIndex] = maxProccessIndex + 1;
}

void maintainQueue(int queue[], int n)
{
    for (int i = 0; (i < n - 1) && (queue[i + 1] != 0); i++)
    {
        int temp = queue[i];
        queue[i] = queue[i + 1];
        queue[i + 1] = temp;
    }
}

void checkNewArrival(int timer, process processes[], int n, int maxProccessIndex, int queue[])
{
    if (timer <= processes[n - 1].arrivalTime)
    {
        bool newArrival = false;
        for (int j = (maxProccessIndex + 1); j < n; j++)
        {
            if (processes[j].arrivalTime <= timer)
            {
                if (maxProccessIndex < j)
                {
                    maxProccessIndex = j;
                    newArrival = true;
                }
            }
        }
        // adding to ready queue
        if (newArrival)
            updateQueue(queue, timer, processes, n, maxProccessIndex);
    }
}

int main()
{
    int numberOfProcesses, timeQuantum, timer = 0, maxProccessIndex = 0;
    double averageWaitingTime = 0, averageTurnAroundTime = 0;
    printf("Please enter the number of Processes: \n");
    scanf("%d", &numberOfProcesses);
    process processes[numberOfProcesses];
    char choice;
    printf("(a)All arriving at Time 0\n(b)All arrive at different time\nPlease Enter your choice: \n");
    scanf(" %c", &choice);
    int tempBurstTime[numberOfProcesses], queue[numberOfProcesses];
    for (int i = 0; i < numberOfProcesses; i++)
    {
        printf("Please Enter the process id, arrival time and burst time of the Process %d: \n", i + 1);
        scanf(" %d %d %d", &processes[i].processId, &processes[i].arrivalTime, &processes[i].burstTime);
        tempBurstTime[i] = processes[i].burstTime;
    }
    printf("Please enter the Time Quantum: \n");
    scanf("%d", &timeQuantum);
    qsort((void *)processes, numberOfProcesses, sizeof(processes[0]), compare);
    bool completed[numberOfProcesses];
    for (int i = 0; i < numberOfProcesses; i++)
    {
        completed[i] = false;
        queue[i] = 0;
    }
    if (choice == 'a')
    {
        while (timer < processes[0].arrivalTime)
            timer++;
        queue[0] = 1;
        while (true)
        {
            bool flag = true;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (tempBurstTime[i] != 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                break;
            for (int i = 0; (i < numberOfProcesses) && (queue[i] != 0); i++)
            {
                int counter = 0;
                while ((counter < timeQuantum) && (tempBurstTime[queue[0] - 1] > 0))
                {
                    tempBurstTime[queue[0] - 1] -= 1;
                    timer += 1;
                    counter++;
                    // Checking & updating the ready queue until time=timer
                    checkNewArrival(timer, processes, numberOfProcesses, maxProccessIndex, queue);
                }
                // If a process is completed, mark completed as true and store completion time
                if ((tempBurstTime[queue[0] - 1] == 0) && (completed[queue[0] - 1] == false))
                {
                    processes[queue[0] - 1].completionTime = timer;
                    completed[queue[0] - 1] = true;
                }
                // checks whether or not CPU is idle
                bool idle = true;
                if (queue[numberOfProcesses - 1] == 0)
                {
                    for (int i = 0; i < numberOfProcesses && queue[i] != 0; i++)
                    {
                        if (completed[queue[i] - 1] == false)
                        {
                            idle = false;
                        }
                    }
                }
                else
                    idle = false;
                if (idle)
                {
                    timer++;
                    checkNewArrival(timer, processes, numberOfProcesses, maxProccessIndex, queue);
                }
                // Maintaining the entries of processes after each premption in the ready Queue
                maintainQueue(queue, numberOfProcesses);
            }
        }
        for (int i = 0; i < numberOfProcesses; i++)
        {
            processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime);
            processes[i].waitingTime = (processes[i].turnAroundTime - processes[i].burstTime);
            averageTurnAroundTime += processes[i].turnAroundTime;
            averageWaitingTime += processes[i].waitingTime;
        }
        averageTurnAroundTime /= numberOfProcesses;
        averageWaitingTime /= numberOfProcesses;
        printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \n");
        for (int i = 0; i < numberOfProcesses; i++)
        {
            printf("%d \t %d \t %d \t %d \t %d \t %d \n", processes[i].processId, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnAroundTime);
        }
        printf("The average Waiting Time is %lf \n", averageWaitingTime);
        printf("The average Turn Around Time is %lf \n", averageTurnAroundTime);
    }
    else if (choice == 'b')
    {
        while (timer < processes[0].arrivalTime)
            timer++;
        queue[0] = 1;
        while (true)
        {
            bool flag = true;
            for (int i = 0; i < numberOfProcesses; i++)
            {
                if (tempBurstTime[i] != 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                break;

            for (int i = 0; (i < numberOfProcesses) && (queue[i] != 0); i++)
            {
                int counter = 0;
                while ((counter < timeQuantum) && (tempBurstTime[queue[0] - 1] > 0))
                {
                    tempBurstTime[queue[0] - 1] -= 1;
                    timer += 1;
                    counter++;
                    // Checking & updating the ready queue until time=timer
                    checkNewArrival(timer, processes, numberOfProcesses, maxProccessIndex, queue);
                }
                // If a process is completed, mark completed as true and store completion time
                if ((tempBurstTime[queue[0] - 1] == 0) && (completed[queue[0] - 1] == false))
                {
                    processes[queue[0] - 1].completionTime = timer;
                    completed[queue[0] - 1] = true;
                }
                // checks whether or not CPU is idle
                bool idle = true;
                if (queue[numberOfProcesses - 1] == 0)
                {
                    for (int i = 0; i < numberOfProcesses && queue[i] != 0; i++)
                    {
                        if (completed[queue[i] - 1] == false)
                        {
                            idle = false;
                        }
                    }
                }
                else
                    idle = false;
                if (idle)
                {
                    timer++;
                    checkNewArrival(timer, processes, numberOfProcesses, maxProccessIndex, queue);
                }
                // Maintaining the entries of processes after each premption in the ready Queue
                maintainQueue(queue, numberOfProcesses);
            }
        }
        for (int i = 0; i < numberOfProcesses; i++)
        {
            processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime);
            processes[i].waitingTime = (processes[i].turnAroundTime - processes[i].burstTime);
            averageTurnAroundTime += processes[i].turnAroundTime;
            averageWaitingTime += processes[i].waitingTime;
        }
        averageTurnAroundTime /= numberOfProcesses;
        averageWaitingTime /= numberOfProcesses;
        printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \n");
        for (int i = 0; i < numberOfProcesses; i++)
        {
            printf("%d \t %d \t %d \t %d \t %d \t %d \n", processes[i].processId, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnAroundTime);
        }
        printf("The average Waiting Time is %lf \n", averageWaitingTime);
        printf("The average Turn Around Time is %lf \n", averageTurnAroundTime);
    }
    else
    {
        printf("You've entered the wrong choice. Try again\n");
    }
    return 0;
}

