#include <stdio.h>

#include "cipher.h"

int main()
{
    char key[30];
    int grid[5][5];

    printf("Enter keyword (preferably without repeated letters): ");
    scanf("%s", key);

    keyFormat(key);
    printf("\nFormatted key: %s\n\n", key);

    makeGrid(key, grid[5][5]);
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