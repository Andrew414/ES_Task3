#ifndef SERVER_FILEREADER_H_INCLUDED
#define SERVER_FILEREADER_H_INCLUDED

typedef struct file_content
{
  		int length;
    	char * content;
} FILE_CONTENT, *PFILE_CONTENT;

FILE_CONTENT read_file_content(char * file_name, int* error);

#endif // SERVER_FILEREADER_H_INCLUDED
