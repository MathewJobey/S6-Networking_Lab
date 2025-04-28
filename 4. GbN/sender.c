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

struct timeval timeout;

void func(int sockfd, int nf, int ws)
{
    char buff[MAX];
    int ack, i = 0, n, k, w1 = 0, w2 = ws - 1, count_ack = 0, flag = 0;

    // Set socket timeout for receiving acknowledgments
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) < 0)
    {
        perror("setsockopt(SO_RCVTIMEO) failed");
    }

    // Send initial frames within the window size
    for (i = 0; i < nf && i <= w2; i++)
    {
        bzero(buff, sizeof(buff));
        snprintf(buff, sizeof(buff), "%d", i);
        k = send(sockfd, buff, sizeof(buff), 0);
        printf("Frame %d sent\n", i);
    }

    while (1)
    {
        if (count_ack == nf)
        {
            // Send "Exit" message to terminate communication
            strcpy(buff, "Exit");
            k = send(sockfd, buff, sizeof(buff), 0);
            printf("All frames acknowledged. Exiting.\n");
            break;
        }

        // Resend frames if the window is not full
        if (w2 - w1 != ws - 1 && flag == 0 && i < nf)
        {
            bzero(buff, sizeof(buff));
            snprintf(buff, sizeof(buff), "%d", i);
            k = send(sockfd, buff, sizeof(buff), 0);
            printf("Frame %d sent\n", i);
            w2++;
            i++;
        }

        flag = 0;
        bzero(buff, sizeof(buff));

        // Receive acknowledgment from the receiver
        n = recv(sockfd, buff, MAX, 0);

        if (n > 0)
        {
            ack = atoi(buff);

            if (ack == -1)
            {
                // Negative acknowledgment: resend the first frame in the window
                printf("Acknowledgment not received for %d. Resending frame %d.\n", w1, w1);
                bzero(buff, sizeof(buff));
                snprintf(buff, sizeof(buff), "%d", w1);
                k = send(sockfd, buff, sizeof(buff), 0);
                printf("Frame %d sent\n", w1);
            }
            else
            {
                // Positive acknowledgment: slide the window
                printf("Acknowledgment received: %d\n", ack);
                count_ack++;
                w1++;
            }
        }
        else
        {
            // Timeout: resend the first frame in the window
            printf("Timeout occurred. Resending frame %d.\n", w1);
            bzero(buff, sizeof(buff));
            snprintf(buff, sizeof(buff), "%d", w1);
            k = send(sockfd, buff, sizeof(buff), 0);
            printf("Frame %d sent\n", w1);
        }
    }
}

int main()
{
    int sockfd, f, w;
    struct sockaddr_in servaddr;

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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Set timeout for receiving acknowledgments
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    // Connect to the server
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("Connection with the server failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server\n");

    // Input number of frames and window size
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    printf("Enter the window size: ");
    scanf("%d", &w);

    // Start communication
    func(sockfd, f, w);

    // Close the socket
    close(sockfd);

    return 0;
}
