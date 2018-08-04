#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myio.h"

int main(int argc, char *argv[]){
    /*declares largest variables*/
    int largest_integer = 0;
    double largest_double = 0.0;
    char *largest_string = (char*) malloc(1024 * sizeof(char));
    /*converts to int*/
    int numInts = atoi(argv[1]);
    int numDoubs = atoi(argv[2]);
    int numStrs = atoi(argv[3]);

    /*Reads and prints the input int numInts times*/
    int x;
    int num;
    for(num = 0; num < numInts; num++){
        printf("please input an int:\n");
        x = ReadInteger();
        if(x > largest_integer){
            largest_integer = x;
        }
    }
    /*Reads and prints the input doubles numdoubs times*/
     double y;
     for(num = 0; num < numDoubs; num++){
        printf("please double an double:\n");
         y = ReadDouble();
         if(y > largest_double){
             largest_double = y;
         }
     }
     /*Reads and prints the input string numstrs times*/
    char *z;
    for(num = 0; num < numStrs; num++){
      printf("please input a string:\n");
        z = ReadLine();
        if(strlen(z) > strlen(largest_string)){
          strcpy(largest_string,z);
            free(z);
        }
    }
    /*prints the end result of largest Values*/
     printf("Largest Integer: %d\n", largest_integer);
     printf("Largest Double: %f\n", largest_double);
     printf("Longest String: %s\n", largest_string);
}
