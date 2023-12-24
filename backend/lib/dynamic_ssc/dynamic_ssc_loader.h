#ifndef DYNAMIC_SSC_LOADER_H
#define DYNAMIC_SSC_LOADER_H

#include<string.h>

#include "utils/regex_handler.h"
#include "dynamic_ssc/dynamic_def.h"
#include "dynamic_ssc/dynamic_wrapper.h"

#define BUFFER_LENGTH 512
#define MAX_DYNAMIC_BUFFER 128

typedef struct
{
    int dynamic_tags, dynamic_functions;
} dynamic_config_t;

extern dynamic_config_t dynamic_config;

static dyn_function_t dyn_function_hashmap[25];

void dynamic_ssc_init(int dynamic_tags, int dynamic_functions);

dyn_function_wrap_t* dynamic_parse(const char* file_path);

int hash_function(const char* function);

#endif
