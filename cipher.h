#include <ctype.h>
#include <string.h>

int keyFormat(char key[]); //removes repeated characters from string
int makeGrid(char formatted_key[], char grid[5][5]); //makes grid with formatted key consisting of only unique letters
int inputFormat(char input[], int flag[]); //formats input according to decided conditions
int search(char grid[5][5], char a, char b, int arr[]); //searches for pair of characters
int encrypt(char grid[5][5], char formatted_string[]); //encrypts formatted string wrt a given grid
int decrypt(char grid[5][5], char encrypted_string[]); //decrypts encrypted string wrt a given grid
int outputFormat(char decrypted_string[], int flag[], int flag_length); //tries to clean up the decrypted output