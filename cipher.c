/* Key
Enter keyword (preferably without repeated letters): qwerty
Formatted key: QWERTY

Enter keyword (preferably without repeated letters): hello
Formatted key: HELO
*/

/* Grid
Formatted key: QWERTY
Q   W   E   R   T
Y   A   B   C   D
F   G   H   I   K
L   M   N   O   P
S   U   V   X   Z

Formatted key: HELO
H   E   L   O   A
B   C   D   F   G
I   K   M   N   P
Q   R   S   T   U
V   W   X   Y   Z
*/

/* Input
Enter string to be encrypted: qwerty
Formatted string: QWERTY

Enter string to be encrypted: hell
Formatted string: HELXLX

Enter string to be encrypted: james
Formatted string: JAMESX

Enter string to be encrypted: hello
Formatted string: HELXLO

Enter string to be encrypted: helllo
Formatted string: HELXLXLO

Enter string to be encrypted: haxx
Formatted string: HAXQXQ

Enter string to be encrypted: haxxo
Formatted string: HAXQXO

Enter string to be encrypted: hello world
Formatted string: HELXLOWORLDX
*/

/* Encryption
Take key input and format it using the above algorithm for keys, removing repeated characters.
Form a grid using the above algorithm.
Take input to be encrypted and format it using the above algorithm for strings.

1> take letters in pairs from formatted input
ex: QWERTY --> QW ER TY

2> if the pair of letters is in the same column in the grid, shift down
ex: QS --> YQ
Q
Y
F
L
S

3> if the pair of letters is in the same row in the grid, shift right
ex: KP --> MI
I   K   M   N   P

4> if the pair of letters is the diagonal of a rectangle, switch to the other diagonal horizontally
ex: DS --> GQ
D   F   G
I   K   M
Q   R   S

5> join all pairs and return encrypted string
*/

