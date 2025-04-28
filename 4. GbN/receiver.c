#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
    char buff[MAX];
    int f, c, ack, next = 0;

    while (1)
    {
        sleep(1);
        bzero(buff, MAX);

        // Receive data from the client
        recv(connfd, buff, MAX, 0);

        // Check for "Exit" message to terminate
        if (strcmp("Exit", buff) == 0)
        {
            printf("Exit\n");
            break;
        }

        f = atoi(buff); // Convert received frame number to integer

        // Simulate random behavior for frame reception
        c = rand() % 3;

        switch (c)
        {
        case 0: // Frame not received
            printf("Frame %d not received\n", f);
            ack = -1;
            printf("Negative acknowledgment sent: %d\n", f);
            bzero(buff, MAX);
            snprintf(buff, sizeof(buff), "%d", ack);
            send(connfd, buff, sizeof(buff), 0);
            break;

        case 1: // Frame received with delay
            ack = f;
            sleep(2); // Simulate delay
            printf("Frame %d received\nAcknowledgment sent: %d\n", f, ack);
            bzero(buff, MAX);
            snprintf(buff, sizeof(buff), "%d", ack);
            send(connfd, buff, sizeof(buff), 0);
            next = ack + 1;
            break;

        case 2: // Frame received normally
            ack = f;
            printf("Frame %d received\nAcknowledgment sent: %d\n", f, ack);
            bzero(buff, MAX);
            snprintf(buff, sizeof(buff), "%d", ack);
            send(connfd, buff, sizeof(buff), 0);
            next = ack + 1;
            break;
        }
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket successfully created\n");

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket successfully binded\n");

    // Listen for connections
    if (listen(sockfd, 5) != 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening\n");

    len = sizeof(cli);

    // Accept client connection
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        perror("Server accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Server accepted the client\n");

    // Handle client communication
    func(connfd);

    // Close the socket
    close(sockfd);

    return 0;
}