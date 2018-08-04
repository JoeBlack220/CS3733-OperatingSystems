/*
run this then run client 
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  //declare variables
  int TOTAL = 0;
  int ff1_fd;
  int ff2_fd;
  int n;
  int tmp;
  char buf[10];
  char fifo_name1[] = "ATM1";
  char fifo_name2[] = "ATM2";
  struct timeval timeout;
  fd_set read_fd_set;

  timeout.tv_sec = 30; //30 sec
  timeout.tv_usec = 0;
  // sets set to 0
  FD_ZERO(&read_fd_set);

  //get the file descriptors and if it is not open open it

  if((ff1_fd = open(fifo_name1, O_RDWR)) < 0){
    mkfifo(fifo_name1, 0666);
    ff1_fd = open(fifo_name1, O_RDWR);
  }
  if((ff2_fd = open(fifo_name2, O_RDWR)) < 0){
    mkfifo(fifo_name2, 0666);
    ff2_fd = open(fifo_name2, O_RDWR);
  }
  //add fds to the set
  n = ff2_fd + 1;

  int errC;
  //infinte loop to look into pipes
  while(1) {
    FD_ZERO(&read_fd_set);
    FD_SET(ff1_fd, &read_fd_set);
    FD_SET(ff2_fd, &read_fd_set);

    errC = select(n, &read_fd_set, NULL, NULL, &timeout);

    if(errC == 0){
      printf("%s\n", "Time out");
      break;
    } else if(errC == -1){
      exit(-1);
    }

    if(FD_ISSET(ff1_fd, &read_fd_set)){
      read(ff1_fd, buf, sizeof(buf));
      tmp = atoi(buf);
      TOTAL+=tmp;
    }
    
    else if(FD_ISSET(ff2_fd, &read_fd_set)){
      read(ff2_fd, buf, sizeof(buf));
      tmp = atoi(buf);
      TOTAL+=tmp;
    }
    printf("%d\n", TOTAL);
  }
  //delete the fifos
  unlink(fifo_name1);
  unlink(fifo_name2);
  printf("%s\n", "Bank File complete");
}
