/* Implement Banker's algorithm. Consider 6 processes and 4 types of resources.
Define the ALLOCATION and  MAX matrix  and the AVAILABLE array. Find the NEED matrix. You must ensure that your  initial allocation will always lead to the system in  safe state. Now, take the input from the user for any process as additional request. Find that this request will lead to safe  or unsafe state.
For eg. P1=(0, 0, 1, 1)
Check whether additional P1 request will lead to safe state or not,
(a) If safe then print "SAFE", sequence of safe processes and update the  ALLOCATION, MAX and NEED Matrix
(b) If unsafe then print "UNSAFE" and discard the request without updating the above matrix.
You can take multiple times the input from the user.*/

// This program is done by CS20B1044 Avinash R Changrani

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// matrix for allocation, max,need,available and for process Sequence
int allocation[6][4], max[6][4], need[6][4], available[4], res[6];

// Checking if the System is in Safe State using Banker's Algorithm
bool isSafe()
{
    bool f[6];
    int p = 0;
    for (int i = 0; i < 6; i++)
    {
        f[i] = false;
    }
    for (int k = 0; k < 7; k++)
    {
        for (int i = 0; i < 6; i++)
        {
            // if execution of process not done
            if (f[i] == 0)
            {
                bool b = false;
                for (int j = 0; j < 4; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        b = true;
                        break;
                    }
                }
                // if process can be done with the available resources
                if (b == false)
                {
                    res[p++] = i + 1;
                    for (int y = 0; y < 4; y++)
                        available[y] += allocation[i][y];
                    f[i] = true;
                }
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < 6; i++)
    {
        // if not even one process gets done with the available resources, its unsafe
        if (f[i] == false)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

// function to print the Matrices for the Processes
void printMatrix()
{
    printf("Process \t\t Allocation \t\t     Max \t\t      Need \n");
    printf("\t\t\t R1 R2 R3 R4 \t\t R1 R2 R3 R4 \t\t R1 R2 R3 R4 \n");
    for (int i = 0; i < 6; i++)
    {
        printf("P%d\t\t\t ", i + 1);
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", allocation[i][j]);
            if (allocation[i][j] < 10)
                printf(" ");
        }
        printf("\t\t ");
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", max[i][j]);
            if (max[i][j] < 10)
                printf(" ");
        }
        printf("\t\t ");
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", need[i][j]);
            if (need[i][j] < 10)
                printf(" ");
        }
        printf("\n");
    }
}

int main()
{
    // get input from user
    for (int i = 0; i < 6; i++)
    {
        printf("Please enter the instances allocated for Processes P%d for R1, R2,R3 and R4: ", i + 1);
        scanf("%d %d %d %d", &allocation[i][0], &allocation[i][1], &allocation[i][2], &allocation[i][3]);
    }
    for (int i = 0; i < 6; i++)
    {
        printf("Please enter the maximum demand of resources for Processes P%d for R1, R2,R3 and R4: ", i + 1);
        scanf("%d %d %d %d", &max[i][0], &max[i][1], &max[i][2], &max[i][3]);
    }
    printf("Please Enter the number of available instances for Resources R1, R2, R3 and R4: ");
    scanf("%d %d %d %d", &available[0], &available[1], &available[2], &available[3]);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    printMatrix();
    int process, r[4];
    while (1)
    {
        char choice;
        printf("a) Check if request by process can be granted b) Exit \n");
        // take request from user
        scanf(" %c", &choice);
        if (choice == 'a')
        {
            printf("Please enter the process id for which you have a request: ");
            scanf("%d", &process);
            // Invalid Process ID
            if (process < 1 && process > 6)
            {
                printf("Wrong Process Entered. Please try again!\n");
                continue;
            }
            printf("Please enter the requested resources for the Given Process: ");
            scanf("%d %d %d %d", &r[0], &r[1], &r[2], &r[3]);
            int temp_allocation[6][4], temp_need[6][4], temp_available[4];
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    temp_allocation[i][j] = allocation[i][j];
                    temp_need[i][j] = need[i][j];
                }
            }
            for (int i = 0; i < 4; i++)
                temp_available[i] = available[i];
            for (int j = 0; j < 4; j++)
            {
                allocation[process - 1][j] += r[j];
                need[process - 1][j] -= r[j];
                available[j] -= r[j];
            }
            // if the state is safe after allocation
            if (isSafe() == true)
            {
                printf("We can grant the reuqest to the Process as the Process is in the safe sequence: ");
                for (int i = 0; i < 6; i++)
                {
                    if (i < 5)
                        printf("P%d-> ", res[i]);
                    else
                        printf("P%d \n", res[i]);
                }
                printf("REQUEST GRANTED\n");
                for (int i = 0; i < 4; i++)
                    available[i] = temp_available[i] - r[i];
            }
            // if it's unsafe, reject the request
            else
            {
                printf("Granting the Request to the Process is leading the system to UNSAFE State!!!!\n");
                printf("REQUEST REJECTED\n");
                for (int i = 0; i < 6; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        allocation[i][j] = temp_allocation[i][j];
                        need[i][j] = temp_need[i][j];
                    }
                }
                for (int i = 0; i < 4; i++)
                    available[i] = temp_available[i];
            }
            printMatrix();
            printf("The available Matrix is : ");
            for (int i = 0; i < 4; i++)
                printf("%d ", available[i]);
            printf("\n");
        }
        else if (choice == 'b')
        {
            printf("Exiting the Program.....\n");
            exit(0);
        }
        else
            printf("Wrong Choice! Please try again!!");
    }
    return 0;
}