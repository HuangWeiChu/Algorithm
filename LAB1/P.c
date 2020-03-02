/******************************************************************************

0 3 0 4 4 0 0 0 0 0
3 0 9 0 2 3 0 0 0 0
0 9 0 0 0 6 1 0 0 0
4 0 0 0 5 0 0 6 0 0
4 2 0 5 0 8 0 2 1 0
0 3 6 0 8 0 2 0 3 7
0 0 1 0 0 2 0 0 0 8
0 0 0 6 2 0 0 0 4 0
0 0 0 0 1 3 0 4 0 7
0 0 0 0 0 7 8 0 7 0

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min,mincost,cost[20][20];
int visited[20] = {0};
int ne=1,n,a,b,u,v,i,j;

void showCost() {
    printf("\n-----\n");
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            printf("%d\t",cost[i][j]);
        }
        printf("\n");
    }
    printf("-----");
}

int main() {
    printf("Enter nodes:");
    scanf("%d",&n);
    printf("%d",n);
    printf("\nEnter matrix:\n");
    clock_t startime,endtime;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) {
            scanf("%d",&cost[i][j]);
            if(cost[i][j]==0)
                cost[i][j]=999;
        }
    startime = clock();
    
    visited[1] = 1;
    //printf("%d",parent[0]);
    //showCost();
    
    while(ne<n) {
        for(i=1,min=999;i<=n;i++) {
            for(j=1;j<=n;j++) {
                if(cost[i][j]<min) 
                    if(visited[i] != 0) {
                        min = cost[i][j];
                        a=u=i;
                        b=v=j;
                    }
            }
        }
        if(visited[u] == 0 || visited[v] == 0) {
            printf("\n%d edge(%d,%d) = %d",ne++,a,b,min);
            mincost += min;
            visited[b] = 1;
        }
        //showUV();
        
        cost[a][b] = cost[b][a] = 999;
        
        //showCost();
    }
    
    //showCost();
    endtime = clock();
    printf("\nMin cost = %d\n",mincost);
    printf("\nTime take = %f",(endtime-startime)/(double)CLOCKS_PER_SEC);
    return 0;
}
