#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){

    //create socket
    int socket_desc=socket(AF_INET,SOCK_STREAM,0);
    //check if socket is created successfully
    if(socket_desc<0)
    {
        printf("socket creation failed\n");
    }
    else
    {
        printf("socket created successfully\n");
        printf("socket file descriptor = %d\n",socket_desc);
    }

    //create socket address structure that we need to connect to 
    struct sockaddr_in server_addr;
    server_addr.sin_family= AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //connect to the server
    int connection=connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(connection<0)
    {
        printf("Connection Unsuccessfull\n");
    }
    else
    {
        printf("Connected to server\n");
    }
    
    //send data to SERVER
    char client_msg[2000],server_msg[2000];
    //clear buffers
    while(1)
    {
        memset(server_msg,'\0',sizeof(server_msg));
        memset(client_msg,'\0',sizeof(client_msg));

        printf("Enter Message: ");
        gets(client_msg);
        //send(socket_fd, buffer, length_of_data, flags) | returns no.of bytes of the msg sent
        int sent=send(socket_desc,client_msg,sizeof(client_msg),0);
        if (sent<0)
        {
            printf("ERROR\n");
        }
        else
        {
            printf("msg sent!\n");
        }
        //receive data from SERVER
        int recvd=recv(socket_desc,server_msg,sizeof(server_msg),0);
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
    close(socket_desc);
    return 0;
}