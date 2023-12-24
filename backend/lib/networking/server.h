
#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "networking/request_handler.h"

#define MAX_CLIENTS 3
#define GET_BUFFER_LENGTH 512

typedef struct
{
    int socket;
    struct sockaddr_in info;
    bool running, listening;
    pthread_t thread_handle;
    int tmp_client;
} server_t;

extern server_t server;

typedef struct
{
    int socket;
} clienthandle_t;

void server_start(void);
void* server_new_client(void* arg);
void server_listen(void);
void server_exit(void);

#endif
