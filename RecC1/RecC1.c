#include <stdio.h>
#include <stdlib.h>

typedef struct PCB {
  int ProcId;
  int ProcPR;
  int CPUburst;
  int Reg[8];
  int queueEnterClock;
  int waitingTime;
   /* other info */
  struct PCB *next;
} PCB;

void printList(PCB *Head, PCB *Tail);
void FIFO_Scheduling(PCB *Head, PCB *Tail);

int main(int argc, char const *argv[]) {
  int CPUreg[8] = {0};
  struct PCB *Head=NULL;
  struct PCB *Tail=NULL;
  int flag = 0;
  int tempProcID = 0;
  int tempProcPR = 0;
  int tempCPUburst = 0;
  if (argc != 5) {
    printf("ERROR: Number of argument is %d. It should be 4.\n Ussage is ./program (0-4) (FIFO) (output file) (input file)\n Ending program now!\n",argc -1);
    return(1);
  }

  printf("Student Name: Juan C. Ruiz\nInput File Name: %s\nCPU Scheduling Alg: %s\n\n",argv[4],argv[2]);

  FILE *inFile;
  if ((inFile = fopen(argv[4],"r")) == NULL) {
    printf("Unable to open %s\n", argv[2]);
    exit(1);
  }

  while (fscanf(inFile,"%d %d %d",&tempProcID, &tempProcPR,&tempCPUburst ) != EOF) {
    if(flag == 0){
      struct PCB *temp = (PCB*) malloc(sizeof(PCB));
      temp->ProcId = tempProcID;
      temp->ProcPR = tempProcPR;
      temp->CPUburst = tempCPUburst;
      temp->queueEnterClock =0;
      temp->waitingTime = 0;
      temp->next = NULL;
      int i;
      for (i = 0; i < 9; i++) {
        temp->Reg[i] = tempProcID;
      }
      Head = temp;
      Tail = temp;
      flag = 1;
    }else{
      struct PCB *cursor = Head;
      while(cursor->next != NULL)
        cursor = cursor->next;
      struct PCB *temp = (PCB*) malloc(sizeof(PCB));
      int tempints = 0;
      temp->ProcId = tempProcID;
      temp->ProcPR = tempProcPR;
      temp->CPUburst = tempCPUburst;
      temp->waitingTime = 0;
      temp->queueEnterClock = 0;
      temp->next = NULL;
      int i;
      for (i = 0; i < 9; i++) {
        temp->Reg[i] = tempProcID;
      }
      Tail = temp;
      cursor->next = temp;
    }
  }
  fclose(inFile);
  struct PCB *cursor = Head;
  while(cursor->next != NULL){
    cursor->queueEnterClock = 0;
    cursor = cursor->next;
  }
  Tail->queueEnterClock = 0;

  //printList(Head,Tail);
  FIFO_Scheduling(Head, Tail);

  return 0;
}

void FIFO_Scheduling(PCB *Head, PCB *Tail){
  int CLOCK=0;
  int Total_waiting_time=0;
  int Total_turnaround_time=0;
  int Total_job=0;
  int count = 0;
  struct PCB *PCB = Head;
  while(PCB->next != NULL){
    count++;
    PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
    Total_waiting_time = Total_waiting_time + PCB->waitingTime ;
    CLOCK = CLOCK + PCB->CPUburst;
    Total_turnaround_time = Total_turnaround_time + CLOCK;
    Total_job = Total_job + 1;
    printf("Process %d is completed at %d ms\n", count,CLOCK);
    PCB = PCB->next;
  }
  count++;
  Tail->waitingTime = Tail->waitingTime + CLOCK - Tail->queueEnterClock;
  Total_waiting_time = Total_waiting_time + Tail->waitingTime ;
  CLOCK = CLOCK + Tail->CPUburst;
  Total_turnaround_time = Total_turnaround_time + CLOCK;
  Total_job = Total_job + 1;
  printf("Process %d is completed at %d ms\n", count,CLOCK);

  printf("Average Waiting time = %.2f ms      (%d/%d)\nAverage Turnaround time = %.2f ms  (%d/%d)\nThroughput = %.2f jobs per ms       (%d/%d)\n",(double) Total_waiting_time / Total_job,Total_waiting_time,Total_job, (double) Total_turnaround_time/Total_job,Total_turnaround_time,Total_job,(double) Total_job / CLOCK,Total_job,CLOCK);
}
void printList(PCB *Head, PCB *Tail){
  struct PCB *cursor = Head;
  while(cursor->next != NULL){
  printf("%d=%d=%d=%d=%d\n", cursor->ProcId,cursor->ProcPR,cursor->CPUburst,cursor->queueEnterClock,cursor->waitingTime);
  cursor = cursor->next;
  }
  printf("%d=%d=%d=%d=%d\n", Tail->ProcId,Tail->ProcPR,Tail->CPUburst,Tail->queueEnterClock,Tail->waitingTime);
}
