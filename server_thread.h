#ifndef SERVER_THREAD_H_INCLUDED
#define SERVER_THREAD_H_INCLUDED

typedef struct _message
{
    char * file;
    int size;
    int index;
} MESSAGE, *PMESSAGE;

// Function to send file to client
void send_file_to_client(PMESSAGE message);

#endif // SERVER_THREAD_H_INCLUDED
