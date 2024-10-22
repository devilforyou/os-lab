#include <stdio.h>
#include <stdlib.h>
#define MAX_REQ 7
#define TOTAL 199
int minimum(int p[],int l,int c){
    int l2[l];
    for(int i=0;i<l;i++){
        if(p[i]==999){
        l2[i]=999;
            continue;
        }
        l2[i]=abs(p[i]-c);
    }
    int m=0;
    for(int i=0;i<l;i++){
        if( l2[i]<l2[m] && l2[i]!=999)
        m=i;
        
    }
    return m;
}
int main()
{
    int req[MAX_REQ];
    int i=0;
    printf("Enter the Requests: ");
    for(i=0;i<MAX_REQ;i++){
        scanf("%d",&req[i]);
    }
    int point;
    printf("Enter the current position of pointer: ");
    scanf("%d",&point);
    int curr=point;
    int move=0;
    for(int c=MAX_REQ-1;c>=0;c--){
        int m=minimum(req,MAX_REQ,curr);
        move+=abs(req[m]-curr);
        curr=req[m];
        printf("Requirement Fulfilled : %d\n",req[m]);
        req[m]=999;
    
    }
    printf("The Avg Number of Movement per request : %d",move/MAX_REQ);

}
