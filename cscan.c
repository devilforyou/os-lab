#include <stdio.h>
#include <stdlib.h>
#define MAX_REQ 7
#define TOTAL 199

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
   for (int i=point;i<TOTAL;i++)
   for(int c=0;c<MAX_REQ;c++){
        if(i==req[c])
        {printf("Requirement Fulfilled : %d\n",req[c]);
      }
    }
    for (int i=0;i<point;i++)
   for(int c=0;c<MAX_REQ;c++){
        if(i==req[c])
        {printf("Requirement Fulfilled : %d\n",req[c]);
        move=i;
      }
    }
    printf("The Total Number of Movement : %d",(TOTAL-point+TOTAL+move));

}
