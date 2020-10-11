#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
bool is_digit(string s);

int main(int argc, string argv[])
{
    if (argc != 2 || atoi(argv[1]) < 0 || !is_digit(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //convert argv[1] into an int
        int key = atoi(argv[1]);
        //get the user plaintext
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        //iterate on each char until we reach the lenght of the string
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            {
                //if the char is lowercase, add the key and make sure to stay in lower
                printf("%c", (plaintext[i] - 'a' + key) % 26 + 'a');
            }
            else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
                //if the char is uppercase, add the key and make sure to stay upper
                printf("%c", (plaintext[i] - 'A' + key) % 26 + 'A');
            }
            else
            {
                //if char is not a letter, print the same char
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;
    }
}

//fonction to know if all chars of a strings are digits
bool is_digit(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
        if (!isdigit(s[i]))
        {
            return false;
        }
    return true;
}