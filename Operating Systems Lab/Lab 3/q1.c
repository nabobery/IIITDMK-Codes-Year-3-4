// This program is done by CS20B1044 Avinash R Changrani
// Implement Shortest Job First Serve CPU scheduling algorithm.
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct {
    int processId,arrivalTime,burstTime,completionTime,waitingTime, turnAroundTime;
} process;

int compare(const void* a, const void* b){
    process *p = (process*) a;
    process *q = (process*) b;
    if(p->arrivalTime != q->arrivalTime) return (p->arrivalTime - q->arrivalTime);
}

int comparator(const void* a, const void* b){
    process *p = (process*) a;
    process *q = (process*) b;
    if(p->burstTime != q->burstTime) return (p->burstTime - q->burstTime);
    else return (p->processId - q->processId);
}

int main(){
    int numberOfProcesses;
    double averageWaitingTime = 0, averageTurnAroundTime = 0;
    printf("Please enter the number of Processes: \n");
    scanf("%d", &numberOfProcesses);
    process processes[numberOfProcesses];
    char choice;
    printf("(a)All arriving at Time 0\n(b)All arrive at different time\nPlease Enter your choice: \n");
    scanf(" %c", &choice);
    for(int i = 0; i < numberOfProcesses;i++){
        printf("Please Enter the process id, arrival time and burst time of the Process %d: \n", i+1);
        scanf(" %d %d %d", &processes[i].processId, &processes[i].arrivalTime, &processes[i].burstTime);
    }
    qsort((void*) processes,numberOfProcesses, sizeof(processes[0]),compare);
    if(choice == 'a'){
        processes[0].completionTime = processes[0].burstTime;
        for(int i = 1; i < numberOfProcesses;i++){
            processes[i].completionTime = (processes[i-1].completionTime + processes[i].burstTime);
        }
        for(int i = 0; i < numberOfProcesses;i++){
            processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime);
            averageTurnAroundTime += processes[i].turnAroundTime;
        }
        for(int i = 0; i < numberOfProcesses;i++){
            processes[i].waitingTime = (processes[i].turnAroundTime - processes[i].burstTime);
            averageWaitingTime += processes[i].waitingTime;
        }
        averageTurnAroundTime /= numberOfProcesses;
        averageWaitingTime /= numberOfProcesses;
        printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \n");
        for(int i = 0; i < numberOfProcesses;i++){
            printf("%d \t %d \t %d \t %d \t %d \t %d \n", processes[i].processId,processes[i].arrivalTime,processes[i].burstTime,processes[i].completionTime,processes[i].waitingTime,processes[i].turnAroundTime);
            printf("The average Waiting Time is %lf \n", averageWaitingTime);
            printf("The average Turn Around Time is %lf \n", averageTurnAroundTime);
        }
    }
    else if(choice == 'b'){
        bool visited[numberOfProcesses];
        for(int i = 0; i < numberOfProcesses;i++) visited[i] = false;
        processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
        visited[0] = false;
        int counter = 0, i =1,index = 0,j,done =1,l;
        bool flag = false;
        while(done < numberOfProcesses){
            if(flag == false) l = processes[index].completionTime;
            counter = 0;
            while(i < numberOfProcesses && processes[i].arrivalTime <= l){
                if(visited[i] == false){
                    counter++;
                }
                i++;
            }
            process temp[counter];
            i = 1, j = 0;
            while(i < numberOfProcesses && processes[i].arrivalTime <= l){
                if(visited[i] == false){
                    temp[j] = processes[i];
                    j++;
                }
                i++;
            }
            qsort((void*) temp,counter, sizeof(temp[0]),comparator);
            int k = 0;
            while(k < numberOfProcesses){
                if(temp[0].processId == processes[k].processId){
                    visited[k] = true;
                    processes[k].completionTime = (l + processes[k].burstTime);
                    done++;
                    index = k;
                    flag = false;
                    break;
                }
                k++;
            }
            i = 1;
            if(l == processes[index].completionTime){
                l++;
                flag = true;
            }
        }
        for(int i = 0; i < numberOfProcesses;i++){
            processes[i].turnAroundTime = (processes[i].completionTime - processes[i].arrivalTime);
            averageTurnAroundTime += processes[i].turnAroundTime;
        }
        for(int i = 0; i < numberOfProcesses;i++){
            processes[i].waitingTime = (processes[i].turnAroundTime - processes[i].burstTime);
            averageWaitingTime += processes[i].waitingTime;
        }
        averageTurnAroundTime /= numberOfProcesses;
        averageWaitingTime /= numberOfProcesses;
        printf("Process ID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time \n");
        for(int i = 0; i <numberOfProcesses;i++){
            printf("%d \t %d \t %d \t %d \t %d \t %d \n", processes[i].processId,processes[i].arrivalTime,processes[i].burstTime,processes[i].completionTime,processes[i].waitingTime,processes[i].turnAroundTime);
        }
        printf("The average Waiting Time is %lf \n", averageWaitingTime);
        printf("The average Turn Around Time is %lf \n", averageTurnAroundTime);
    }
    else{
        printf("You've entered the wrong choice. Try again\n");
    }
    return 0;
}


