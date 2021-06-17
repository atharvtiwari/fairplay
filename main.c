#include <stdio.h>

#include "cipher.h"

int main()
{
    const int row = 5, col = 5;
    char key[1000], grid[row][col];

    printf("Enter keyword: ");
    scanf("%s", key);

    keyFormat(key);
    //printf("%I64d\n", strlen(key));
    printf("Formatted key: %s\n", key);

    makeGrid(key, row, col, grid);
    printf("Key grid:\n\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t");
        for (int j = 0; j < 5; j++)
        {
            printf("%c  ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}