/* Decryption
Take key input and format it using the above algorithm for keys, removing repeated characters
Form a grid using the above algorithm
Take encrypted input

1> take letters in pairs from formatted input
ex: QWERTY --> QW ER TY

2> if the pair of letters is in the same column in the grid, shift up
ex: YQ --> QS
Q
Y
F
L
S

3> if the pair of letters is in the same row in the grid, shift left
ex: MI --> KP
I   K   M   N   P

4> if the pair of letters is the diagonal of a rectangle, switch to the other diagonal horizontally
ex: GQ --> DS
D   F   G
I   K   M
Q   R   S

5> join all pairs and return encrypted string
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "cipher.h"

#define alphabet "ABCDEFGHIKLMNOPQRSTUVWXYZ"

int keyFormat(char key[])
{
    for (int i = 0; i < strlen(key); i++) // key to uppercase
    {
        char ch = key[i];
        key[i] = toupper(ch);
    }

    char string[1000];
    strcpy(string, key);
    strcat(string, alphabet);

    int i, j , k = 0;
    for (i = 0; i < strlen(string); i++) // remove repeated characters
  	{
  		for (j = 0; j < i; j++)
  		{
  			if (string[j] == string[i])  
			{
                break;
 			}
		}
        if (j == i && string[j] != 'J')
        {
            string[k++] = string [i];
        }
	}
    
    strcpy(key, string);

    key[25] = '\0'; // truncate formatted key to remove junk

    return 0;
}

int makeGrid(char formatted_key[], char grid[5][5]) //string to 2d array
{
    int i = 0;
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            grid[row][col] = formatted_key[i];
            i++;
        }
    }

    return 0;
}

int inputFormat(char input[], int flag[])
{
    int len = strlen(input);

    for (int i = 0; i < len; i++) // input to uppercase
    {
        char ch = input[i];
        input[i] = toupper(ch);
    }
    
    char temp[len];
    int i = 0, j = 0, k = 0, l = 0;
    while (input[i] != '\0') // remove whitespaces and punctuation
    {
        if (!ispunct(input[i]) && !isspace(input[i]))
        {
            temp[j++] = input[i];
        }
        else
        {
            flag[k++] = i - l;
            l++;
        }
        i++;
    }
    temp[j] = '\0'; // truncate to remove junk
    len = j;

    //printf("%s %d %d %d\n", temp, len, flag_length, flag[0]);

    i = 0, j = 0;
    while (temp[i] != '\0') //replace 'J's with 'I's
    {
        if (temp[i] == 'J')
        {
            temp[i] = 'I';
        }
        i++;
    }
    
    char string[10000];
    strcpy(string, temp);

    i = 0, j = 0;
    if (len % 2 == 0) // even number of characters
    {
        for (int i = 1; i <= len; i += 2) // taken in pairs
        {
            if (string[i] == string[i - 1]) //repeating character
            {
                for (int j = len - 1; j >= i; j--)
                {
                    string[j + 1] = string[j];
                }
                len++;
                for (int j = len; j > i; j--)
                {
                    string[j] = string[j - 1];
                }
                len++;
                if (string[i] == 'X')
                {
                    string[i] = 'Q';
                    string[i + 2] = 'Q';
                }
                else
                {
                    string[i] = 'X';
                    string[i + 2] = 'X';
                }
            }
        }
    }
    else // odd number of characters
    {
        string[len] = 'X'; // adding 'X' at the end to make even
        len++;
        for (int i = 1; i <= len; i += 2) // taken in pairs
        {
            if (string[i] == string[i - 1]) //repeating character
            {
                for (int j = len - 1; j > i; j--)
                {
                    string[j] = string[j - 1];
                }
                if (string[i] == 'X')
                {
                    string[i] = 'Q';
                }
                else
                {
                    string[i] = 'X';
                }
                string[len] = 'X'; // adding 'X' at the end to make odd
                len++;
            }
        }
    }

    if (len % 2 == 1)
    {
        string[len - 1] = '\0'; // truncate to remove junk
    }

    strcpy(input, string);

    return k;
}

int search(char grid[5][5], char a, char b, int arr[])
{ 
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (grid[i][j] == a)
            {
                arr[0] = i;
                arr[1] = j;
            }
            else if (grid[i][j] == b)
            {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }

    return 0;
}

int encrypt(char grid[5][5], char formatted_string[])
{
    int arr[4];
 
    for (int i = 0; i < strlen(formatted_string); i += 2) {
        search(grid, formatted_string[i], formatted_string[i + 1], arr);
        if (arr[0] == arr[2]) {
            formatted_string[i] = grid[arr[0]][(arr[1] + 1) % 5];
            formatted_string[i + 1] = grid[arr[0]][(arr[3] + 1) % 5];
        }
        else if (arr[1] == arr[3]) {
            formatted_string[i] = grid[(arr[0] + 1) % 5][arr[1]];
            formatted_string[i + 1] = grid[(arr[2] + 1) % 5][arr[1]];
        }
        else {
            formatted_string[i] = grid[arr[0]][arr[3]];
            formatted_string[i + 1] = grid[arr[2]][arr[1]];
        }
    }

    return 0;
}

int decrypt(char grid[5][5], char encrypted_string[])
{
    int arr[4];
    
    for (int i = 0; i < strlen(encrypted_string); i += 2)
    {
        search(grid, encrypted_string[i], encrypted_string[i + 1], arr);
        if (arr[0] == arr[2])
        {
            if (arr[1] == 0 && arr[3] == 0)
            {
                encrypted_string[i] = grid[arr[0]][4];
                encrypted_string[i + 1] = grid[arr[0]][4];
            }
            else if (arr[1] == 0)
            {
                encrypted_string[i] = grid[arr[0]][4];
                encrypted_string[i + 1] = grid[arr[0]][(arr[3] - 1) % 5];
            }
            else if (arr[3] == 0)
            {
                encrypted_string[i] = grid[arr[0]][(arr[1] - 1) % 5];
                encrypted_string[i + 1] = grid[arr[0]][4];
            }
            else
            {
                encrypted_string[i] = grid[arr[0]][(arr[1] - 1) % 5];
                encrypted_string[i + 1] = grid[arr[0]][(arr[3] - 1) % 5];
            }
        }
        else if (arr[1] == arr[3])
        {
            if (arr[2] == 0 && arr[4] == 0)
            {
                encrypted_string[i] = grid[4][arr[1]];
                encrypted_string[i + 1] = grid[4][arr[1]];
            }
            else if (arr[0] == 0)
            {
                encrypted_string[i] = grid[4][arr[1]];
                encrypted_string[i + 1] = grid[(arr[2] - 1) % 5][arr[1]];
            }
            else if (arr[2] == 0)
            {
                encrypted_string[i] = grid[(arr[0] - 1) % 5][arr[1]];
                encrypted_string[i + 1] = grid[4][arr[1]];
            }
            else
            {
                encrypted_string[i] = grid[(arr[0] - 1) % 5][arr[1]];
                encrypted_string[i + 1] = grid[(arr[2] - 1) % 5][arr[1]];
            }
        }
        else
        {
            encrypted_string[i] = grid[arr[0]][arr[3]];
            encrypted_string[i + 1] = grid[arr[2]][arr[1]];
        }
    }

    return 0;
}

int outputFormat(char decrypted_string[], int flag[], int flag_length)
{
    int i = 0, j = 0, len = strlen(decrypted_string);
    char temp[len], temp2[len];
    
    while (decrypted_string[i] != '\0')
    {
        if (decrypted_string[i] == 'X' && decrypted_string[i - 1] == decrypted_string[i + 1]);
        else if (decrypted_string[i] == 'X' && decrypted_string[i - 2] == 'X'&& decrypted_string[i - 1] == decrypted_string[i - 3]);
        else
        {
            temp[j++] = decrypted_string[i];
        }
        i++;
    }
    temp[j] = '\0'; // truncate to remove junk
    len = j;

    i = 0, j = 0;
    while (temp[i] != '\0')
    {
        for (int k = 0; k < flag_length; k++)
        {
            if (i == flag[k])
            {
                if (!isspace(temp2[j - 1]))
                {
                    temp2[j++] = ' ';
                }
            }
        }
        temp2[j++] = temp[i];
        i++;
    }
    temp2[j] = '\0'; // truncate to remove junk
    len = j;

    strcpy(decrypted_string, temp2);

    return 0;
}