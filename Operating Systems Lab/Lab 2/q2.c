// This program is done by CS20B1044 Avinash R Changrani
// Implement First Come First Serve CPU scheduling algorithm.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processId,arrivalTime,burstTime,completionTime,waitingTime,turnAroundTime;
} process;

int compare1(const void* a, const void* b){
    process* p = (process*) a;
    process* q = (process*) b;
    return (p->processId - q->processId);
}

int compare2(const void* a, const void* b){
    process* p = (process*) a;
    process* q = (process*) b;
    return (p->arrivalTime - q->arrivalTime);
}


int main(){
    int numberOfProcesses;
    double averageWaitingTime = 0, averageTurnAroundTime = 0;
    printf("Please Enter the number of processes: \n");
    scanf("%d", &numberOfProcesses);
    process processes[numberOfProcesses];
    char choice;
    printf("a)All arriving at time 0 \nb)All arrive at different time \nPlease Enter your choice: \n");
    scanf(" %c", &choice);
    for(int i = 0; i < numberOfProcesses;i++){
        printf("Please Enter the process Id, arrival time and Burst time of Process %d : \n", i+1);
        scanf(" %d %d %d", &processes[i].processId, &processes[i].arrivalTime, &processes[i].burstTime);
    }
    switch(choice){
        case 'a':
            qsort((void*) processes, numberOfProcesses, sizeof(processes[0]),compare1);
            processes[0].completionTime = processes[0].burstTime;
            for(int i = 1; i < numberOfProcesses;i++){
                processes[i].completionTime = (processes[i-1].completionTime + processes[i].burstTime);
            }
            for(int i = 0; i < numberOfProcesses;i++){
                processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime);
                averageTurnAroundTime += processes[i].turnAroundTime;
            }
            for(int i = 0; i < numberOfProcesses;i++){
                processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                averageWaitingTime += processes[i].waitingTime;
            }
            averageWaitingTime /= numberOfProcesses;
            averageTurnAroundTime /= numberOfProcesses;
            printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \n");
            for(int i = 0; i < numberOfProcesses;i++){
                printf("%d \t %d \t %d \t %d \t %d \t %d \n",processes[i].processId,processes[i].arrivalTime,processes[i].burstTime,processes[i].completionTime,processes[i].waitingTime,processes[i].turnAroundTime);
            }
            printf("The Average Waiting Time is %lf \n", averageWaitingTime);
            printf("The Average Turn Around Time is %lf \n", averageTurnAroundTime);
            break;
        case 'b':
            qsort((void*) processes, numberOfProcesses, sizeof(processes[0]),compare2);
            processes[0].completionTime = processes[0].burstTime;
            for(int i = 1; i < numberOfProcesses;i++){
                processes[i].completionTime = (processes[i-1].completionTime + processes[i].burstTime);
            }
            for(int i = 0; i < numberOfProcesses;i++){
                processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime);
                averageTurnAroundTime += processes[i].turnAroundTime;
            }
            for(int i = 0; i < numberOfProcesses;i++){
                processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                averageWaitingTime += processes[i].waitingTime;
            }
            averageWaitingTime /= numberOfProcesses;
            averageTurnAroundTime /= numberOfProcesses;
            printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \n");
            for(int i = 0; i < numberOfProcesses;i++){
                printf("%d \t %d \t %d \t %d \t %d \t %d \n",processes[i].processId,processes[i].arrivalTime,processes[i].burstTime,processes[i].completionTime,processes[i].waitingTime,processes[i].turnAroundTime);
            }
            printf("The Average Waiting Time is %lf \n", averageWaitingTime);
            printf("The Average Turn Around Time is %lf \n", averageTurnAroundTime);
            break;
        default:
            break;
    }
    return 0;
}

