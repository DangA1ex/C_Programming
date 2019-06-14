#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// Used to put the characters into the output file
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

void initiateCompression(int limit, int size, char *inChar, FILE *out)
{
    char previousChar = ' ';
    char currentChar;
    int repeatedCount = 0;
    int tempSharedIter = size;

    // Used for 1's compression
    for (int i = 0; i <= limit; i++)
    {
        currentChar = inChar[tempSharedIter];
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
    if (repeatedCount != 0) {
        if (repeatedCount >= 16) {
            putCompression(out, repeatedCount, previousChar);
        }
        else {
            for (int i = 0; i < repeatedCount; i++) {
                putc(previousChar, out);
            }
        }
    }
}

int main(int argc, char **argv)
{
    pid_t pid;
    FILE *in;
    in = fopen(argv[1], "r");
    FILE *out;
    out = fopen(argv[2], "w");

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

    // Fork Logic using number of parts from earlier to
    // decide how many forks to run.
    for (int i = 0; i < numOfParts; i++)
    {
        pid = fork();

        // Child Fork
        if (pid == 0)
        {
            printf("Child Process Start %d\n", getpid());
            initiateCompression(charLimit, (charLimit * i), inputString, out);
            exit(0);
        }
        // Parent fork
        else
        {
            printf("Parent Process Waiting\n");
            wait(NULL);
            printf("Child is finished and Parent will now finish\n");
        }
    }

    return 0;
}