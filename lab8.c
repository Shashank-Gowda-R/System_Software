#include<stdio.h>
int main()
{
    int Max[10][10], need[10][10],alloc[10][10],avail[10],completed[10],safesequence[10],p,r,i,j,process,count=0;
    printf("\nEnter the number of process:");
    scanf("%d",&p);
    for(i=0; i<p; i++)
        completed[i]=0;
    printf("\nEnter the number of resources:");
    scanf("%d",&r);
    printf("\n Enter the Max Matrix for each process:");
    for(i=0; i<p; i++)
    {
        printf("\n For process %d:",i+1);
        for(j=0; j<r; j++)
            scanf("%d",&Max[i][j]);
    }
    printf("\n Enter the allocation for each process:");
    for(i=0; i<p; i++)
    {
        printf("\n For process %d:",i+1);
        for(j=0; j<r; j++)
            scanf("%d",&alloc[i][j]);
    }

    printf("\n Enter the available Resources :");
    for(i=0; i<r; i++)
        scanf("%d",&avail[i]);

    for(i=0; i<p; i++)
        for(j=0; j<r; j++)
            need[i][j]=Max[i][j]-alloc[i][j];

    do
    {
        printf("\n Max matrix: \t Allocation matrix:\n");
        for(i=0; i<p; i++)
        {
            for(j=0; j<r; j++)
                printf("%d",Max[i][j]);
            printf("\t\t");
            for(j=0; j<r; j++)
                printf("%d",alloc[i][j]);

            printf("\n");
        }
        for(j=0; j<r; j++)
                printf("%d",avail[j]);
        process=-1;

        for(i=0; i<p; i++)
        {
            if(completed[i]==0)
            {
                process=i;
                for(j=0; j<r; j++)
                {
                    if(avail[j]<need[i][j])
                    {
                        process=-1;
                        break;
                    }
                }
            }
            if(process !=-1)
                break;
        }
        if(process !=-1)
        {
            printf("\n Process %d runs to completion!", process+1);
            safesequence[count]=process+1;
            count++;
            for(j=0; j<r; j++)
            {
                avail[j]+=alloc[process][j];
                alloc[process][j]=0;
                Max[process][j]=0;
                completed[process]=1;
            }
        }
    }
    while(count!=p && process !=-1);

    if(count ==p)
    {
        printf("\n The system is in a safe state !!\n");
        printf("Safe Sequence:<");
        for(i=0; i<p; i++)
            printf("%d\n",safesequence[i]);
    }
    else
    {
        printf("\n The System is in unsafe state!!");
    }
}

