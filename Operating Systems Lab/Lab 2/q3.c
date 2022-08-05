// This program is done by CS20B1044 Avinash R Changrani

/* Write a program using file handling functions to copy a file (Input1.txt). Write a program which
converts entire file (obtained after copying) from lower case to upper case and vice versa.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    FILE *fptr, *fp;
    fptr = fopen("Input1.txt", "r");
    fp = fopen("result.txt", "w");
    char c = fgetc(fptr);
    if(islower(c)){
        c = toupper(c);
        fputc(c,fp);
        printf("%c", c);
        while((c=fgetc(fptr))!= EOF){
            c = toupper(c);
            fputc(c,fp);
            printf("%c", c);
        }
    }
    else{
        c = tolower(c);
        fputc(c,fp);
        printf("%c", c);
        while((c=fgetc(fptr))!= EOF){
            c = tolower(c);
            fputc(c,fp);
            printf("%c", c);
        }
    }
    fclose(fptr);
    fclose(fp);
    return 0;
}

