#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
    //create CLIENT socket
    int client_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(client_socket<0)
    {
        printf("ERROR(socket creation)\n");
        return -1;
    }
    else
    {
        printf("socket created successfully\n");
    }

    //define server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    char client_msg[2000],server_msg[2000];
    //clear buffers
    memset(server_msg,'\0',sizeof(server_msg));
    memset(client_msg,'\0',sizeof(client_msg));
    
    int server_addr_length=sizeof(server_addr);
    //SEND data to SERVER
    printf("Enter msg: ");
    gets(client_msg);
    if(sendto(client_socket,client_msg,strlen(client_msg),0,(struct sockaddr*)&server_addr,server_addr_length)<0)//send+connect paramenters combined
    {
        printf("ERROR(send)\n");
        return -1;
    }
    //RECV data from SERVER
    if(recvfrom(client_socket,server_msg,sizeof(server_msg),0,(struct sockaddr*)&server_addr,&server_addr_length)<0)
    {
        printf("ERROR(recv)\n");
        return -1;
    }
    else
    {
        printf("SERVER's response: %s\n",server_msg);
    }
    close(client_socket);
    return 0;
}