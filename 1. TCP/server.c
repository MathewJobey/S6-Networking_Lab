#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{

    // CREATE SERVER socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // a file descriptor is returned (+ve integer)
    if (server_socket < 0)
    {
        printf("ERROR(socket creation)\n");
        return -1;
    }
    else
    {
        printf("socket created successfully\n");
    }

    // define SERVER address
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // BIND the defined address to the SERVER's socket
    int binding = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)); // same as connect parameters
    if (binding < 0)
    {
        printf("ERROR(bind)\n");
        return -1;
    }
    else
    {
        printf("socket binded to server's address\n");
    }

    // LISTEN for connections
    int listening = listen(server_socket, 1); // 1 is the backlog: max number of pending connections
    if (listening < 0)
    {
        printf("ERROR(listen)\n");
        return -1;
    }
    else
    {
        printf("Listening for incoming connections...\n");
    }

    // ACCEPT the CLIENT connection
    int client_socket;
    int client_addr_size = sizeof(client_addr);
    // accept(): server doesn't know the client in advance,
    // so kernel fills client_addr when a client connects
    // so the client addr struct length can change depending on what the kernel inserts
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
    if (client_socket < 0)
    {
        printf("ERROR(accept)\n");
        return -1;
    }
    else
    {
        printf("CLIENT connected from IP: %s and PORT: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        // inet_ntoa(): converts IP from binary to readable string (e.g., 127.0.0.1)
        // ntohs(): converts port from network byte order to host byte order
    }

    char server_msg[2000], client_msg[2000];
    while (1)
    {
        // clear buffers
        memset(server_msg, '\0', sizeof(server_msg));
        memset(client_msg, '\0', sizeof(client_msg));
        // RECV data from CLIENT
        int recvd = recv(client_socket, client_msg, sizeof(client_msg), 0);
        if (recvd < 0)
        {
            printf("ERROR(recv)\n");
            return -1;
        }
        printf("CLIENT's response: %s\n", client_msg);
        // SEND data to CLIENT
        printf("Enter Message: ");
        gets(server_msg);
        int sent = send(client_socket, server_msg, sizeof(server_msg), 0);
        if (sent < 0)
        {
            printf("ERROR(send)\n");
            return -1;
        }
        if (strcmp(client_msg, "exit") == 0)
            break;
    }
    close(client_socket);
    close(server_socket);
    return 0;
}
//To allow retrying connections; wrap the accept() + chat logic inside a while(1) 