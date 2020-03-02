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

//int min,mincost,cost[20][20],parent[20],ne=1,a,b,u,v,i,j,n;

int min,mincost,cost[20][20];
int parent[20];
//int parent[20] = {0};
int ne=1,n,a,b,u,v,i,j;

void showCost() {
    printf("\n-----\n");
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            printf("%d\t",cost[i][j]);
        }
        printf("\n");
    }
    printf("-----\n");
}

void showUV() {
    printf("\nparent(u)[%d]:%d ",u,parent[u]);
    printf("\nparent(v)[%d]:%d ",v,parent[v]);
    printf("\n-----\n");
}

int main() {
    FILE *fp = fopen("input.txt","r"); //開啟檔案
    
    if (fp == NULL) {
        printf("無檔案");
        return -1;
    }
    
    n = 10;
    
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            fscanf(fp,"%d",&cost[i][j]);/*每次讀取一個數，fscanf函式遇到空格或者換行結束*/
            //printf("%d\t",cost[i][j]);
        }
        fscanf(fp,"\n");
        //printf("\n");
    }
    fclose(fp);
    
    showCost();
    
    /*
    printf("Enter nodes:");
    scanf("%d",&n);
    printf("%d",n);
    printf("\nEnter matrix:\n");
    */
    
    clock_t startime,endtime;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) {
            if(cost[i][j]==0)
                cost[i][j]=999;
        }
    startime = clock();
    
    //printf("%d",parent[0]);
    //showCost();
    
    while(ne<n) {
        for(i=1,min=999;i<=n;i++) {
            for(j=1;j<=n;j++) {
                if(cost[i][j]<min) {
                    min = cost[i][j];
                    a=u=i;
                    b=v=j;
                }
            }
        }
        //showUV();
        while(parent[u])
            u = parent[u];
        //showUV();  
        while(parent[v])
            v = parent[v];
        //showUV();
        if(u != v) {
            printf("\n%d edge(%d,%d) = %d",ne++,a,b,min);
            mincost += min;
            parent[v] = u;
        }
        //showUV();
        
        cost[a][b] = cost[b][a] = 999;
        
        //showCost();
    }
    
    //showCost();
    endtime = clock();
    printf("\nMin cost = %d\n",mincost);
    printf("\nTime take = %f",(endtime-startime)/(double)CLOCKS_PER_SEC);
    
    for(int p=1;p<=10;p++)
        printf("\nparent[%d]:%d",p,parent[p]);
    printf("\n");
    
    return 0;
}
