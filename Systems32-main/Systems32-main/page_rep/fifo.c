#include<stdio.h>
int main(){
    int frames, pages, i, j, hit=0, fault=0, counter=0;
    int reference_string[100], mem_layout[100][100];
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
                mem_layout[j][i+1]=1;
                break;
            }
        }
        if(hit==0){
            mem_layout[counter][0]=reference_string[i];
            fault++;
            for(j=0;j<frames;j++){
                mem_layout[counter][j+1]=0;
            }
            counter++;
            if(counter==frames){
                counter=0;
            }
        }
        printf("\n");
        for(j=0;j<frames;j++){
            printf("%d\t",mem_layout[j][i]);
        }
    }
    printf("\nTotal Page Faults: %d",fault);
    return 0;
}