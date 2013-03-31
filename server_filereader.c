#include "server_filereader.h"

#include <stdlib.h>
#include <stdio.h>

// Function for reading file
FILE_CONTENT read_file_content(char * file_name, int * error)
{
    FILE *pFile;

    size_t result;

    FILE_CONTENT ans;

    // Opening file
    pFile = fopen(file_name, "r");
    if (pFile == NULL) {
        *error = 1;
    return ans;
    }

    fseek(pFile, 0, SEEK_END);
    ans.length = ftell(pFile);
    rewind(pFile);

    ans.content = (char*)calloc(ans.length, sizeof(char));
    if (ans.content == NULL) {
        *error = 2;
	return ans;
    }

    result = fread(ans.content, 1, ans.length, pFile);
    if (result != ans.length) {
        *error = 3;
	return ans;  
    }

    fclose(pFile);

    *error = 0;
    return ans;
}
