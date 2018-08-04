#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

int main(int argc, char const *argv[]) {
  int i;
  int sum;
  if (argc != 8) {
    printf("ERROR: Number of argument is %d. It should be 7. Ending program now!\n",argc -1);
    return(1);
  }
  printf("Assignment 1 program was written by Juan C. Ruiz\ninputs: ");
  for (i = 1; i < argc; i++) {
    printf("%s ", argv[i]);
    if (i == argc-1) {
      printf("\n");
    }
    if (i >= argc-6) {
      sum += atoi(argv[i]);
    }
  }
  char s1[sum];
  char s2[sum];
  fcfsa(s1,s2,atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]),atoi(argv[6]),atoi(argv[7]));
  //printf("String 1:%s\nString 2:%s\n",s1,s2 );

  char heading[] = "Part 1\n";
  display(heading,s1,s2);
  return 0;
}
