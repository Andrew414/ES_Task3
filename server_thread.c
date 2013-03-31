#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include "server_thread.h"

#define USE_PTHREADS_LUKE

void* send_file_to_client_pthreads(void * pointer)
{

    PMESSAGE message = (PMESSAGE)pointer;

    printf("sending - pthread - entering\n");
	printf("%d \n", message->index);

    write(message->index, message->file, message->size);
    return NULL;
	printf("sending - pthread - leaving\n");
}

void send_file_to_client(PMESSAGE message)
{
#ifdef USE_PTHREADS_LUKE
	printf("sending - entering\n");
	pthread_t thread;
    pthread_create(&thread, NULL, send_file_to_client_pthreads, (void*)message);  
	printf("sending - leaving\n");
#endif
}


void completion_routine()
{
    
}

void init_routine()
{

}
