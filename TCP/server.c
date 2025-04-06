#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    int sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Socket created successfully\n");
        printf("socketfc=%d\n", sockfd);
    }
}