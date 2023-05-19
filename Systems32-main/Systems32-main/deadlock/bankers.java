import java.util.*;
public class Bankers_Algorithm {
    public static void main(String args[])
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number of processes:");
        int p=sc.nextInt();
        System.out.println("Enter the number of resources:");
        int r=sc.nextInt();
        int allocation[][]=new int[p][r];
        int max[][]=new int[p][r];
        int need[][]=new int[p][r];
        int available[]=new int[r];
        System.out.println("Enter the content for the allocation matrix");
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<r;j++)
            {
                allocation[i][j]=sc.nextInt();
            }
        }
        System.out.println("The allocation matrix is");
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<r;j++)
            {
                System.out.print(allocation[i][j]+" ");
            }
            System.out.println();
        }

        System.out.println("Enter the content for the max matrix");
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<r;j++)
            {
                max[i][j]=sc.nextInt();
            }
        }

        System.out.println("The max matrix is");
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<r;j++)
            {
                System.out.print(max[i][j]+" ");
            }
            System.out.println();
        }


        for(int i=0;i<p;i++)
        {
            for(int j=0;j<r;j++)
            {
               need[i][j]=max[i][j]-allocation[i][j];
            }
        }

        System.out.println("The need matrix is");
        for(int i=0;i<p;i++)
        {
            for(int j=0;j<r;j++)
            {
                System.out.print(need[i][j]+" ");
            }
            System.out.println();
        }

        System.out.println("Enter the available resource:");
        for(int i=0;i<available.length;i++)
        {
            available[i]=sc.nextInt();
        }
        System.out.println("The available resources:");
        for(int i=0;i<available.length;i++)
        {
            System.out.print(available[i]+" ");
        }
        System.out.println();

        int finish[]=new int[p];
        int ans[]=new int[p];
        int flg=0;
        int pos=0;

        for(int k=0;k<p;k++)
        {
            for(int i=0;i<p;i++)
            {
                if(finish[i]==0) {
                    flg = 0;
                    for (int j = 0; j < r; j++) {
                        if (need[i][j] > available[j]) {
                            flg = 1;
                            break;
                        }
                    }


                    if (flg == 0) {
                        ans[pos++] = i;
                        for (int y = 0; y < r; y++) {
                            available[y] += allocation[i][y];
                        }
                        finish[i] = 1;
                    }
                }
            }
        }

        System.out.println("The finish matrix(1-Process is completed ,0-Process is incomplete");
        for(int i=0;i<p;i++)
        {
            System.out.print(finish[i]+" ");
        }
        System.out.println();

        System.out.println("The final available resources");
        for(int i=0;i<r;i++)
        {
            System.out.print(available[i]+" ");
        }
        System.out.println();
        int flg1=0;
        for(int i=0;i<p;i++)
        {
            if(finish[i]==0)
            {
                flg1=1;
                System.out.println("The system is in deadlock");
                break;
            }
        }
        if(flg1==0)
        {
            System.out.println("The system is in safe state");
            for(int i=0;i<p;i++)
            {
                System.out.print("P"+ans[i]+" ");
            }

        }
    }
}
