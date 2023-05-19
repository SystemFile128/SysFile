#include<stdio.h>
#include<stdlib.h>


int main(){
    int n;
    printf("Enter the number of page table entries: ");
    scanf("%d",&n);
    int page_table[n];
    for(int i=0;i<n;i++){
        printf("Enter frame_no for page %d: ",i);
        scanf("%d",&page_table[i]);
    }
    int page_size;
    printf("Enter the page size: ");
    scanf("%d",&page_size);
    int LA;
    int choice = 1;
    while(choice == 1){
        printf("Enter the logical address: ");
        scanf("%d",&LA);
        int PA;
        int PTE;
        PTE = LA/page_size;
        if(PTE>n-1){
            printf("Page fault\n");
        }else{
            PA = page_table[PTE]*page_size+LA%page_size;
        }
        printf("Physical addresss corresponding tob given logical address is: %d\n",PA);
        printf("Enter 1 to check more: ");
        scanf("%d",&choice);
    }
   

return 0;
}