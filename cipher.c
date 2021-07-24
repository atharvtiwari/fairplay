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

int keyFormat(char key[]); //removes repeated characters from string
int makeGrid(char formatted_key[], int row, int col, char grid[row][col]); //makes grid with formatted key consisting of only unique letters
int inputFormat(char input[]); //formats input according to decided conditions
int encrypt(int grid[], char formatted_string[]); //encrypts formatted string wrt a given grid
int decrypt(int grid[], char encrypted_string[]); //decrypts encrypted string wrt a given grid

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

int makeGrid(char formatted_key[], int row, int col, char grid[row][col]) //string to 2d array
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

int inputFormat(char input[])
{
    int len = strlen(input);

    for (int i = 0; i < len; i++) // input to uppercase
    {
        char ch = input[i];
        input[i] = toupper(ch);
    }
    
    char temp[len];
    int i = 0, j = 0;
    while (input[i] != '\0') // remove whitespaces and punctuation
    {
        if (!ispunct(input[i]) && !isspace(input[i]))
        {
            temp[j++] = input[i];
        }
        i++;
    }
    temp[j] = '\0'; // truncate to remove junk
    len = j;

    //printf("%s %d\n", temp, len);
    
    char string[10000];
    strcpy(string, temp);

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

    return 0;
}