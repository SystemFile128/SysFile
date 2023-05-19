/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int n,i,j;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int burst[n],arrival[n],waiting[n],turnaround[n];
    for( i=0;i<n;i++)
    {
        printf("Enter the arrival time for Process %d: ",i+1);
        scanf("%d",&arrival[i]);
        printf("Enter the burst time for Process %d: ",i+1);
        scanf("%d",&burst[i]);
    }
    float waiting_avt=0.0;
    float turnaround_avt=0.0;
    waiting[0]=0;
    for(i=0;i<n;i++)
    {
        waiting[i]=0;
        for(j=0;j<i;j++)
        {
            waiting[i]+=burst[j];
        }
        waiting[i]-=arrival[i];
        if(waiting[i]<0)
        {
            waiting[i]=0;
        }
    }
    
    for(i=0;i<n;i++)
    {
        turnaround[i]=burst[i]+waiting[i];
        waiting_avt+=waiting[i];
        turnaround_avt+=turnaround[i];
    }
    int completion[n];
    for(i=0;i<n-1;i++)
    {
        completion[i]=completion[i-1]+burst[i];
    }
    
    waiting_avt/=n;
    turnaround_avt/=n;
    
    printf("\n\nProcess\tBurstTime\tArrivalTime\tWaitingTime\tTurnaroundTime\tCompletionTime \n");
    

    for(i=0; i<n; i++) {
        printf("\n%d\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d", i+1, burst[i], arrival[i], waiting[i], turnaround[i],completion[i]);
    }

    printf("\n\nAverage Waiting Time: %.2f", waiting_avt);
    printf("\nAverage Turnaround Time: %.2f", turnaround_avt);

    return 0;
}
