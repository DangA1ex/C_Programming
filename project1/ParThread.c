#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

//Struct to hold info to pass in multiple arguemenst to pthread
struct Info
{
    int limit;
    //The number of symbols
    int size;
    //The plus or minus symbol
    char *symbol;
    //Handles closing the file so all threads can access it
};

void putCompression(FILE *out, int repeatedCount, char previousChar)
{
    if (repeatedCount >= 16)
    {
        if (previousChar == '0')
        {
            putc('-', out);
            fprintf(out, "%d", repeatedCount);
            putc('-', out);
        }
        else if (previousChar == '1')
        {
            putc('+', out);
            fprintf(out, "%d", repeatedCount);
            putc('+', out);
        }
    }
}

void initiateCompression(void *arg)
{
    struct Info *input = (struct Info *)arg;
    // Handle file output
    FILE *out;
    out = fopen(argv[2], "w");
    char previousChar = ' ';
    char currentChar;
    int repeatedCount = 0;
    int tempSharedIter = input->size;

    // Used for 1's compression
    for (int i = 0; i <= input->limit; i++)
    {
        currentChar = input->symbol[tempSharedIter];
        if (currentChar != previousChar)
        {
            if (repeatedCount >= 16)
            {
                putCompression(out, repeatedCount, previousChar);
            }
            else
            {
                for (int i = 0; i < repeatedCount; i++)
                {
                    putc(previousChar, out);
                }
            }
            repeatedCount = 0;
        }
        repeatedCount++;
        previousChar = currentChar;
        tempSharedIter++;
    }

    // For putting repeated 0's
    if (repeatedCount != 0)
    {
        if (repeatedCount >= 16)
        {
            putCompression(out, repeatedCount, previousChar);
        }
        else
        {
            for (int i = 0; i < repeatedCount; i++)
            {
                putc(previousChar, out);
            }
        }
    }
    
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    // Handle file input and display selected files
    FILE *in;
    printf("<-----------------------------------------------------------> \n");
    printf("                _                             \n");
    printf("               | |                             \n");
    printf("__      __ ___ | |  ___  ___   _ __ ___    ___ \n");
    printf("\\ \\ /\\ / // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\ \n");
    printf(" \\ V  V /|  __/| || (__| (_) || | | | | ||  __/\n");
    printf("  \\_/\\_/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|\n");
    printf("\n");
    printf("CS4440 MyCompression Program\n");
    printf("Input File: %s \n", argv[1]);
    printf("Output File: %s \n", argv[2]);
    printf("<-----------------------------------------------------------> \n");
    printf("Input string: \n");

    in = fopen(argv[1], "r");

    char tempChar;
    char previousChar = ' ';
    char currentChar;
    int charCounter = 0;
    int numOfParts = 0;
    double charLimit = 36;

    // Find the Char Length of the Input File
    while ((tempChar = fgetc(in)) != EOF)
    {
        currentChar = tempChar;
        printf("%c", currentChar);
        charCounter++;
        previousChar = currentChar;
    }

    // Divide the Char Limit in Input file by the set Char Limit
    // for the number of forks.
    numOfParts = (charCounter / charLimit);

    char inputString[charCounter];
    char tempString[charCounter];

    // Used to reset the fgetc
    rewind(in);

    // Used fscanf here to ignore blank spaces for better
    // compression in output file.
    while (fscanf(in, "%s\n", tempString) != EOF)
    {
        strcat(inputString, tempString);
    }

    //Intializes a struct array for storing all the information
    struct Info input[numOfParts];

    //Create thread IDs
    pthread_t tids[numOfParts];

    //Creates multiple threads
    for (int i = 0; i < numOfParts; i++)
    {
        input[i].limit = charLimit;
        input[i].size = charLimit * i;
        input[i].symbol = strdup(inputString);
        pthread_create(&tids[i], NULL, initiateCompression, &input[i]);
    }

    //Closes multiple threads
    for (int i = 0; i < 10; i++)
    {
        pthread_join(tids[i], NULL);
    }
}