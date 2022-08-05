// This program is done by CS20B1044 Avinash R Changrani
// Take input.c as input to remove redundant spaces, lines, and comments from it and write it into the output.c file.

#include <stdio.h>
#include <stdbool.h>

int main(int args, char* argv[]){
	FILE *fptr, *fp;
	fptr = fopen(argv[1],"r");
    //fp = fopen("/home/l209/Desktop/result.c", "w");
    char c;
    bool redundantSpaces = false, redundantLines = false, newLine = true, charEncountered = false, singleComment = false, multiComment = false;
	for(c = getc(fptr); c != EOF; c = getc(fptr)){
        if(c == '/'){
            c = getc(fptr);
            if(c == '/') singleComment = true;
            else if(c == '*') multiComment = true;
        }
        if(singleComment){
            while(c != '\n'){
                c = getc(fptr);
            }
            singleComment = false;
        }
        else if(multiComment){
            char prev = c;
            c = fgetc(fptr);
            while(true){
                if(prev == '*' && c == '/') break;
                c = getc(fptr);
            }
            c = getc(fptr);
            multiComment = false;
            redundantLines = false;
        }
        else{
            if(c != ' ' && c != '\n'){
                charEncountered = true;
                newLine = false;
                redundantSpaces = false;
            }
            if(c != '\n'){
                redundantLines = false;
                if(c != ' ') printf("%c",c);
                else{
                    if(newLine){
                        printf("%c",c);
                    }
                    else{
                        if(!redundantSpaces){
                            redundantSpaces = true;
                            printf("%c",c);
                        }
                    }
                }
                //printf("%c",c);
            }
            if(c == '\n'){
                if(redundantLines) continue;
                else{
                    printf("%c",c);
                    redundantLines = true;
                    //printf("%c",c);
                }
                newLine = true;
            }
        }
	}
	fclose(fptr);
	return 0;
}
