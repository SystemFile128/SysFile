#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[4];
char IR[4];
char M[100][4];
char data[5];

void read(int i) {
    int k = 0;
    for (int m = i; m < (i + 4); m++) {
        buffer[k] = IR[m]; // extracting that instruction in that row of buffer
        k++;
        if (k == 4)
            break;
    }
    int x = (buffer[2] - '0') * 10 + (buffer[3] - '0');
    int l = 0;
    for (int i = x; i < (x + 3); i++) {
        for (int j = 0; j <= 3; j++) {
            M[i][j] = data[l];
            l++;
            if (l ==10 )
                break;
        }
    }

    printf("Memory is:\n");
    for (int i = 0; i < 100; i++) {
        printf("M[%d]: ", i);
        for (int j = 0; j <= 3; j++)
            printf("%c", M[i][j]);
        printf("\n");
    }
}

int main() {
    printf("Enter data of 10 letters: ");
    scanf("%s", data);
    
    printf("Enter the instruction: ");
    scanf("%s", IR);

    for (int i = 0; i < 4; i++) {
        if (IR[i] == 'P') {
            printf("Put data command found\n");
            read(i);
        }
    }

    return 0;
}

