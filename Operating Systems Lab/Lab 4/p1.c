// Implement Round Robin CPU scheduling algorithm.
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int processId, arrivalTime, burstTime, completionTime, waitingTime, turnAroundTime, responseTime;
} process;

int compare(const void *a, const void *b)
{
    process *p = (process *)a;
    process *q = (process *)b;
    if (p->arrivalTime != q->arrivalTime)
        return (p->arrivalTime - q->arrivalTime);
    return (p->processId - q->processId);
}

int comparepid(const void *a, const void *b)
{
    process *p = (process *)a;
    process *q = (process *)b;
    return (p->processId - q->processId);
}

int main()
{
    int numberOfProcesses, timeQuantum, timer = 0, maxProccessIndex = 0, contextSwitchingOverHead = 0, completed = 0, numberOfContextSwitches = 0;
    double averageWaitingTime = 0, averageTurnAroundTime = 0;
    printf("Please enter the number of Processes: \n");
    scanf("%d", &numberOfProcesses);
    process processes[numberOfProcesses];
    bool visited[numberOfProcesses];
    char choice;
    // printf("(a)All arriving at Time 0\n(b)All arrive at different time\nPlease Enter your choice: \n");
    // scanf(" %c", &choice);
    int tempBurstTime[numberOfProcesses], queue[numberOfProcesses];
    for (int i = 0; i < numberOfProcesses; i++)
    {
        printf("Please Enter the process id, arrival time and burst time of the Process %d: \n", i + 1);
        scanf(" %d %d %d", &processes[i].processId, &processes[i].arrivalTime, &processes[i].burstTime);
        tempBurstTime[i] = processes[i].burstTime;
        visited[i] = false;
    }
    printf("Please enter the Time Quantum: \n");
    scanf("%d", &timeQuantum);
    printf("Please enter the Context Context Switching OverHead: \n");
    scanf("%d", &contextSwitchingOverHead);
    qsort((void *)processes, numberOfProcesses, sizeof(processes[0]), compare);
    process readyQueue[1000];
    int front = 0, rear = 0, arrived = 0, index[1000];
    while (completed < numberOfProcesses)
    {
        for (timer = processes[arrived].arrivalTime; arrived < numberOfProcesses; arrived++)
        {
            if (processes[arrived].arrivalTime == timer)
            {
                readyQueue[rear] = processes[arrived];
                index[rear] = arrived;
                rear++;
            }
            else
                break;
        }
        while (front < rear)
        {
            if (visited[index[front]] == false)
            {
                processes[index[front]].responseTime = timer - processes[index[front]].arrivalTime;
                visited[index[front]] = true;
            }
            if (readyQueue[front].burstTime <= timeQuantum)
            {
                for (timer += readyQueue[front].burstTime; arrived < numberOfProcesses; arrived++)
                {
                    if (processes[arrived].arrivalTime <= timer)
                    {
                        readyQueue[rear] = processes[arrived];
                        index[rear] = arrived;
                        rear++;
                    }
                    else
                        break;
                }
                processes[index[front]].completionTime = timer;
                printf("%d    %d\n", index[front], timer);
                completed++;
            }
            else
            {
                for (timer += timeQuantum; arrived < numberOfProcesses; arrived++)
                {
                    if (processes[arrived].arrivalTime <= timer)
                    {
                        readyQueue[rear] = processes[arrived];
                        index[rear] = arrived;
                        rear++;
                    }
                    else
                        break;
                }
                readyQueue[front].burstTime -= timeQuantum;
                readyQueue[rear] = readyQueue[front];
                index[rear] = index[front];
                rear++;
            }
            front++;
            if (front < rear)
            {
                if (readyQueue[front].processId != readyQueue[front - 1].processId)
                {
                    for (timer += contextSwitchingOverHead; arrived < numberOfProcesses; arrived++)
                    {
                        if (processes[arrived].arrivalTime <= timer)
                        {
                            readyQueue[rear] = processes[arrived];
                            index[rear] = arrived;
                            rear++;
                        }
                        else
                            break;
                    }
                    // numberOfContextSwitches++;
                }
            }
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
    qsort((void *)processes, numberOfProcesses, sizeof(processes[0]), comparepid);
    printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \t Response Time \n");
    for (int i = 0; i < numberOfProcesses; i++)
    {
        printf("%d \t\t %d \t\t %d \t\t %d \t\t %d \t\t\t %d \t\t\t %d\n", processes[i].processId, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnAroundTime, processes[i].responseTime);
    }
    printf("The average Waiting Time is %lf \n", averageWaitingTime);
    printf("The average Turn Around Time is %lf \n", averageTurnAroundTime);
    // printf("The number of Context Switches is %d \n", numberOfContextSwitches);
    return 0;
}
