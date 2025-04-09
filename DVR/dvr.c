//Distance Vector Routing Protocol
#include<stdio.h>

//2d matrix router for distance vector table
struct node{
    unsigned dist[20];
    unsigned from[20];
}router[20];

int main(){

    int nodes;
    printf("Enter no.of routers: ");
    scanf("%d",&nodes);

    //create the initial cost matrix
    int costmat[20][20];
    int i,j,k,count=0;
    printf("\nEnter The Cost Matrix\n");
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            printf("costmat[%d][%d]-",i,j);
            scanf("%d",&costmat[i][j]);
            
            costmat[i][i]=0;//dist to itself=0

            router[i].dist[j]=costmat[i][j];//initialise the distance of cost matrix to routing table
            router[i].from[j]=j;
        }
    }
    do{
        count=0;
        for(i=0;i<nodes;i++)
        {
            for(j=0;j<nodes;j++)
            {
                for(k=0;k<nodes;k++)
                {
                    //check if dist(AB)>dist(Ak)+dist(kB)
                    if(router[i].dist[j]>costmat[i][k]+router[k].dist[j])
                    {
                        //min distance calculation
                        router[i].dist[j]=router[i].dist[k]+router[k].dist[j];
                        router[i].from[j]=k;
                        count++;
                    }
                }
            }
        }
    }while(count!=0);
    
    //print Routing Table for each router
    for(i=0;i<nodes;i++)
    {
        printf("\n\nRouting Table For Router %d\n",i+1);
        for(j=0;j<nodes;j++)
        {
            printf("To Node %d via %d|Distance: %d\n",j+1,router[i].from[j]+1,router[i].dist[j]);
        }
    }
}
