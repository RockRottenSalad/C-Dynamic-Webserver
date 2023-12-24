#ifndef CONFIG_TYPES_H
#define CONFIG_TYPES_H

#include <stdbool.h>
#include<stdio.h>

#include "dynamic_ssc/dynamic_ssc_loader.h"
#include "dynamic_ssc/dynamic_wrapper.h"

typedef struct
{
    const unsigned int page_id;
    const char* title;
    const char* HTML;
    const char* CSS;
    bool DYNAMIC;
    char URL[10][64];

    dyn_function_wrap_t* dyn_wrap;
    int dyn_wrap_len;
} page_t;

#endif
