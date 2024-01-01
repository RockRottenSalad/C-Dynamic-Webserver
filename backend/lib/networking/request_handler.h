
#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string.h>

#include "utils/file_handler.h"
#include "utils/regex_handler.h"
#include "config/config_loader.h"
#include "dynamic_ssc/dynamic_ssc_loader.h"

#define REQ_MAX_LEN 64

#define MAX_PAGE_SIZE 512
#define BUFFER_LENGTH 512

void build_http_response(FILE* client_stream, int status_code, int type);

void build_dynamic_content_response(FILE* client_stream, page_t* page, FILE* file_stream);

void build_content_response(FILE* client_stream, page_t* page);

char* build_request(FILE* client_stream, int status_code);

int handle_request(FILE* client_stream, const char* get_request);

#endif
