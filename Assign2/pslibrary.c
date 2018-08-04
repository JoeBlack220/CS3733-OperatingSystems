#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pslibrary.h"

#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

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

void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
   int i;                                   /* next string position (time) */
   int state1 = READY;                            /* start with both ready */
   int state2 = READY;
   int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
   int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
   int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
   int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         state1 = RUNNING;
      }
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}

void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
   int i;                                   /* next string position (time) */
   int state1 = READY;                            /* start with both ready */
   int state2 = READY;
   int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
   int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
   int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
   int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         if (cpuLeft1 <= cpuLeft2)
            state1 = RUNNING;
         else
            state2 = RUNNING;
      }
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}

void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2) {
   int i;                                   /* next string position (time) */
   int state1 = READY;                            /* start with both ready */
   int state2 = READY;
   int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
   int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
   int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
   int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         if (cpuLeft1 <= cpuLeft2)
            state1 = RUNNING;
         else
            state2 = RUNNING;
      }
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }
                                                      /* handle preemption */
      else if ( (state1 == READY) && (cpuLeft1 < cpuLeft2)) {
         state2 = READY;
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (cpuLeft2 < cpuLeft1)) {
         state1 = READY;
         state2 = RUNNING;
      }
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                       /* decrement counts */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2) {
   int i;                                   /* next string position (time) */
   int state1 = READY;                            /* start with both ready */
   int state2 = READY;
   int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
   int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
   int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
   int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
   int qleft;                                         /* quantum remaining */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }
                                     /* running process has quantum expire */
      if ((state1 == RUNNING) && (qleft == 0) ) {
         state1 = READY;
         qleft = q;
         if (state2 == READY)
            state2 = RUNNING;
      }
      if ((state2 == RUNNING) && (qleft == 0) ) {
         state2 = READY;
         qleft = q;
         if (state1 == READY)
            state1 = RUNNING;
      }
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         state1 = RUNNING;
         qleft = q;
      }
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
         qleft = q;
      }
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
         qleft = q;
      }
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      qleft--;                   /* OK to decrement even if nothing running */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}
