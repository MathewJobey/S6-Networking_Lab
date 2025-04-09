#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(){
    int sock_desc=socket(AF_INET,SOCK_STREAM,0);
    if (sock_desc < 0)
    {
        printf("ERROR(socket creation)\n");
        return -1;
    }
    else
    {
        printf("socket created successfully\n");
    }

    // create socket address structure that we need to connect to
    struct sockaddr_in server_addr,client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("ERROR(bind)\n");
        return -1;
    }
    else
    {
        printf("socket binded successfully\n");
    }

    if(listen(sock_desc,1)<0)
    {
        printf("ERROR(listen)\n");
        return -1;
    }
    else
    {
        printf("Listening for incoming connections...\n");
    }

    int client_addr_length=sizeof(client_addr);
    int client_socket=accept(sock_desc,(struct sockaddr*)&client_addr,&client_addr_length);
    if(client_socket<0)
    {
        printf("ERROR(accept)\n");
        return -1;
    }
    else
    {
        printf("CLIENT connected from IP: %s and PORT: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }

    //FTP
    FILE *fp;
    char client_msg[100],fileread[100];
    memset(client_msg,'\0',100);
    memset(fileread,'\0',100);
    if(recv(client_socket,client_msg,100,0)<0)
    {
        printf("ERROR(recv)\n");
        return -1;
    }
    else
    {
        fp=fopen(client_msg,"r");
        if(fp==NULL)
        {
            send(client_socket,"error",5,0);
            close(client_socket);
        }
        else
        {
            while(fgets(fileread,sizeof(fileread),fp))
            {
                if(send(client_socket,fileread,sizeof(fileread),0)<0)
                {
                    printf("cant send file contents\n");
                }
                sleep(1);
            }
                printf("Done!...\n");
                send(client_socket,"completed",9,0);
        }
    }
    fclose(fp);
    close(sock_desc);
    close(client_socket);
    return 0;
}