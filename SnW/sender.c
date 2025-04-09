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

    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        printf("ERROR(connect)\n");
        return -1;
    }
    else{
        printf("Connected to SERVER\n");
    }

    char server_msg[2000],client_msg[2000],buffer[1000];
    //clear buffers
    memset(server_msg, '\0', sizeof(server_msg));
    memset(client_msg, '\0', sizeof(client_msg));
    memset(buffer, '\0', sizeof(buffer));

    //initialize variables used to simulate STOPnWAIT
    int k=5,m=1,p;
    while(k!=0)
    {
        if(m<=5)
        {
            printf("Sending frame %d\n",m);
        }
        if(m%2==0)
        {
            strcpy(buffer,"frame");
        }
        else
        {   //simulating packet loss for odd frames
            strcpy(buffer,"error");
            printf("packet loss\n");
            // wait 3s to simulate timeout
            for(p=1;p<=3;p++)
            {   
                printf("Waiting for %ds\n",p);
            }
            printf("Retransmitting...\n");
            strcpy(buffer,"frame");
            sleep(3);
        }
        
        if(send(socket_desc,buffer,strlen(buffer),0)<0)
        {
            printf("ERROR(send)\n");
            return -1;
        }
        else{
            printf("send frame %d\n",m);
        }
        //clear buffer before receiving
        memset(buffer, '\0', sizeof(buffer));
        //recv and send into buffer as temporary storage to check ack only
        if(recv(socket_desc,buffer,1000,0)<0){
            printf("ERROR(recv)\n");
            return -1;
        }
        else{
            if(strncmp(buffer,"ack",3)==0)//strn for checking first n chars
            {
                printf("Ack received for frame %d\n",m);
            }
            else
            {
                printf("No Ack received for frame %d\n",m);
            }
        }
        m++;
        k--;
    }
    close(socket_desc);
    return 0;
}