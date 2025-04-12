#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(){
    int sock_desc = socket(AF_INET, SOCK_STREAM, 0); // a file descriptor is returned (+ve integer)
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
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // CONNECT to the SERVER
    int connection = connect(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connection < 0)
    {
        printf("ERROR(connect)\n");
        return -1;
    }
    else
    {
        printf("Connected to server\n");
    }

    //FTP
    FILE *fp;
    char name[100],fname[100],server_msg[100];
    int bytes_received;//important
    memset(server_msg,'\0',sizeof(server_msg));
    memset(name,'\0',sizeof(name));
    memset(fname,'\0',sizeof(fname));

    printf("Enter filename: ");
    gets(name);
    printf("\nEnter the new filename: ");
    gets(fname);

    fp=fopen(fname,"w");
    send(sock_desc,name,strlen(name),0);
    
    while(1)
    {
        bytes_received=recv(sock_desc,server_msg,sizeof(server_msg),0);
        if(bytes_received<0)
        {
            printf("ERROR(send)\n");
        }
        else
        {
            server_msg[bytes_received]='\0';//Null terminate the received data
            if(strcmp(server_msg,"error")==0)
            {
                printf("File not available\n");
                return -1;
            }
            else if(strcmp(server_msg,"completed")==0)
            {
                printf("File is Transferred...\n");
                fclose(fp);
                break;
            }
            else
            {
                printf("%s\n",server_msg);
                fprintf(fp,"%s",server_msg);
            }
        }
    }
    close(sock_desc);
    return 0;
}