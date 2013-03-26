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
  write(message->index, message->file, message->size);
    return NULL;
}

void send_file_to_client(PMESSAGE message)
{
#ifdef USE_PTHREADS_LUKE
	pthread_t thread;
    pthread_create(&thread, NULL, send_file_to_client_pthreads, (void*)message);  
#endif
}


void completion_routine()
{
    
}

void init_routine()
{

}
