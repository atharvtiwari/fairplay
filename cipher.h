#include <ctype.h>
#include <string.h>

int keyFormat(char key[]);
int makeGrid(char formatted_key[], int grid[5][5]);
int inputFormat(char input[]);
int encrypt(int grid[], char formatted_string[]);
int decrypt(int grid[], char encrypted_string[]);