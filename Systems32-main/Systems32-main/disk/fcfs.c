#include<stdio.h>
#include<stdlib.h>
int no_of_tracks;
int main()
{
    printf("Enter the number of tracks: ");
    scanf("%d",&no_of_tracks);
    int sec[no_of_tracks][2];
    for(int i=0;i<no_of_tracks;i++)
    {
        printf("Enter track no %d: ",i+1);
        scanf("%d",&sec[i][0]);
    }
    int head;
    printf("Enter the head: ");
    scanf("%d",&head);
    int total_seek_time=0;
    for(int i=0;i<no_of_tracks;i++)
    {
        sec[i][1]=abs(head-sec[i][0]);
        head=sec[i][0];
    }
    for(int i=0;i<no_of_tracks;i++)
    {
        total_seek_time+=sec[i][1];
    }
    printf("Next track to be traversed No of tracks to be traveraed \n");
    for(int i=0;i<no_of_tracks;i++)
    {
        printf("\t\t%d\t\t",sec[i][0]);
        printf("\t\t%d\t\t",sec[i][1]);
        printf("\n");
    }
    float avg=(float)total_seek_time/no_of_tracks;
    printf("Average seek time: %.2f \n",avg);
    return 0;
}