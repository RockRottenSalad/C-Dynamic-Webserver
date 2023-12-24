#ifndef DYNAMIC_WRAPPER_H
#define DYNAMIC_WRAPPER_H

typedef void (*dyn_function_t)(FILE*,char*);

typedef struct
{
//    volatile void* dyn_function_v;
    dyn_function_t dyn_function_v;
    char* arg;
    int dyn_line;
} dyn_function_wrap_t;

#endif
