
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<time.h>

#include "dynamic_ssc/dynamic_def.h"

void dynamic_test(FILE* client_stream, char* arg)
{

    fprintf(client_stream, "LE SSC RANDOM NUMBER IS: %d<br>", rand() % 100);
}

void another_dynamic_test(FILE* client_stream, char* arg)
{
    time_t seconds = time(NULL);
    fprintf(client_stream, "did you know that %ld seconds have passed since jan 1. 1970?<br>", seconds);
}

void include_file(FILE* client_stream, char* file_path)
{
    FILE* fd = NULL;
    char buffer[BUFFER_LENGTH];

    fd = fopen(file_path, "r");
    assert(fd != NULL);

    while(fgets(buffer, sizeof(buffer), fd))
        fprintf(client_stream, "%s", buffer);

    fclose(fd);
}
