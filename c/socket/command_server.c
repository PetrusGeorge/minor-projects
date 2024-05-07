#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define BACKLOGSIZE 5
#define BUFFER_SIZE 1024
#define QTD_CLIENTS 10
#define FILE_NAME "temp.txt"

typedef struct {
    int fd;
    int index;
    struct sockaddr_in sock_info;
    pthread_t thread;
    int halt_already_used;

} client_t;

pthread_mutex_t halt_mutex;
pthread_mutex_t file_mutex;
FILE *output;

int halt_count = 0;

void *handle_client(void *p) {
    client_t *cli_info = (client_t *)p;

    char buffer_read[BUFFER_SIZE];
    char buffer_write[BUFFER_SIZE];
    char buffer_line[100];

    printf("Handling client(%d,%d)\n", cli_info->index, cli_info->fd);

    while (1) {
        recv(cli_info->fd, buffer_read, (size_t)sizeof(buffer_read), 0);
        if (strncmp(buffer_read, "HALT", 4) == 0) {
            printf("[%d] HALT\n", cli_info->index);

            pthread_mutex_lock(&halt_mutex);

            if (!cli_info->halt_already_used) {
                halt_count++;
                cli_info->halt_already_used = 1;
            }
            if (halt_count >= 5) {
                exit(EXIT_SUCCESS);
            }
            sprintf(buffer_write, "Halt count at %d\n", halt_count);

            pthread_mutex_unlock(&halt_mutex);

        } else if (strncmp(buffer_read, "SHOW", 4) == 0) {
            printf("[%d] SHOW\n", cli_info->index);

            output = fopen(FILE_NAME, "r");

            while (fgets(buffer_line, sizeof(buffer_line), output) != NULL) {
                strcat(buffer_write, buffer_line);
            }
            fclose(output);

        } else {

            strcpy(buffer_write, "Writing to file\n");

            pthread_mutex_lock(&file_mutex);

            output = fopen(FILE_NAME, "a");
            fprintf(output, "%s", buffer_read);
            fclose(output);

            pthread_mutex_unlock(&file_mutex);
        }

        int bytes_sent = send(cli_info->fd, buffer_write, strlen(buffer_write),
                              MSG_NOSIGNAL);
        if (bytes_sent < 0) {
            printf("Client(%d,%d) lost connection\n", cli_info->index,
                   cli_info->fd);
            return 0;
        }

        bzero(buffer_read, BUFFER_SIZE);
        bzero(buffer_write, BUFFER_SIZE);
    }
}

int main(int argc, char *argv[]) {

    // Receive port used for server
    int port;
    if (argc != 2) {
        perror("Run the program with ./cs port_number");
        exit(EXIT_FAILURE);
    }
    port = atoi(argv[1]);

    // Erase past temp
    output = fopen(FILE_NAME, "w");
    fclose(output);

    // server vars
    int server_fd;
    struct sockaddr_in server_sock_config;

    // set random seed
    srand(time(NULL));

    // Try to create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Catch socket create error
    if (server_fd == -1) {
        perror("socket() error!");
        exit(EXIT_FAILURE);
    }

    // Server config
    server_sock_config.sin_family = AF_INET;
    server_sock_config.sin_port = htons(port);
    server_sock_config.sin_addr.s_addr = INADDR_ANY;

    // Try to create the server
    int bind_return = bind(server_fd, (struct sockaddr *)&server_sock_config,
                           sizeof(server_sock_config));

    // Catch bind error
    if (bind_return == -1) {
        perror("bind() error!");
        exit(EXIT_FAILURE);
    }

    // Listen to conenctions
    int listen_return = listen(server_fd, BACKLOGSIZE);

    // Catch listen errors
    if (listen_return == -1) {
        perror("listen() error!");
        exit(EXIT_FAILURE);
    }

    printf("Waiting connection on port: %d\n", port);

    client_t client[QTD_CLIENTS];

    int client_index = 0;
    while (1) {

        // Connect with client
        socklen_t client_sock_info_size;
        struct sockaddr_in client_sock_info;
        int client_fd = accept(server_fd, (struct sockaddr *)&client_sock_info,
                               &client_sock_info_size);

        // Catch connection error
        if (client_fd == -1) {
            perror("accept() error!");
            exit(EXIT_FAILURE);
        }

        printf("New connection stablished\n");

        // Set client info vars
        client[client_index].fd = client_fd;
        client[client_index].index = client_index;
        client[client_index].sock_info = client_sock_info;
        client[client_index].halt_already_used = 0;

        pthread_create(&client[client_index].thread, NULL, handle_client,
                       (void *)&client[client_index]);

        client_index++;
        // Go back to start if end of array
        // Should use a better data structure to handle more cases
        if (client_index >= QTD_CLIENTS) {
            client_index = 0;
        }
    }

    close(server_fd);

    return 0;
}
