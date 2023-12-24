
#include<stdio.h>
#include<signal.h>
#include<time.h>

#include "networking/server.h"
#include "networking/request_handler.h"
#include "utils/regex_handler.h"

#include "config/config_loader.h"

void quit(void)
{
    server.listening = false;
    server_exit();
    regex_delete();
    config_cleanup();
}

void handle_term(int arg)
{
    arg = 0;
    quit();
    printf("\nExit handled by term handler\n");
    exit(arg);
}

int main(void)
{
    signal(SIGINT, handle_term);
    signal(SIGTERM, handle_term);

    srand(time(NULL));

    regex_init();
    dynamic_ssc_init(MAX_DYNAMIC_TAGS, MAX_DYNAMIC_FUNCTIONS);
    page_hashmap_init();

    server_start();
    printf("Server started\n");

    server_listen();
    quit();
    printf("Server closed\n");
    return 0;
}
