
#include "utils/file_handler.h"

long file_length(const char* file_path)
{
    FILE* fd = NULL;
    long len = 0;

    fd = fopen(file_path, "r");
    if(fd == NULL)
        return NOT_FOUND_404;

    (void)fseek(fd, 0, SEEK_END);
    len  = ftell(fd);

    fclose(fd);

    return len;
}

inline
long file_length_fd(FILE* fd)
{
    long length = 0;

    (void)fseek(fd, 0, SEEK_END);
    length = ftell(fd);
    rewind(fd);

    return length;
}

bool file_exists(const char* file_path)
{
    FILE* fd = NULL;
    bool exists;

    fd = fopen(file_path, "r");
    if(fd == NULL)
        exists = false;
    else
    {
        exists = true;
        fclose(fd);
    }


    return exists;
}

inline
bool file_exists_fd(FILE* fd)
{
    if(fd == NULL)
        return false;
    return true;
}

int file_type(char* file_name)
{
    int type = 0, len = 0;
    char* token = NULL, *prev = NULL;

    len = strlen(file_name);
    token = strtok(file_name, ".");

    while((token = strtok(NULL, ".")))
        prev = token;

    for(int i = 0; i < len; i++)
        type += prev[i];

    switch(type)
    {
        case (int)('h'+'t'+'m'+'l'):
            return 0;
        case (int)('c'+'s'+'s'):
            return 1;
    }
    return -1;
}

int file_read(const char* file_path, int* type_out,
        long* len_out, char* dest)
{
    FILE* fd = NULL;
    long len;
    *len_out = 0;

    fd = fopen(file_path, "r");
    if(fd == NULL)
        return NOT_FOUND_404;

    len = file_length_fd(fd);

    (void)fread(dest, sizeof(dest), len, fd);

    *type_out = file_type((char*)file_path);
    *len_out = len;

    return OK_200;
}

int file_nread(const char* file_path, long n, int* type_out,
        long* len_out, char* dest)
{
    FILE* fd = NULL;
    long len;
    *len_out = 0;

    fd = fopen(file_path, "r");
    if(fd == NULL)
        return NOT_FOUND_404;

    len = file_length_fd(fd);

    if(len > n)
    {
        printf("\n\nERROR | file_nread: file length longer than n\n\n");
        return FORBIDDEN_403;
    }

    (void)fread(dest, sizeof(dest), len, fd);

    *type_out = file_type(strdup(file_path));
    *len_out = len;

    return OK_200;
}

