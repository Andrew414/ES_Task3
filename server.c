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
#include "file_read.h"
#include "file_sender.h"

typedef struct socketaddress_in SOCKET_ADDRESS, *PSOCKET_ADDRESS;
typedef struct my_message MESSAGE, *PMESSAGE;
typedef struct file_content FILE_CONTENT, *PFILE_CONTENT;

int main(int argc, char *argv[])
{
  if(argc != 2) {
		printf("Enter the command line parameter with file name.\n");
		return 1;
	}
	file_content info = read_file(argv[1]); 
	printf("%s\n", info.content);
	// Defining and initializing socket
	int sock = 0, connfd = 0;
	socketaddress_in server_address; 

	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server_address, 0, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(5000); 

	// Bind socket to address
	bind(sock, (SOCKET_ADDRESS*)&server_address, sizeof(server_address)); 

	int i = 5;
	// Starting server
	while(i--) {
		// Start listening socket
		listen(sock, 10);

		//Initializing data for starting sending file in the separate thread
		my_message mes;
		mes.file = info.content;
		mes.size = info.size;

		// Accepting connection and getting connection identifier
		mes.index = accept(sock, (SOCKET_ADDRESS*)NULL, NULL); 
		pthread_t thread;
		pthread_create(&thread, NULL, send_file_to_client, (void*)&mes);
	}


	close(sock);
	free(info.content);
	return 0;
}
