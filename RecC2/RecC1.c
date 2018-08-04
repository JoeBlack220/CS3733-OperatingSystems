#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void SJF_Scheduling(PCB *Head, PCB *Tail);
void PR_Scheduling(PCB *Head, PCB *Tail);
void RR_Scheduling(PCB *Head, PCB *Tail, int quantum);
void contextSwitching(PCB *Head);

int main(int argc, char const *argv[]) {
  struct PCB *Head=NULL;
  struct PCB *Tail=NULL;
  int flag = 0;
  int tempProcID = 0;
  int tempProcPR = 0;
  int tempCPUburst = 0;
  if (argc < 5) {
    printf("ERROR: Number of argument is %d. It should be 4. Usage: -alg [FIFO|SJF|PR|RR] [-quantum [integer(ms)]] -input [input_file_name.txt]\nEnding program now!\n",argc -1);
    return(1);
  }

  printf("Student Name: Juan C. Ruiz\nInput File Name: %s\nCPU Scheduling Alg: %s\n\n",argv[argc-1],argv[2]);

  FILE *inFile;
  if ((inFile = fopen(argv[argc-1],"r")) == NULL) {
    printf("Unable to open %s\n", argv[argc-1]);
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

  if(strcmp("FIFO", argv[2]) == 0)
              FIFO_Scheduling(Head, Tail);
  if(strcmp("SJF", argv[2]) == 0)
              SJF_Scheduling(Head, Tail);
  if(strcmp("PR", argv[2]) == 0)
              PR_Scheduling(Head, Tail);
  if(strcmp("RR", argv[2]) == 0 && strcmp("-quantum", argv[3]) == 0 && atoi(argv[4]) != 0)
              RR_Scheduling(Head, Tail, atoi(argv[4]));
  return 0;
}

void FIFO_Scheduling(PCB *Head, PCB *Tail){
  int CLOCK=0;
  int Total_waiting_time=0;
  int Total_turnaround_time=0;
  int Total_job=0;
  int count = 0;
  struct PCB *PCB = Head;
  struct PCB *temp;
  //contextSwitching(PCB);
  while(PCB->next != NULL){
    count++;
    PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
    Total_waiting_time = Total_waiting_time + PCB->waitingTime ;
    CLOCK = CLOCK + PCB->CPUburst;
    Total_turnaround_time = Total_turnaround_time + CLOCK;
    Total_job = Total_job + 1;
    printf("Process %d is completed at %d ms\n", PCB->ProcId,CLOCK);
    temp = PCB;
    free(PCB);
    PCB = temp->next;

  }
  count++;
  Tail->waitingTime = Tail->waitingTime + CLOCK - Tail->queueEnterClock;
  Total_waiting_time = Total_waiting_time + Tail->waitingTime ;
  CLOCK = CLOCK + Tail->CPUburst;
  Total_turnaround_time = Total_turnaround_time + CLOCK;
  Total_job = Total_job + 1;
  printf("Process %d is completed at %d ms\n", Tail->ProcId,CLOCK);

  printf("Average Waiting time = %.2f ms      (%d/%d)\nAverage Turnaround time = %.2f ms  (%d/%d)\nThroughput = %.2f jobs per ms       (%d/%d)\n\n",(double) Total_waiting_time / Total_job,Total_waiting_time,Total_job, (double) Total_turnaround_time/Total_job,Total_turnaround_time,Total_job,(double) Total_job / CLOCK,Total_job,CLOCK);
}

void SJF_Scheduling(PCB *Head, PCB *Tail){
  int CLOCK=0;
  int Total_waiting_time=0;
  int Total_turnaround_time=0;
  int Total_job=0;
  int count = 0;
  //TEMP
  int temp_CPUburst = 0;
  int temp_ProcId = 0;
  struct PCB *PCB_H = Head;
  struct PCB *PCB_T = Tail;
  struct PCB *PCB_P;
  PCB_T->next = PCB_H;
  // contextSwitching(PCB_H);
  while(PCB_H->next != NULL){
    if(temp_CPUburst == 0){
    temp_CPUburst = PCB_H->CPUburst;
    temp_ProcId = PCB_H->ProcId;
    } else {
      if(PCB_H->CPUburst < temp_CPUburst){
        temp_CPUburst = PCB_H->CPUburst;
        temp_ProcId = PCB_H->ProcId;
      } else
       if(PCB_H->CPUburst == temp_CPUburst && PCB_H->ProcId == temp_ProcId){ //Reached the same node
        count++;
        PCB_H->waitingTime = PCB_H->waitingTime + CLOCK - PCB_H->queueEnterClock;
        Total_waiting_time = Total_waiting_time + PCB_H->waitingTime ;
        CLOCK = CLOCK + PCB_H->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        printf("Process %d is completed at %d ms\n", PCB_H->ProcId,CLOCK);
        PCB_P->next = PCB_H->next;
        temp_CPUburst = 0;
        temp_ProcId = 0;
        if (PCB_P->next->ProcId == PCB_H->ProcId) {
          break;
        }
      }
    }
    PCB_P = PCB_H;
    PCB_H = PCB_H->next;
  }
  printf("Average Waiting time = %.2f ms      (%d/%d)\nAverage Turnaround time = %.2f ms  (%d/%d)\nThroughput = %.2f jobs per ms       (%d/%d)\n\n",
    (double) Total_waiting_time / Total_job,Total_waiting_time,Total_job, (double) Total_turnaround_time/Total_job,Total_turnaround_time,Total_job,
    (double) Total_job / CLOCK,Total_job,CLOCK);
}

void PR_Scheduling(PCB *Head, PCB *Tail){
  int CLOCK=0;
  int Total_waiting_time=0;
  int Total_turnaround_time=0;
  int Total_job=0;
  int count = 0;
  //TEMP
  int temp_CPUburst = 0;
  int temp_ProcId = 0;
  struct PCB *PCB_H = Head;
  struct PCB *PCB_T = Tail;
  struct PCB *PCB_P = Tail;
  PCB_T->next = PCB_H;
  // contextSwitching(PCB_H);
  while(PCB_H->next != NULL){
    if(temp_CPUburst == 0){
    temp_CPUburst = PCB_H->CPUburst;
    temp_ProcId = PCB_H->ProcId;
    } else {
      if(PCB_H->CPUburst > temp_CPUburst){
        temp_CPUburst = PCB_H->CPUburst;
        temp_ProcId = PCB_H->ProcId;
      } else
       if(PCB_H->CPUburst == temp_CPUburst && PCB_H->ProcId == temp_ProcId){ //Reached the same node
        count++;
        PCB_H->waitingTime = PCB_H->waitingTime + CLOCK - PCB_H->queueEnterClock;
        Total_waiting_time = Total_waiting_time + PCB_H->waitingTime ;
        CLOCK = CLOCK + PCB_H->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        printf("Process %d is completed at %d ms\n", PCB_H->ProcId,CLOCK);
        PCB_P->next = PCB_H->next;
        temp_CPUburst = 0;
        temp_ProcId = 0;
        if (PCB_P->next->ProcId == PCB_H->ProcId) {
          break;
        }
      }
    }
    PCB_P = PCB_H;
    PCB_H = PCB_H->next;
  }
  printf("Average Waiting time = %.2f ms      (%d/%d)\nAverage Turnaround time = %.2f ms  (%d/%d)\nThroughput = %.2f jobs per ms       (%d/%d)\n\n",
    (double) Total_waiting_time / Total_job,Total_waiting_time,Total_job, (double) Total_turnaround_time/Total_job,Total_turnaround_time,Total_job,
    (double) Total_job / CLOCK,Total_job,CLOCK);
}

void RR_Scheduling(PCB *Head, PCB *Tail, int quantum){
  int CLOCK=0;
  int Total_waiting_time=0;
  int Total_turnaround_time=0;
  int Total_job=0;
  int count = 0;
  struct PCB *PCB = Head;
  struct PCB *PCB_T = Tail;
  struct PCB *temp;
  //contextSwitching(PCB);
  while(PCB->next != NULL){
    if (PCB->CPUburst <= quantum) {
      count++;
      PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
      Total_waiting_time = Total_waiting_time + PCB->waitingTime ;
      CLOCK = CLOCK + PCB->CPUburst;
      Total_turnaround_time = Total_turnaround_time + CLOCK;
      Total_job = Total_job + 1;
      printf("Process %d is completed at %d ms\n", PCB->ProcId,CLOCK);
      temp = PCB;
      free(PCB);
      PCB = temp->next;
    }else{
      PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
      CLOCK = CLOCK + quantum;
      PCB->CPUburst = PCB->CPUburst - quantum;
      PCB->queueEnterClock = CLOCK;
      temp = PCB;
      free(PCB);
      PCB = temp->next;
      temp->next = NULL;
      PCB_T->next = temp;
      PCB_T = temp;

    }


  }
  count++;
  PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
  Total_waiting_time = Total_waiting_time + PCB->waitingTime ;
  CLOCK = CLOCK + PCB->CPUburst;
  Total_turnaround_time = Total_turnaround_time + CLOCK;
  Total_job = Total_job + 1;
  printf("Process %d is completed at %d ms\n", PCB->ProcId,CLOCK);

  printf("Average Waiting time = %.2f ms      (%d/%d)\nAverage Turnaround time = %.2f ms  (%d/%d)\nThroughput = %.2f jobs per ms       (%d/%d)\n\n",(double) Total_waiting_time / Total_job,Total_waiting_time,Total_job, (double) Total_turnaround_time/Total_job,Total_turnaround_time,Total_job,(double) Total_job / CLOCK,Total_job,CLOCK);

}

void contextSwitching(PCB *Head){
  struct PCB *cursor = Head;
  int CPUreg[8] = {0};
  int count = 0;
  while(cursor->next != NULL){
    CPUreg[count] = cursor->Reg[count]+1;
    cursor->Reg[count] = CPUreg[count];
    cursor = cursor->next;
  }
  free(cursor);
}

void printList(PCB *Head, PCB *Tail){
  struct PCB *cursor = Head;
  while(cursor->next != NULL){
  printf("%d=%d=%d=%d=%d\n", cursor->ProcId,cursor->ProcPR,cursor->CPUburst,cursor->queueEnterClock,cursor->waitingTime);
  cursor = cursor->next;
  }
  printf("%d=%d=%d=%d=%d\n", Tail->ProcId,Tail->ProcPR,Tail->CPUburst,Tail->queueEnterClock,Tail->waitingTime);
}
