#include<stdio.h>
#include<stdlib.h>
struct proc
{
    int id;
    int arrival;
    int burst;
    int rem;
    int wait;
    int finish;
    int turnaround;
    float ratio;
} process[10];
struct proc temp;
int no;
int chkprocess(int);
int nextprocess();
void roundrobin(int,int,int[],int[]);
void srtf(int);
int main()
{
    int n,tq,choice;
    int bt[10],st[10],i,j,k;
    do
    {
        printf("\n ****MENU****");
        printf("\n 1. ROUND ROBIN \n 2.SRTF \n 3. EXIT \n");
        printf("Enter your chpoice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("ROUND ROBIN SCHEDULING ALGORITHM");
            printf("\nEnter number of process:");
            scanf("%d",&n);
            printf("\nEnter burst time for %d process",n);
            for(i=0; i<n; i++)
            {
                scanf("%d",&bt[i]);
                st[i]=bt[i];
            }
            printf("Enter the quantum time:");
            scanf("%d",&tq);
            roundrobin(n,tq,st,bt);
            break;
        case 2:
            printf("SHORTEST REMAINING TIME FIRST");
            printf("\nEnter the number of process");
            scanf("%d",&n);
            srtf(n);
            break;
        case 3:
            exit(0);
        }
    }
    while(choice != 3);
}
void roundrobin(int n,int tq,int st[], int bt[])
{
    int time=0;
    int tat[10],wt[10],i,count=0,swt=0,stat=0,temp1,sq=0,j,k;
    float awt=0.0,atat=0.0;
    while(1)
    {
        for (i=0,count=0; i<n; i++)
        {
            temp1=tq;
            if(st[i] ==0)
            {
                count++;
                continue;
            }
            if(st[i]>tq)
                st[i]-=tq;
            else if(st[i]>=0)
            {
                temp1=st[i];
                st[i]=0;
            }
            sq+=temp1;
            tat[i]=sq;
        }
        if(n==count)
            break;
    }
    for(i=0; i<n; i++)
    {
        wt[i]=tat[i]-bt[i];
        swt=swt+wt[i];
        stat=stat+tat[i];
    }
    awt=(float)swt/n;
    atat=(float)stat/n;
    printf("\nProcess_No \t Burst_Time \t Waiting_Time \t Turnaround_Time\n");
    for(i=0; i<n; i++)
    {
        printf("%d \t\t %d \t\t %d \t\t %d\n",i+1,bt[i],wt[i],tat[i]);
    }
    printf("Average waiting time is %f\nAverage turn around time is %f",awt,atat);
}

int chkprocess(int s)
{
    int i;
    for(i=1; i<=s; i++)
    {
        if( process[i].rem!=0)
            return 1;
    }
    return 0;
}

int nextprocess()
{
    int min,l,i;
    min = 32000;
    for(i=1; i<=no; i++)
    {
        if(process[i].rem !=0 && process[i].rem < min)
        {
            min= process[i].rem;
            l=i;
        }
    }
    return l;
}

void srtf(int n)
{
    int i,j,k,time=0;
    float tavg,wavg;
    for(i=1; i<=n; i++)
    {
        process[i].id=i;
        printf("\nEnter the arrival time of process %d:",i);
        scanf("%d",&(process[i].arrival));
        printf("\nEnter the burst time of process %d:",i);
        scanf("%d",&(process[i].burst));
        process[i].rem=process[i].burst;
    }
    for(i=1; i<=n; i++)
    {
        for(j=i; j<=n; j++)
        {
            if(process[i].arrival > process[j].arrival)
            {
                temp= process[i];
                process[i] = process[j];
                process[j]= temp;
            }
        }
    }
    no =0;
    j=1;
    while(chkprocess(n)==1)
    {
        if(process[no+1].arrival == time)
        {
            no++;
            if(process[j].rem==0)
                process[j].finish=time;
            j=nextprocess();
        }
        if(process[j].rem!=0)
        {
            process[j].rem--;
            for(i=1; i<=no; i++)
            {
                if(i!=j && process[i].rem !=0 )
                    process[i].wait++;
            }
        }
        else
        {
            process[j].finish = time;
            j = nextprocess();
            time--;
            k=j;
        }
        time ++;
    }
    process[k].finish=time;
    printf("\nProcess_No \tArrival_Time\t Burst_Time \t Waiting_Time\t Finishing_Time \t Turnaround_Time \t Tr/Tb\n");
    printf("%5s \t %9s \t %7s \t %10s \t %8s \t %9s \n","id","time","time","time","time","time");
    for(i=1; i<=n; i++)
    {
        process[i].turnaround= process[i].wait+process[i].burst;
        process[i].ratio =(float)process[i].turnaround/ (float)process[i].burst;
        printf("%5d %8d %7d %8d %10d %9d %10.1f", process[i].id,process[i].arrival,process[i].burst,process[i].wait,process[i].finish,process[i].turnaround,process[i].ratio);
        tavg+=process[i].turnaround;
        wavg+=process[i].wait;
        printf("\n\n");
    }
    tavg/=n;
    wavg/=n;
    printf("Average waiting timeis %f\n Average turnarounf time is %f",wavg,tavg);
}
