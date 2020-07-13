#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

#define FLAG1 "\nflag1{d8fdbd5986197623ac9658524faabbc3}\n"
#define FLAG2 "\nflag2{7f789cf2e4810ccb705456bcb74022c5}\n"
#define FLAG3 "\nflag3{033423c6617750cd92bdc2f1c3750faf}\n"
#define FLAG4 "\nflag4{5b6af90422c70251bd5833f4baeff263}\n"
#define FLAG5 "\nflag5{b25029a6f008ab89bc8c433b10720c88}\n"
#define FLAG6 "\nflag6{77aa905484838fa1cfc577904ad8cfaf}\n"
#define FLAG7 "\nflag7{1f402a4d1bbf8de16e8a73ef12afa470}\n"
#define FLAG8 "\nflag8{76f38fb4b2eaa6545fba8d281d57eec8}\n"
#define FLAG9 "\nflag9{4f9960f9b58088a6c6c4bd8fa80a4bb5}\n"
#define FLAG10 "\nflag10{deb4a1073ab96334d2b05826bfb90c0d}\n"

int main(){
  
  int sockfd, i=0, result=-1; //Socket file descriptor
  struct sockaddr_in serverAddr; 

  int newSocket;
  struct sockaddr_in newAddr;
  
  socklen_t addr_size;

  char q_arr[10][200] = {
    "\nQuestion1\n",
    "\nQuestion2\n",
    "\nQuestion3\n",
    "\nQuestion4\n",
    "\nQuestion5\n",
    "\nQuestion6\n",
    "\nQuestion7\n",
    "\nQuestion8\n",
    "\nQuestion9\n",
    "\nQuestion10\n"
  };

  char a_arr[10][200] = {
  "1234\n",
  "Answer2\n",
  "Answer3\n",
  "Answer4\n",
  "Answer5\n",
  "Answer6\n",
  "Answer7\n",
  "Answer8\n",
  "Answer9\n",
  "Answer10\n"
  };

  char input[200] = { 0 };

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("\n[+] Socket created succesfully...\n");

  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family=AF_INET;
  serverAddr.sin_port=htons(PORT);
  serverAddr.sin_addr.s_addr=INADDR_ANY;

  bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("\nBound to port number %d.\n", PORT);
  listen(sockfd, 5);

  printf("\nRunning on port: %d...\nListening...\n", PORT);

  newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);	
  
  for(i = 0; i<10; i++){
    send(newSocket, q_arr[i], strlen(q_arr[i]), 0);
    send(newSocket, "\n", 1, 0);
    read(newSocket, input, 200, 0);
    result = strcasecmp(input, a_arr[i]);
    if(result == 0){
    send(newSocket, FLAG1, 10, 0);
    }else{
    send(newSocket, "\nfail\n", 5, 0);
    }
    printf(input);
    memset(input, '\0', 200);
  }

printf("closing...");

return 0;
}


