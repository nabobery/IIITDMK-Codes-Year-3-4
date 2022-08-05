// This program is done by CS20B1044 Avinash R Changrani
// Given a file name, Write a C program to take it as an argument and count the number of lines, words, and characters in it.

#include <stdio.h>

int main(int args, char* argv[]){
	FILE *fptr;
	fptr = fopen(argv[1],"r");
	char c, prev = ' ';
	int numberOfLines = 0, numberOfWords = 0, numberOfCharacters = 0;
	for(c = getc(fptr); c != EOF; c = getc(fptr)){
		if(c == '\n'){
			numberOfLines++;
			numberOfWords++;
		}
		if(c == ' '){
            if(prev != ' ' && prev != '\n') numberOfWords++;
        }
		if(c != '\n') numberOfCharacters++;
        prev = c;
	}
	if(numberOfCharacters > 0){
		    numberOfLines++;
            numberOfWords++;
	}
	printf("\nThe number of Lines in the given File is %d \n", numberOfLines);
	printf("The number of words in the given File is %d \n", numberOfWords);
	printf("The number of characters in the given File is %d \n", numberOfCharacters);
	fclose(fptr);
	return 0;
}
