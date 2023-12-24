
#include "networking/server.h"

server_t server;

void server_start(void)
{
    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    server.info.sin_family = AF_INET;
    server.info.sin_port = htons(8000);
    server.info.sin_addr.s_addr = inet_addr("192.168.0.40");
    server.thread_handle = 0;

    assert(bind(server.socket, (const struct sockaddr*)&server.info, sizeof(server.info)) == 0);
    
    server.running = true;
    server.listening = false;
}

void* server_new_client(void* arg)
{
    int* client_ptr = (int*)arg;
    int client = *client_ptr;
    free(client_ptr);

    FILE* stream;

    char* buffer = malloc(sizeof(char) * GET_BUFFER_LENGTH);

    ssize_t get_size = recv(client, buffer, GET_BUFFER_LENGTH, 0);
//    printf("\n\nREQUEST: %s\n\n", buffer);
    if(get_size <= 0)
    {
        printf("Empty GET request\n");
        close(client);
        free(buffer);
        return (void*)0;
    }

    stream = fdopen(client, "w+");
    if(stream == NULL)
    {
        printf("Failed to open stream\n");
        close(client);
        free(buffer);
        return (void*)0;
    }

    handle_request(stream, buffer);

    fclose(stream);
    close(client);
    free(buffer);
    return (void*)0;
}

void server_listen(void)
{
    server.listening = true;

    int ret;
    int* int_ptr;
    listen(server.socket, MAX_CLIENTS);
    while(server.listening == true)
    {
        server.tmp_client = accept(server.socket, NULL, NULL);
        printf("Accepted client\n");
        
        int_ptr = malloc(sizeof(int));
        *int_ptr = server.tmp_client;
        ret = pthread_create(&server.thread_handle, NULL, &server_new_client, (void*)int_ptr);
        assert( ret == 0 );
        pthread_detach(server.thread_handle);
    }
}

void server_exit(void)
{
    assert(server.running == true && server.listening == false && close(server.socket) == 0);
    server.running = false;
}
