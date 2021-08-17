#include <stdio.h>

#include "cipher.h"

int main()
{
    int  flag_start[100], flag_length;
    char input[10000], key[1000], grid[5][5];
    
    printf("Enter message to be encrypted: ");
    scanf("%[^\n]s", input);

    flag_length = inputFormat(input, flag_start);
    printf("Formatted message: %s\n", input);
    //printf("%lu\n", strlen(input));

    int flag[flag_length];
    for (int i = 0; i < flag_length; i++)
    {
        flag[i] = flag_start[i];
        //printf("%d ", flag[i]);
    };

    printf("\nEnter keyword: ");
    scanf("%s", key);

    keyFormat(key);
    printf("Formatted key: %s\n", key);
    //printf("%lu\n", strlen(key));

    makeGrid(key, grid);
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

    encrypt(grid, input);
    printf("Encrypted message: %s\n", input);
    //printf("%lu\n", strlen(input));

    decrypt(grid, input);
    outputFormat(input, flag, flag_length);
    printf("Decrypted message: %s\n", input);
    //printf("%lu\n", strlen(input));


    return 0;
}