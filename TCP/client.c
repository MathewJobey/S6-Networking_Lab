#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{

    // CREATE CLIENT socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0); // a file descriptor is returned (+ve integer)
    if (client_socket < 0)
    {
        printf("ERROR(socket creation)\n");
        return -1;
    }
    else
    {
        printf("socket created successfully\n");
    }

    // create socket address structure that we need to connect to
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // CONNECT to the SERVER
    int connection = connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connection < 0)
    {
        printf("ERROR(connect)\n");
        return -1;
    }
    else
    {
        printf("Connected to server\n");
    }

    char client_msg[2000], server_msg[2000];
    while (1)
    {
        // clear buffers
        memset(server_msg, '\0', sizeof(server_msg));
        memset(client_msg, '\0', sizeof(client_msg));

        // SEND data to SERVER
        printf("Enter Message: ");
        gets(client_msg);
        // send(socket_fd, buffer, length_of_data, flags) | returns no.of bytes of the msg sent
        int sent = send(client_socket, client_msg, sizeof(client_msg), 0);
        if (sent < 0)
        {
            printf("ERROR(send)\n");
            return -1;
        }
        // recv data from SERVER
        int recvd = recv(client_socket, server_msg, sizeof(server_msg), 0);
        if (recvd < 0)
        {
            printf("ERROR(recv)\n");
            return -1;
        }
        printf("SERVER's response: %s\n", server_msg);
        if (strcmp(server_msg, "exit") == 0)
            break;
    }
    close(client_socket);
    return 0;
}

/*
    As a CLIENT:
    - We don't need to manually define our own IP and port.
    - The OS assigns them automatically (any free IP/port available).
    - We ONLY need to know the SERVER's:
        - IP address (e.g., "127.0.0.1")
        - Port number (e.g., 2000)
    - Then, we use connect() to reach that specific server address.

    Summary:
    CLIENT -> connects TO -> SERVER_IP : SERVER_PORT
*/