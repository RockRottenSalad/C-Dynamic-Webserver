
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "config/config_types.h"

#define OK_200 0
#define NOT_FOUND_404 1
#define FORBIDDEN_403 2

long file_length(const char* file_path);
long file_length_fd(FILE* fd);

bool file_exists(const char* file_path);
bool file_exists_fd(FILE* fd);

int file_type(char* file_name);

int file_read(const char* file_path, int* type_out,long* len_out, char* dest);

int file_nread(const char* file_path, long n, int* type_out,
        long* len_out, char* dest);

#endif
