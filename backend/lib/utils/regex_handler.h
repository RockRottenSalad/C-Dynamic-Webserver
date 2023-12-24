#ifndef REGEX_HANDLER_H
#define REGEX_HANDLER_H

#include<regex.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define REQ_MAX_LEN 64

typedef struct
{
    regex_t parse_get;
    regex_t parse_dynamic;
    regex_t parse_arg;
} regex_container_t;

extern regex_container_t regex_container;


void regex_init(void);

void regex_delete(void);

int regex_match(regex_t* reg, const char* str, char** dest);

int regex_nmatch(regex_t* reg, const char* str, char** dest, int n);

#endif
