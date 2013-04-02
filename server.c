#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include "server_filereader.h"
#include "server_thread.h"

typedef struct sockaddr_in SOCKET_ADDRESS, *PSOCKET_ADDRESS;
typedef struct sockaddr SOCK_ADDR, *PSOCK_ADDR;

int main(int argc, char *argv[])
{
	int errorCode = 0;
	FILE_CONTENT information;

	int my_socket = 0;
	int connfd = 0;
	SOCKET_ADDRESS server_address; 
	
    if(argc != 2) {
		printf("Enter the command line parameter with file name.\n");
		return 1;
	}
	
	
	information = read_file_content(argv[1], &errorCode); 
	
	if (errorCode!=0){
		printf("Error %d occured while reading file. Terminating...\n", errorCode);
		return 1;
	}
	
	printf("%s\n", information.content);
	// Defining and initializing socket
	

	my_socket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server_address, 0, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(1234); 

	// Bind socket to address
	bind(my_socket, (PSOCK_ADDR)&server_address, sizeof(server_address)); 
	init_routine();
	printf("binded\n");
	
    MESSAGE message = {0};

	// Starting server
	while(1) {
		
		// Start listening socket
		listen(my_socket, 10);
		printf("listening\n");

		//Initializing data for starting sending file in the separate thread
		
		message.file = information.content;
		message.size = information.length;

		// Accepting connection and getting connection identifier
		message.index = accept(my_socket, (PSOCK_ADDR)NULL, NULL); 
		printf("accepted - %d\n", message.index);

        PMESSAGE newMsg = (PMESSAGE) malloc(sizeof(MESSAGE));
        newMsg->file = message.file;
        newMsg->size = message.size;
        newMsg->index = message.index;

		send_file_to_client(newMsg);
		printf("sent\n");
	}
	completion_routine();

	close(my_socket);
	free(information.content);
	return 0;
}
