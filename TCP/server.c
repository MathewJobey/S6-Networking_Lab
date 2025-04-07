#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){

    //CREATE SERVER socket
    int server_socket;
    server_socket=socket(AF_INET,SOCK_STREAM,0);//a file descriptor is returned (+ve integer)
    if(server_socket<0)
    {
        printf("ERROR(socket creation)\n");   
    }
    else
    {
        printf("socket created successfully\n");
    }

    //define SERVER address
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //BIND the defined address to the SERVER's socket
    int binding=bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));//same as connect parameters
    if(binding<0)
    {
        printf("ERROR(bind)\n");
    }
    else
    {
        printf("socket binded to server's address\n");
    }

    //LISTEN for connections
    int listening=listen(server_socket,1);// 1 is the backlog: max number of pending connections
    if(listening<0)
    {
        printf("ERROR(listen)\n");
    }
    else
    {
        printf("Listening for incoming connections...\n");
    }

    //ACCEPT the CLIENT connection
    int client_socket;
    // accept(): server doesn't know the client in advance,
    // so kernel fills client_addr when a client connects
    //so the client addr struct length can change depending on what the kernel inserts

    client_socket=accept()
}