#include <stdio.h>
#define MAX_PAGES 100

int findLRU(int time[], int n){
    int i, min = time[0], pos = 0;
    for(i=1;i<n;i++){
        if(time[i]<min){
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main(){
    int pages[MAX_PAGES], frames, n, i, j, k, faults = 0, pos;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for(i=0;i<n;i++){
        scanf("%d", &pages[i]);
    }
    int mem[frames], time[frames];
    for(i=0;i<frames;i++){
        mem[i] = -1;
        time[i] = 0;
    }
    for(i=0;i<n;i++){
        for(j=0;j<frames;j++){
            if(mem[j]==pages[i]){
                time[j] = i+1;
                break;
            }
        }
        if(j==frames){
            pos = findLRU(time, frames);
            mem[pos] = pages[i];
            time[pos] = i+1;
            faults++;
        }
        printf("\n");
        for(k=0;k<frames;k++){
            printf("%d\t", mem[k]);
        }
    }
    printf("\nTotal Page Faults: %d", faults);
    return 0;
}