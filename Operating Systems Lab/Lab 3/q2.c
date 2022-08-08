// This program is done by CS20B1044 Avinash R Changrani
// Implement Priority Based (Pre-emptive) CPU Scheduling algorithm
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int pid,at,bt,ct,wt,tat,pr,tt,rt,ot,it;
} process;

int compare(const void* a, const void* b){
    process *p = (process*) a;
    process *q = (process*) b;
    return (p->at - q->at);
}

int comparator(const void* a, const void* b){
    process *p = (process*) a;
    process *q = (process*) b;
    if(p->pr != q->pr) return (p->pr - q->pr);
    else if(p->at != q->at) return (p->at - q->at);
    else return (p->id - q->id);
}

int main(){
    int n;
    double averageWaitingTime = 0, averageTurnAroundTime = 0;
    printf("Please enter the number of Processes: \n");
    scanf("%d", &n);
    process processes[n];
    char choice;
    printf("(a)All arriving at time 0\n(b)All arrive at different time\nPlease Enter your choice: \n");
    scanf(" %c", &choice);
    for(int i = 0; i < n;i++){
        printf("Please Enter the process id, arrival time, burst time and priority: \n");
        scanf(" %d %d %d %d", &processes[i].pid, &processes[i].at,  &processes[i].bt,  &processes[i].pr);
    }
    if(choice == 'a'){
        qsort((void*) processes,n,sizeof(processes[0]),comparator);
        processes[0].ct = processes[0].bt;
        for(int i = 1; i < n;i++){
            processes[i].ct = (processes[i-1].ct + processes[i].bt);
        }
        for(int i = 0; i < n; i++){
            processes[i].tat = processes[i].ct - processes[i].at;
            averageTurnAroundTime += processes[i].tat;
        }
        for(int i = 0; i < n; i++){
            processes[i].wt = processes[i].tat - processes[i].bt;
            averageWaitingTime += processes[i].wt;
        }
        averageWaitingTime /= n;
        averageTurnAroundTime /= n;
        printf("PID \t Arrival Time \t Burst Time \t Completion Time \t Waiting Time \t Turn Around Time\n");
        for(int i = 0; i < n;i++){
            printf("%d \t %d \t %d \t %d \t %d \t %d \n", processes[i].pid, processes[i].at, processes[i].bt, processes[i].ct, processes[i].wt, processes[i].tat);
        }
        printf("The average Waiting Time is: %d", averageWaitingTime);
        printf("The average Turn Around Time is: %d", averageTurnAroundTime);
    }
    else if(choice == 'b'){
        qsort((void*) processes,n,sizeof(processes[0]),compare);
    }
    else{
        printf("You've entered the wrong choice. Please try again \n");
    }
    return 0;
}


