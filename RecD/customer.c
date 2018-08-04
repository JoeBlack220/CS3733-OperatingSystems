/*
run this after the bank and run with ./(program) (ATM1|ATM2)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int  argc, char const *argv[]) {
  // declare variables
  int ATM;
  char buf[10];
  int number;
  ATM = open(argv[1], O_WRONLY);
  //infinite loop if number is less than 0 then exit the customer
  while(1){
    printf("Enter Deposit: ");
    scanf("%s", buf);
    number = atoi(buf);
    if(number < 0)
    break;
    else
    //write to ATM 
    write(ATM, buf, sizeof(char) * 10);
  }
  close(ATM);
  exit(0);
}
