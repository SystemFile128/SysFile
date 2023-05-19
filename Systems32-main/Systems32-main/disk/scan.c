#include<stdio.h>
#include<stdlib.h>

int no_of_tracks;

int main(){
    printf("Enter the number of request tracks: ");
    scanf("%d",&no_of_tracks);
    int sec_track[no_of_tracks][2];
    for(int i=0;i<no_of_tracks;i++){
        printf("Enter the %d(th/st/nd/rd) track: ",i+1);
        scanf("%d",&sec_track[i][0]);
    }
    for(int i=0;i<no_of_tracks;i++){
        sec_track[i][1]=0;
    }
    int head;
    printf("Enter the head: ");
    scanf("%d",&head);
    
    for(int i=0;i<no_of_tracks-1;i++){
        for(int j=0;j<no_of_tracks-i-1;j++){
            if(sec_track[j][0]<sec_track[j+1][0]){
                int temp = sec_track[j][0];
                sec_track[j][0]=sec_track[j+1][0];
                sec_track[j+1][0]=temp;
            }
        }
    }

    int flag = 0;
    for(int i=0;i<no_of_tracks;i++){
        if(sec_track[i][0]<head){
            flag = i;
            break;
        }
    }
    
    int l = 0;
    int r = flag-1;
    while(l<r){
        int temp = sec_track[l][0];
        sec_track[l][0]=sec_track[r][0];
        sec_track[r][0]=temp;
        l++;
        r--;
    }

    printf("Next track to be traversed  No. of tracks to be traversed\n");
    for(int i=0;i<no_of_tracks;i++){
        printf("\t\t%d\t\t",sec_track[i][0]);
        printf("\t\t%d\t\t",sec_track[i][1]);
        printf("\n");
    }

    for(int i=0;i<no_of_tracks;i++){
        sec_track[i][1]=abs(head - sec_track[i][0]);
        head=sec_track[i][0];
    }

    int total_seek_time;
    for(int i=0;i<no_of_tracks;i++){
        total_seek_time+=sec_track[i][1];
    }

    printf("Next track to be traversed  No. of tracks to be traversed\n");
    for(int i=0;i<no_of_tracks;i++){
        printf("\t\t%d\t\t",sec_track[i][0]);
        printf("\t\t%d\t\t",sec_track[i][1]);
        printf("\n");
    }

    printf("Total seek time: %d\n",total_seek_time);
    float avg_s_time = (float)total_seek_time/no_of_tracks;
    printf("Average seek time is %f: ",avg_s_time); 

    return 0;
}

