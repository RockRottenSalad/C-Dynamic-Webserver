
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<time.h>

#include "dynamic_ssc/dynamic_def.h"

void dynamic_plus(FILE* client_stream, char* arg)
{

    fprintf(client_stream, "5 + 5 = %d<br>", 5+5);
}

