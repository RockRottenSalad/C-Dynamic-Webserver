#ifndef CONFIG_H
#define CONFIG_H

#include "config/config_types.h"

/*
 * CONFIG - v1
 */

static const int MAX_DYNAMIC_TAGS = 10;
static const int MAX_DYNAMIC_FUNCTIONS = 25;

static page_t pages[10] = 
{
    {
        .page_id = 1,
        .title = "index page or somethin idfk",
        .HTML = "html/hello.html",
        .CSS = NULL,
        .URL = {"/", "/index", "/index.html"},
        .DYNAMIC = false
    },
    {
        .page_id = 2,
        .title = "css test page",
        .HTML = "html/idk.html",
        .CSS = "css/test.css",
        .URL = {"/idk", "/wait"},
        .DYNAMIC = false
    },
    {
        .page_id = 3,
        .title = "dynamic ssc test",
        .HTML = "html/dynamic.html",
        .CSS = "css/test.css",
        .URL = {"/dynamic"},
        .DYNAMIC = true
    }
};

#define ERROR_PAGE_404 0
static page_t error_pages[1] =
{
    {
        .page_id = 404,
        .title = "404 Not Found",
        .HTML = "html/404.html",
        .CSS = "css/404.css"
    }
};

#endif
