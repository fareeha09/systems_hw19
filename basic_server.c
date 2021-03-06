#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo){
	if (signo == SIGINT){
		remove("pipe");
		exit(EXIT_SUCCESS);
	}
}

int main() {
	
  signal(SIGINT,sighandler);
  
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  printf("to_client %d, from client %d\n", to_client, from_client);

  
  while(1){

  //gets data from client
  char received[100];
  read(from_client, received, 100);
  printf("[Server]: %s\n", received);
  
  //process data
  char new[100];
  strncpy(new, received, strlen(received)-1);
    
  //send to client
  write(to_client, new, 100);
  }
}
