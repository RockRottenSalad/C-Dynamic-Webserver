
#include "dynamic_ssc/dynamic_ssc_loader.h"

dynamic_config_t dynamic_config;

/*
 * Dynamic functions are added to init function on compiliation
 * DO NOT MANUALLY EDIT THIS FILE
 */

void dynamic_ssc_init(int dynamic_tags, int dynamic_functions)
{
    dynamic_config.dynamic_tags = dynamic_tags;
    dynamic_config.dynamic_functions = dynamic_functions;

    for(int i = 0; i < dynamic_config.dynamic_functions; i++)
        dyn_function_hashmap[i] = NULL;

    int index = 0;

// ### AUTOMATIC INSERTION POINT ###


}

dyn_function_wrap_t* dynamic_parse(const char* file_path)
{
    FILE* fd = NULL;
    char buffer[BUFFER_LENGTH];
    char* dynamic_buffer = NULL, *token = NULL;
    int ret = 0, line_count = 0, dynamic_function_count = 0;
    dyn_function_t func = NULL;
    dyn_function_wrap_t* dynamic_functions = NULL;

    dynamic_buffer = (char*)malloc(sizeof(char) * MAX_DYNAMIC_BUFFER);
    dynamic_functions = (dyn_function_wrap_t*)malloc(sizeof(dyn_function_wrap_t) * dynamic_config.dynamic_tags);

    fd = fopen(file_path, "r");
    while(fgets(buffer, sizeof(buffer), fd))
    {
        line_count++;
        ret = regex_nmatch(&regex_container.parse_dynamic, buffer, &dynamic_buffer, MAX_DYNAMIC_BUFFER);
        if(ret == 0)
        {
            // "<dynamic func=actualfunc()"
            // "<dynamic func"
            token = strtok(dynamic_buffer, "=");
            // "actualfunc()"
            token = strtok(NULL, "=");
            func = dyn_function_hashmap[hash_function(token)];
            printf("PARSING TOKEN %s\n", token);
            assert(func != NULL);
            dynamic_functions[dynamic_function_count].dyn_function_v = func;
            dynamic_functions[dynamic_function_count].dyn_line = line_count;
            memset(dynamic_buffer, 0, sizeof(char));
            ret = regex_nmatch(&regex_container.parse_arg, buffer, &dynamic_buffer, MAX_DYNAMIC_BUFFER);
            if(ret == 0)
            {
                dynamic_functions[dynamic_function_count].arg = (char*)malloc(sizeof(char) * strlen(dynamic_buffer));
                strcpy(dynamic_functions[dynamic_function_count].arg, dynamic_buffer+1);
            }

            dynamic_function_count++;
        }
    }

    free(dynamic_buffer);
    fclose(fd);

    return dynamic_functions;
}


int hash_function(const char* function)
{
    int index = 0, len = strlen(function);
    for(int i = 0; i < len; i++)
    {
        index += function[i];
        index *= function[i];
    }

    index *= index;
    index = index % dynamic_config.dynamic_functions;
    if(index < 0)
        index *= -1;

    return index;
}

