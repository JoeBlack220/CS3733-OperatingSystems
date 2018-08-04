#include <sys/types.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myio.h"

int ReadInteger(void){
    char *line;
    int index;
    int nums[1024];
    char temp;
    char next;
    char prev;
    int incomplete = 1;
    int returnValue;
    while(incomplete == 1){
        line = ReadLine();
        index = 0;
        int i;
        for( i = 0; i < strlen(line); i++){
            if(isdigit(line[i])){
                temp = line[i];
                next = line[i+1];
                prev = line[i-1];
                nums[index++] = line[i] - '0';
                if(isdigit(prev) && !isdigit(next) && i != (strlen(line)-1)){
                    printf("character found after digit\n");
                    incomplete = 1;
                    break;
                } else if (i == strlen(line) && isdigit(prev)) {
                    printf("character found after digit\n");
                    incomplete = 1;
                    break;
                } else {
                    incomplete = 0;
                }
            }
        }
    }
    returnValue = 0;
    int i;
    for(i = 0; i < index; i++){
        returnValue = 10 * returnValue + nums[i];
    }
    return returnValue;
}

double ReadDouble(void){
    char *line;
    int wIndex;
    int dIndex;
    int wholeNums[1024];
    int decNums[1024];
    char curr;
    char next;
    char prev;
    int incomplete = 1;
    int decimalFlag = 0;
    double returnValue;
    while(incomplete == 1){
        line = ReadLine();
        wIndex = 0;
        dIndex = 0;
        int i;
        for(i = 0; i < strlen(line); i++){
            if(line[i] == '.' && isdigit(line[i+1])){
                decimalFlag = 1;
                incomplete = 0;
            }
            if(isdigit(line[i])){
                incomplete = 0;
                curr = line[i];
                next = line[i+1];
                prev = line[i-1];
                if(decimalFlag == 0){
                    wholeNums[wIndex] = curr - '0';
                    wIndex++;
                }
                if(decimalFlag == 1){
                    decNums[dIndex] = curr - '0';
                    dIndex++;
                }
                if(isdigit(curr) && (!isdigit(next) && next != '.') && i != (strlen(line)-1)){
                  incomplete = 1;
                  printf("character found after digit\n");
                  break;
                }
            }
        }
    }
    double wValue = 0.0;
    double dValue = 0.0;
    int i;
    for(i = 0; i < wIndex; i++){
        wValue = 10 * wValue + wholeNums[i];
    }
    for(i = dIndex -1; i >= 0; i--){
      dValue =(double) dValue / 10 + decNums[i];
    }
    dValue = dValue / 10;
    returnValue = wValue + dValue;
    return returnValue;
}

char *ReadLine(void){
    /*line is the returning char *tmp is used to add onto line*/
    char *line = (char*) malloc(1024 * sizeof(char));
    char tmp = NULL;
    /* Size of the String */
    size_t size = 0;
    int index = 0;
    /*set char to -1 sowhile loop initiates*/
    int ch = EOF;
    /*
    while loop that grabs char by char until EOF or Enter  */
    while (ch) {
        /*grab char input*/
        ch = getc(stdin);

        /*check char for -1 or Enterif true then exit while loop*/
        if (ch == EOF || ch == '\n'){
            ch = 0;
        }
        line[index] = ch;
        index++;
    }//END WHILE
    return line;
}

char *ReadLineFile(FILE *infile){
  /*line is the returning char *tmp is used to add onto line*/
  char *line = (char*) malloc(1024 * sizeof(char));
  char tmp = NULL;
  /* Size of the String */
  size_t size = 0;
  int index = 0;
  /*set char to -1 sowhile loop initiates*/
  int ch = EOF;
  /*
  while loop that grabs char by char until EOF or Enter  */
  while (ch) {
      /*grab char input*/
      ch = getc(infile);

      /*check char for -1 or Enterif true then exit while loop*/
      if (ch == EOF || ch == '\n'){
          ch = 0;
      }
      line[index] = ch;
      index++;
  }//END WHILE
  return line;
}
