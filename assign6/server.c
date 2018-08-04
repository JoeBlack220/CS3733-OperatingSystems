/* server.c - code for example server program that uses TCP */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define ACC_NUM 10
struct account {
  char username[20];
  char passwd[10];
  double balance;
};

struct account accounts[ACC_NUM] = {{"pspman","pspman",100},{"kerther","kerther",120},{"champppy","champppy",999},{"weava","weava",123},
{"pspman1","pspman1",100},{"kerther1","kerther1",120},{"champppy1","champppy1",999},{"weava","weava",123},{"pspman2","pspman2",100},{"kerther2","kerther2",120}};

int main(int argc, char *argv[]){
  struct  sockaddr_in sad; /* structure to hold server's address  */
  int     port;            /* protocol port number                */

  struct  sockaddr_in cad; /* structure to hold client's address  */
  int     alen;            /* length of address                   */

  int     welcomeSocket, connectionSocket; /* socket descriptors  */

  char    clientSentence[128];
  char    capitalizedSentence[128];
  char    buff[128];
  char    buff2[128];
  int     i, n, x;
  int flag =0;
  int childpid;

  /* Check command-line argument for protocol port and extract   */
  /* port number if one is specified. Otherwise, give error      */
  if (argc > 1) {                /* if argument specified        */
    port = atoi(argv[1]);        /* convert argument to binary   */
  } else {
    fprintf(stderr,"Usage: %s port-number\n",argv[0]);
    exit(1);
  }

  /* Create a socket */

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0); /* CREATE SOCKET */
  if (welcomeSocket < 0) {
    fprintf(stderr, "socket creation failed\n");
    exit(1);
  }

  /* Bind a local address to the socket */

  memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure   */
  sad.sin_family = AF_INET;           /* set family to Internet     */
  sad.sin_addr.s_addr = INADDR_ANY;   /* set the local IP address   */
  sad.sin_port = htons((u_short)port);/* set the port number        */

  if (bind(welcomeSocket, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
    fprintf(stderr,"bind failed\n");
    exit(1);
  }

  /* Specify the size of request queue */

  if (listen(welcomeSocket, 10) < 0) {
    fprintf(stderr,"listen failed\n");
    exit(1);
  }

  /* Main server loop - accept and handle requests */

  while (1) {
    alen = sizeof(cad);
    if ( (connectionSocket=accept(welcomeSocket, (struct sockaddr *)&cad, &alen)) < 0) {
      fprintf(stderr, "accept failed\n");
      exit(1);
    }

    childpid = fork();

    if (childpid < 0) {
       fprintf(stderr,"Error creating child process\n");
       return 1;
    }

    if (childpid == 0) {                                     /* child code */
      /* Get the sentence from the client */

      clientSentence[0]='\0';
      n=read(connectionSocket,buff,sizeof(buff));
      while(n > 0){
        strncat(clientSentence,buff,n);
        if (buff[n-1]=='\0') break;
        n=read(connectionSocket,buff,sizeof(buff));
      }
      printf("received: %s\n", clientSentence);
      /* Capitalize the sentence */
      for(i=0; i < ACC_NUM; i++){
        if (strcmp(accounts[i].username, clientSentence) == 0) {
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
      write(connectionSocket, "OK", 3);
      }
      else{
        write(connectionSocket, "INVALID", 8);
        close(connectionSocket);
        exit(0);
      }
      clientSentence[0]='\0';
      n=read(connectionSocket,buff,sizeof(buff));
      while(n > 0){
        strncat(clientSentence,buff,n);
        if (buff[n-1]=='\0') break;
        n=read(connectionSocket,buff,sizeof(buff));
      }
      printf("received: %s\n", clientSentence);

      if (strcmp(accounts[i].passwd,clientSentence) == 0) {
        char balancest[12] = "BALANCE IS ";
        sprintf(buff,"%s%.2f",balancest,accounts[i].balance);
        write(connectionSocket, buff, 128);

      }
      else{
        write(connectionSocket, "INVALID", 8);
        close(connectionSocket);
        exit(0);
      }
      /* send it to the client */

      write(connectionSocket, capitalizedSentence, strlen(capitalizedSentence)+1);

      close(connectionSocket);
    }

  }
}
