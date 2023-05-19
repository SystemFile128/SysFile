#include<stdio.h>
#include<limits.h>
int main(){
    int frames, pages, i, j, k, l, hit=0, fault=0, max_dist, max_frame, flag;
    int reference_string[100], mem_layout[100][100], distance[100];
    printf("\nEnter the number of frames: ");
    scanf("%d",&frames);
    printf("\nEnter the number of pages: ");
    scanf("%d",&pages);
    printf("\nEnter the reference string: ");
    for(i=0;i<pages;i++){
        scanf("%d",&reference_string[i]);
    }
    for(i=0;i<frames;i++){
        mem_layout[i][0]=-1;
    }
    for(i=0;i<pages;i++){
        hit=0;
        for(j=0;j<frames;j++){
            if(mem_layout[j][0]==reference_string[i]){
                hit=1;
                break;
            }
        }
        if(hit==0){
            fault++;
            flag=0;
            for(j=0;j<frames;j++){
                if(mem_layout[j][0]==-1){
                    mem_layout[j][0]=reference_string[i];
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                for(j=0;j<frames;j++){
                    distance[j]=INT_MAX;
                    for(k=i+1;k<pages;k++){
                        if(reference_string[k]==mem_layout[j][0]){
                            distance[j]=k-i;
                            break;
                        }
                    }
                }
                max_dist=-1;
                for(j=0;j<frames;j++){
                    if(distance[j]>max_dist){
                        max_dist=distance[j];
                        max_frame=j;
                    }
                }
                mem_layout[max_frame][0]=reference_string[i];
            }
        }
        for(j=0;j<frames;j++){
            mem_layout[j][i+1]=mem_layout[j][i];
        }
    }
    printf("\nTotal Page Faults: %d",fault);
    return 0;
}