#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
    int server_socket;
    server_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(server_socket<0)
    {
        printf("ERROR(socket creation)\n");
        return -1;
    }
    else
    {
        printf("socket created successfully\n");
    }
    //set SERVER's PORT & IP
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //bind the socket to the set PORT & IP
    if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("ERROR(bind)\n");
        return -1;
    }
    else
    {
        printf("socket binded to PORT & IP\n");
    }
    printf("Waiting For Incoming Messages...\n");

    char server_msg[2000],client_msg[2000];
    //clear buffers
    memset(server_msg,'\0',sizeof(server_msg));
    memset(client_msg,'\0',sizeof(client_msg));

    //RECV data from CLIENT
    if(recvfrom(server_socket,client_msg,strlen(client_msg),0,(struct sockaddr*)&client_addr,sizeof(client_addr),0)<0)
    {
        printf("ERROR(recv)\n");
        return -1;
    }
    else
    {
        printf("Received msg from IP: %s and PORT: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        printf("Msg received: %s\n",client_msg);
    }
    //SEND data to CLIENT
    printf("Enter msg: ");
    gets(server_msg);
    if(sendto(server_socket,server_msg,strlen(server_msg),0,(struct sockaddr*)&client_addr,sizeof(client_addr),0)<0)
    {
        printf("ERROR(send)\n");
        return -1;      
    }
    close(server_socket);
    return 0;
}
