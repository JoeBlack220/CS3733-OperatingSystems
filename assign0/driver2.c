#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myio.h"

int main(int argc, char *argv[]){
  /* checks for number of arguments to be correct and ends if not */
    if(argc != 3) {
        printf("Usage ./%s <infile> <outfile>\n", argv[0]);
        exit(-1);
    }
    /*declares files and opens them*/
    FILE *inFILE, *outFile;

    inFILE = fopen(argv[1], "r");
    if (inFILE == NULL){
      printf("Unable to open %s\n", argv[1]);
      exit(1);
    }
    outFile = fopen(argv[2], "w");
    if (outFile == NULL){
      printf("Unable to open %s\n", argv[2]);
      exit(1);
    }
    /*declares variables*/
    char *data;
    char *newData;
    newData = (char *)malloc(1024 * sizeof(char));
    int i;
    int index = 0;

    while(1){
        data = ReadLineFile(inFILE);
        for(i = 0; i < strlen(data); i++){
          /*adds all chars into array except ' '*/
            if(data[i] != ' '){
                newData[index] = data[i];
                index++;
            }
            /*adds only ' '*/
            if(data[i] == ' ' && data[i-1] != ' '){
                newData[index] = ' ';
                index++;
            }
        }
        newData[index] = '\n';
        index++;
        if(feof(inFILE)){
            break;
        }
    }
    /*print chars into file*/
    for(i = 0; i < index; i++){
        fprintf(outFile,"%c", newData[i]);
    }
    /*close files used */
    fclose(inFILE);
    fclose(outFile);
}
