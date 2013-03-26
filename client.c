#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

typedef struct sockaddr_in sock_addr;

int main(int argc, char * argv[]) 
{
	int sockfd = 0, n = 0;
	char recvBuff[10000] = {0};
	FILE *stream;
	sock_addr server_address = {0}; 

	if(argc != 2) {
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return 1;
	} 

	//allocating memory for received data and creating socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error : Could not create socket \n");
		return 1;
	}

	//configuring address and validating it
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(1234); 

	if(inet_pton(AF_INET, argv[1], &server_address.sin_addr) <= 0) {
		printf("\n Error: wrong address\n");
		return 1;
	} 
/*
	//connecting and handling error
	if( connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
		printf("\n Error : Connect Failed \n");
		return 1;
	} 

	//opening file for writing received data
	//if((stream = freopen("file.in", "w", stdout)) == NULL) {
	//	printf("\n Write error \n");
	//	return 1;
	//}

	//reading data from socket
	while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
		recvBuff[n] = 0;
		if(fputs(recvBuff, stdout) == EOF) {
			printf("\n Error : Fputs error\n");
		}
	} 

	if(n < 0) {
	printf("\n Read error \n");
	} 
*/
	return 0;
}