
#include "networking/request_handler.h"

/*
 * 200 OK = 0
 * 404 Not Found = 1
 * 403 Forbidden = 2
 */

const char STATUS_CODES[][20] = 
{
    {"200 OK"},
    {"404 Not Found"},
    {"403 Forbidden"}
};

const char CONTENT_TYPE[][20] =
{
    {"text/html"},
    {"text/css"}
};

void build_http_response(FILE* client_stream, int status_code, int type)
{
    fprintf(client_stream, "HTTP/1.1 %s\r\nContent-Type: %s\r\n\n",
            STATUS_CODES[status_code], CONTENT_TYPE[type]);
}

void build_dynamic_content_response(FILE* client_stream, page_t* page, FILE* file_stream)
{
    char buffer[BUFFER_LENGTH];
    int line_count = 0, dynamic_count = 0;
    dyn_function_t func;

    while(fgets(buffer, sizeof(buffer), file_stream))
    {
        line_count++;

        if(line_count == page->dyn_wrap[dynamic_count].dyn_line)
        {
            func = page->dyn_wrap[dynamic_count].dyn_function_v;
            (*func)(client_stream, page->dyn_wrap[dynamic_count].arg);
            dynamic_count++;
        }
        else
            fprintf(client_stream, "%s", buffer);
    }
}

void build_content_response(FILE* client_stream, page_t* page)
{
    char buffer[BUFFER_LENGTH];
    FILE* file_stream;

    fprintf(client_stream, "<!DOCTYPE html>\n<html>\n<head>\n<title>%s</title>\n", page->title);

    // Check if page has a css file
    if(page->CSS != NULL)
    {
        fprintf(client_stream, "<style>\n");
        file_stream = fopen(page->CSS, "r");
        while(fgets(buffer, sizeof(buffer), file_stream))
            fprintf(client_stream, "%s", buffer);

        fclose(file_stream);
        fprintf(client_stream, "\n</style>\n</head>\n");
    }

    fprintf(client_stream, "<body>\n");
    file_stream = fopen(page->HTML, "r");

    if(!page->DYNAMIC)
        while(fgets(buffer, sizeof(buffer), file_stream))
            fprintf(client_stream, "%s", buffer);
    else
        build_dynamic_content_response(client_stream, page, file_stream);

    fprintf(client_stream, "\n</body>\n</html>");

    fclose(file_stream);
}


int handle_request(FILE* client_stream, const char* get_request)
{
    int ret = 0, status_code = OK_200;
    char* buffer = NULL, *token = NULL; 

    buffer = malloc(sizeof(char) * REQ_MAX_LEN);
    ret = regex_nmatch(&regex_container.parse_get, get_request, &buffer, REQ_MAX_LEN);
    if(ret != 0)
        return ret;

    // buffer = "GET /path/here HTTP/1.1"
    // strtok is used to fetch page path, spaces are guranteed from regex
    token = strtok(buffer, " ");
    token = strtok(NULL, " ");

    page_t* page = pages_hashmap[hash_page(token)];

    if(page == NULL)
    {
        status_code = NOT_FOUND_404;
        page = &error_pages[ERROR_PAGE_404];
    }

    build_http_response(client_stream, status_code, 0);
    build_content_response(client_stream, page);

    free(buffer);

    return 0;
}

