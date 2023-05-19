#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char M[300][4];
void init()
{
    
}
int allocate()
{
    srand(time(0));
    return (rand()% 30);
}
int addmap(int VA)
{
    if(VA>0 && VA<100)
    {
        int pte = allocate();
        pte = pte*10+VA/10;
        printf("Taking page table entry as %d",pte);
        int RA = allocate();//generating frame number for M[pte]
        printf("\n M[pte] is %d",RA);
        RA = RA*10 + VA%10;
    }
    else
    return -1;
}
int main()
{
    printf("Enter data for data card (has to be 10 characters only) ");
    char data[10];
    scanf("%s",&data);
    for(int i=0;i<10;i++)
    printf("%c",data[i]);
    printf("Enter a virtual address to be mapped");
    int x;
    scanf("%d",&x);
    int y = addmap(x);
    if(y!=-1)
    printf("\nCorresponding real address is %d",y);
    else
    printf("Virtual address provided is wrong");
    int k=0;
    for(int i=y;i<y+3;i++)
    {
        for(int j=0;j<4;j++)
        {
            M[i][j] = data[k];
            k++;
            if(k==10)
            break;
        }
    }
    printf("\n Memory is \n");
    for(int i=0;i<300;i++)
    {
        printf("M[%d]:",i);
        for(int j=0;j<4;j++)
        printf("%c",M[i][j]);
        printf("\n");
    }
    return 0;
}
