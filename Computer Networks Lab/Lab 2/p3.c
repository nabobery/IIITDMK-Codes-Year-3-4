// This program is done by CS20B1044 Avinash R Changrani
/* A menu driven program to implement VRC with following options :
1. Send message:
    You need to take <Data bits> from user. Then, perform VRC and display the output as <Data bits>+<VRC code bits>
2. Receive message:
    You need to take input as <Data bits>+<VRC code bits> from user. Then, perform LRC and display <Data bits> and detection message (Accept/Reject)
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
				char VRC[n/4];
				int temp = 0;
				for(int i = 0; i < n;i+=4){
					int sum = 0;
					for(int j = i; j < i+4;j++){
						if(dataBits[j] == '1') sum++;
					}
					if(sum % 2 == 0) VRC[temp] = '0';
					else VRC[temp] = '1'; 
					temp++;
				}
				printf("The resultant message is: \n");
				for(int i = 0; i < n;i++){
					printf("%c", dataBits[i]);
				}
				for(int i = 0; i < n/4;i++){
					printf("%c", VRC[i]);
				}
				printf("\n");
			}	
			else{
				printf("Please enter a multiple of 4 as number of bits \n");
			}
		}
		else if (choice == 'b'){
			int n,v;
			printf("Please enter the number of bits of the message (VRC + databits): \n");
			scanf("%d", &n);
			printf("Please enter the number of VRC bits of the message: \n");
			scanf("%d", &v);
			if((n-v) % 4 != 0) printf("Something is wrong about the size of data bits. Please try again\n");
			else{
				printf("Please enter the data bits of the message: \n");
				char result[n-v];
				char vrc[v];
				for(int i = 0; i < n-v;i++){
					scanf(" %c", &result[i]);
				}
				for(int i = 0; i < v;i++){
					scanf(" %c", &vrc[i]);
				}
				bool flag = false;	
				int temp = 0;
				for(int i = 0; i < n-v;i+=4){
					int sum = 0;
					for(int j = i; j < i+4;j++){
						if(result[j] == '1') sum++;
					}
					if(sum % 2 == 0){
						if(vrc[temp] == '0') continue;
						else{
							flag = true;
							break;
						}
					}
					else{
						if(vrc[temp] == '1') continue;
						else{
							flag = true;
							break;
						}
					}
					temp++;
				}
				if(!flag) printf("The Given Data is not corrupted (Accepted) \n");
				else printf("The Given Data is corrupted (Rejected) \n");
			}	
		}
		else if(choice == 'q'){
			printf("Exiting the program....\n");
			exit(0);
		}
		else{
            printf("Enter a proper choice and try again\n");
        }
	}
	return 0;
}
