// Implementation of Go-back-by-N Problem in which there're number of frames, sliding window size and packet
// dropping at multiple of i. We need to find number of frames sent
// This program is done by CS20B1044 Avinash R Changrani
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nf, size, periodicFrameDrop, result = 0, curr = 1;
    printf("Please enter the number of frames to be sent:\n");
    scanf("%d", &nf);
    printf("Please enter the size of window on the sender's side:\n");
    scanf("%d", &size);
    printf("Please enter which packet to drop periodically :\n");
    scanf("%d", &periodicFrameDrop);
    while (curr <= nf)
    {
        if (nf - curr <= size - 1)
        {
            if ((result + 1) % periodicFrameDrop == 0)
            {
                result += nf - curr + 1;
            }
            else
            {
                curr++;
                result++;
            }
        }
        else
        {
            if ((result + 1) % periodicFrameDrop == 0)
            {
                result += size;
            }
            else
            {
                curr++;
                result++;
            }
        }
    }
    printf("The number of frames sent is %d\n", result);
    return 0;
}