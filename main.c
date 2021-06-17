#include <stdio.h>

#include "cipher.h"

int main()
{
    const int row = 5, col = 5;
    char key[26], grid[row][col];

    printf("Enter keyword: ");
    scanf("%s", key);

    keyFormat(key);
    printf("Formatted key: %s\n", key);

    makeGrid(key, row, col, grid);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}