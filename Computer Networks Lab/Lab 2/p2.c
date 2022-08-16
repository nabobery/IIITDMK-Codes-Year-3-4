// This program is done by CS20B1044 Avinash R Changrani
/* A menu driven program to implement CRC with following options :
1. Send message:
    You need to take <Data bits> from user. Then, perform LRC and display the output as <Data bits>+<LRC code bits>
2. Receive message:
    You need to take input as <Data bits>+<LRC code bits> from user. Then, perform LRC and display <Data bits> and detection message (Accept/Reject)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	char choice = '0';
	while(choice !='q'){
		printf("Menu\na)Send Message\nb)Receive Message\nq)Exit\n");
		scanf(" %c", &choice);
		if(choice == 'a'){
			int n;
				printf("Please enter the number of bits of the message(databits): \n");
				scanf("%d", &n);
				if(n%4 == 0){
					char dataBits[n];
					printf("Please enter the data bits of the message: \n");	
					for(int i = 0; i < n;i++){
						scanf(" %c", &dataBits[i]);
					}
					char LRC[4];
					for(int i = 0; i < 4;i++){
						int sum = 0;
						for(int j = i; j < n;j += 4){
							if(dataBits[j] == '1') sum++;
						}
						if(sum % 2 == 0) LRC[i] = '0';
						else LRC[i] = '1'; 
					}
					printf("The resultant message is: \n");
					for(int i = 0; i < n;i++){
						printf("%c", dataBits[i]);
					}
					for(int i = 0; i < 4;i++){
						printf("%c", LRC[i]);
					}
					printf("\n");
				}	
				else{
					printf("Please enter a multiple of 4 as number of bits \n");
				}
		}
		else if (choice == 'b'){
			int n;
			printf("Please enter the number of bits of the message (LRC + databits): \n");
			scanf("%d", &n);
			if(n%4 == 0){
				printf("Please enter the data bits of the message: \n");
				char result[n];
				for(int i = 0; i < n;i++){
					scanf(" %c", &result[i]);
				}
				bool flag = false;
				for(int i = 0; i < 4;i++){
					int sum = 0;
					for(int j = i; j < (n - 4);j += 4){
						if(result[j] == '1') sum++;
					}
					if(sum % 2 == 0){
						if(result[n-4+i] == '0') continue;
						else{
							flag = true;
							break;
						}
					}
					else{
						if(result[n-4+i] == '1') continue;
						else{
							flag = true;
							break;
						}
					}
				}
				if(!flag) printf("The Given Data is not corrupted (Accepted) \n");
				else printf("The Given Data is corrupted (Rejected) \n");
			}	
			else{
				printf("Please enter a multiple of 4 as number of bits \n");
			}
		}
		else if(choice == 'q'){
			printf("Exiting the program.... \n");
			exit(0);
		}
        else{
            printf("Enter a proper choice and try again\n");
        }
	}
	return 0;
}