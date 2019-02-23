#include <stdio.h>
#include <pthread.h>

//Struct to hold info to pass in multiple arguemenst to pthread
struct Info
{
    //Handles closing the file so all threads can access it
    File *out;
    //The number of symbols
    int count;
    //The plus or minus symbol
    char symbol;
};

//I changed the arguement to make it work with pthreads
void MyCompression(void *arg)
{
    //Allows me to access the values stored in the arguement
    struct Info *input = (struct Info *)arg;
    //input->counts allows me to take what is stored in input count
    if (input->count >= 16)
    {
        //input->symbol allows me to access what is stored in input symbol
        if (input->symbol == '0')
        {
            //input->out allows me to access what is stroed in input *out
            putc('-', input->out);
            fprintf(input->out, "%d", repeatedCount);
            putc('-', input->out);
        }
        else if (input->symbol == '1')
        {
            putc('+', input->out);
            fprintf(input->out, "%d", repeatedCount);
            putc('+', input->out);
        }
    }
    //This exits the pthread
    pthread.exit(0);
}

int main(int argc, char **argv)
{
    //Create thread IDs
    pthread_t tids[];

    //Creates multiple threads
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&tids[i], NULL, MyCompression, &input);
    }

    //Intializes a struct array for storing all the information
    struct Info input[];

    // Handle file input and display selected files
    FILE *fp;
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

    fp = fopen(argv[1], "r");

    // Handle file output
    FILE *out;
    out = fopen(argv[2], "w");

    char tempChar;
    char previousChar = ' ';
    char currentChar;
    int repeatedCount = 0;

    while ((tempChar = fgetc(fp)) != EOF)
    {
        currentChar = tempChar;
        printf("%c", currentChar);
        if (currentChar != previousChar)
        {
            if (repeatedCount >= 16)
            {
                //Set the struct Info input values
                input.out = out;
                input.count = repeatedCount;
                input.symbol = previousChar;

                MyCompression(out, repeatedCount, previousChar);
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
    }

    //Closes multiple threads
    for (int i = 0; i < 10; i++)
    {
        pthread_join(&tids[i], NULL);
    }


    fclose(out);
}