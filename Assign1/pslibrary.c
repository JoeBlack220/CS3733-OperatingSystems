#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pslibrary.h"
void part0(char *s1, char *s2){
  strcpy(s1,"RRwwwwwRRRRRRRRR");
  strcpy(s2,"rrRRRRwwwwwwwwrrRRRRRRR");
}

void display(char *heading, char *s1, char *s2){
  int i;
  int sizeOfLongerString;
  int numberOfrInString1 = 0;
  int numberOfrInString2 = 0;
  int numberOfRInString1 = 0;
  int numberOfRInString2 = 0;
  double avgr = 0;
  double avgRbyLongestString = 0;
  if (strlen(s1) > strlen(s2)) {
    sizeOfLongerString = strlen(s1);
  }else{
    if (strlen(s2)>strlen(s1)) {
      sizeOfLongerString = strlen(s2);
    }else{
      sizeOfLongerString = strlen(s1);
    }
  }
  printf("\n%s%s\n%s\n", heading,s1,s2);
  for (i = 0; i < strlen(s1); i++) {
    if (s1[i] == 'r') {
      numberOfrInString1++;
    }
    if (s1[i] == 'R') {
      numberOfRInString1++;
    }
  }
  for (i = 0; i < strlen(s2); i++) {
    if (s2[i] == 'r') {
      numberOfrInString2++;
    }
    if (s2[i] == 'R') {
      numberOfRInString2++;
    }
  }
  avgr = (double)(numberOfrInString1 + numberOfrInString2) / 2;
  avgRbyLongestString = (double)(numberOfRInString2 + numberOfRInString1) / sizeOfLongerString;
  printf("%d %d %.1f %.5f\n", numberOfrInString1,numberOfrInString2,avgr,avgRbyLongestString);
}

void fcfsa(char *s1,char *s2,int x1,int y1,int z1,int x2,int y2,int z2){
  int i;
  int counter1 = 0;
  int counter2 = 0;
  //making of string 1
  for (i = 0; i < x1; i++) {
    s1[counter1] = 'R';
    counter1++;
  }
  for (i = 0; i < y1; i++) {
    s1[counter1] = 'w';
    counter1++;
  }
  for (i = 0; i < z1; i++) {
    s1[counter1] = 'R';
    counter1++;
  }
  s1[counter1] = '\0';
  //making of string 2
  for (i = 0; i < x1; i++) {
    s2[counter2] = 'r';
    counter2++;
  }
  for (i = 0; i < x2; i++) {
    s2[counter2] = 'R';
    counter2++;
  }
  for (i = 0; i < y2; i++) {
    s2[counter2] = 'w';
    counter2++;
  }
  for (i = 0; i < z2; i++) {
    s2[counter2] = 'R';
    counter2++;
  }
  s2[counter2] = '\0';
      for(i = 0; i < counter2; i++){
                    if((s2[i] == 'R' && s1[i] == 'R') && (s2[i-1] == 'w' || s2[i-1] == 'r')){
                            //shift s2 to the right by 1
                            int n;
                            for(n = counter2; n > i; n--){
                                    s2[n] = s2[n-1];
                            }
                            //sub 'r' in where i is
                            s2[i] = 'r';
                    }
            }
       for(i = 0; i < counter1; i++){
               if((s1[i] == 'R' && s2[i] == 'R') && (s1[i-1] == 'w' || s1[i-1] == 'r')){
                       //shift s1 to the right by 1
                       int n;
                       for(n = counter1; n > i; n--){
                               s1[n] = s1[n-1];
                       }
                       //sub 'r' in where i is
                       s1[i] = 'r';
               }
       }
       for(i = 0; i < counter2; i++){
                    if((s2[i] == 'R' && s1[i] == 'R') && (s2[i-1] == 'w' || s2[i-1] == 'r')){
                            //shift s2 to the right by 1
                            int n;
                            for(n = counter2; n > i; n--){
                                    s2[n] = s2[n-1];
                            }
                            //sub 'r' in where i is
                            s2[i] = 'r';
                    }
            }
}
