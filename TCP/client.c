#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){

    //CREATE CLIENT socket
    int client_socket=socket(AF_INET,SOCK_STREAM,0);//a file descriptor is returned (+ve integer)
    if(client_socket<0)
    {
        printf("ERROR(socket creation)\n");
    }
    else
    {
        printf("socket created successfully\n");
    }

    //create socket address structure that we need to connect to 
    struct sockaddr_in server_addr;
    server_addr.sin_family= AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //CONNECT to the SERVER
    int connection=connect(client_socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(connection<0)
    {
        printf("Connection Unsuccessfull\n");
    }
    else
    {
        printf("Connected to server\n");
    }
    
    char client_msg[2000],server_msg[2000];
    //clear buffers
    while(1)
    {
        memset(server_msg,'\0',sizeof(server_msg));
        memset(client_msg,'\0',sizeof(client_msg));

        //SEND data to SERVER
        printf("Enter Message: ");
        gets(client_msg);
        //send(socket_fd, buffer, length_of_data, flags) | returns no.of bytes of the msg sent
        int sent=send(client_socket,client_msg,sizeof(client_msg),0);
        if (sent<0)
        {
            printf("ERROR\n");
        }
        else
        {
            printf("msg sent!\n");
        }
        //receive data from SERVER
        int recvd=recv(client_socket,server_msg,sizeof(server_msg),0);
        if(recvd<0)
        {
            printf("ERROR\n");
        }
        else
        {
            printf("msg recvd!\n");
        }
        printf("SERVER's response: %s\n",server_msg);
        if(strcmp(server_msg,"exit")==0)    
            break;
        } 
    close(client_socket_desc);
    return 0
}