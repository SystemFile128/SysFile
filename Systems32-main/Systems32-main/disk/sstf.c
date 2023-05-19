#include<stdio.h>
#include<stdlib.h>

int no_of_tracks;

int main()
{
    printf("Enter the no of request tracks: ");
    scanf("%d",&no_of_tracks);
    int sec[no_of_tracks][2];
    for(int i=0;i<no_of_tracks;i++)
    {
        printf("Enter track no %d: ",i+1);
        scanf("%d",&sec[i][0]);
    }
    for(int i=0;i<no_of_tracks;i++)
    {
        sec[i][1]=0;
    }
    int head;
    printf("Enter the head: ");
    scanf("%d",&head);
    
    int temp[no_of_tracks][2];
    int j=0;
    for(int i=0;i<no_of_tracks;i++)
    {
        temp[i][1]=0;
    }
    int headt=head;
    int flag;
    int count=0;
    int min;
    while(count<=no_of_tracks)
    {
        min=9999;
        for(int i=0;i<no_of_tracks;i++)
        {
            if(abs(sec[i][0]-headt)<min && sec[i][0]!=-1)
            {
                min=abs(sec[i][0]-headt);
                flag=i;
            }
        }
        count++;
        headt=sec[flag][0];
        temp[j][0]=headt;
        sec[flag][0]=-1;
        j++;
    }
    
    
    for(int i=0;i<no_of_tracks;i++)
    {
        temp[i][1]=abs(head-temp[i][0]);
        head=temp[i][0];
        
    }
    
    int total_seek_time=0;
    for(int i=0;i<no_of_tracks;i++)
    {
        total_seek_time+=temp[i][1];
    }
    printf("Next track to be traversed No of tracks to be traversed \n");
    for(int i=0;i<no_of_tracks;i++)
    {
        printf("\t\t%d\t\t",temp[i][0]);
        printf("\t\t%d\t\t",temp[i][1]);
        printf("\n");
    }
    
    printf("Total seek time: %d \n",total_seek_time);
    float avg_time=(float)total_seek_time/(no_of_tracks);
    printf("Average seek time is: %.2f \n",avg_time);
    return 0;
}