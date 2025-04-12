#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
    int socket_desc=socket(AF_INET,SOCK_STREAM,0);
    if(socket_desc<0){
        printf("ERROR(socket creation)\n");
        return -1;
    }
    else{
        printf("socket created successfully\n");
    }

    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("ERROR(bind)\n");
        return -1;
    }
    else{
        printf("socket successfully binded to server\n");
    }

    if(listen(socket_desc,1)<0)
    {
        printf("ERROR(listen)\n");
        return -1;
    }
    else{
        printf("Listening for incoming connections...\n");
    }

    int client_addr_length=sizeof(client_addr);
    //return value of accept is used as the socket for comms
    int client_socket=accept(socket_desc,(struct sockaddr*)&client_addr, &client_addr_length);
    if(client_socket<0)
    {
        printf("ERROR(accept)\n");
        return -1;
    }
    else{
        printf("Connected with CLIENT at IP: %s and PORT: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    }
    
    //initialize variables used to simulate STOPnWAIT
    int k=5,m=1,p;
    char server_msg[2000],client_msg[2000],buffer[1000];
    memset(server_msg, '\0', sizeof(server_msg));
    memset(client_msg, '\0', sizeof(client_msg));

    while(k!=0)
    {
        memset(buffer, '\0', sizeof(buffer));
        if(recv(client_socket,buffer,1000,0)<0)
        {
            printf("ERROR(recv)\n");
            return -1;
        }
        else
        {
            if(strncmp(buffer,"frame",5)==0)
            {
                printf("Received frame %d\n",m);
            }
        }

        if(m%2==0)
        {
            strcpy(buffer,"ack");
        }
        else{
            strcpy(buffer,"kca");
            printf("ack lost\n");

            for(p=1;p<=3;p++)
            {
                printf("Waiting for %ds\n",p);
            }
            printf("Retransmitting ACK...\n");
            strcpy(buffer,"ack");
            sleep(3);
        }

        printf("Sending ACK %d\n",m);
        if(send(client_socket,buffer,strlen(buffer),0)<0)
        {
            printf("ERROR(send)\n");
        }
        m++;
        k--;
    }
    close(client_socket);
    close(socket_desc);
    return 0;
}