#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Used to print output characters into the specificed OUT file.
void MyCompression(FILE *out, int repeatedCount, char previousChar)
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

int main(int argc, char **argv)
{
    // Pipe fd
    int fd[2],
        nbytes;
    pid_t pid;
    char tempString[1000];
    char readbuffer[1000];
    FILE *in;
    FILE *out;
    out = fopen(argv[2], "w");

    pipe(fd);
    char inputString[1000];
    
    if ((pid = fork()) == -1)
    {
        perror("Fork Error!");
        exit(1);
    }

    if (pid != 0)
    {
        // Close Input Pipe End
        close(fd[0]);
        in = fopen(argv[1], "r");

        // Read from File
        while (fscanf(in, "%s\n", tempString) != EOF)
        {
            strcat(inputString, tempString);
        }

        // Inputs tempString through the output end
        write(fd[1], inputString, (strlen(inputString) + 1));
        close(fd[1]);

        waitpid(pid, NULL, 0);
    }
    else
    {
        // Close Output Pipe End
        close(fd[1]);
        // Reads from pipe to take in the tempString from input end.
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

        char tempChar;
        char previousChar = ' ';
        char currentChar;
        int repeatedCount = 0;
        int counter = 0;

        // Compress File
        while (counter < strlen(readbuffer))
        {
            currentChar = readbuffer[counter];
            if (currentChar != previousChar)
            {
                if (repeatedCount >= 16)
                {
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
            counter++;
            previousChar = currentChar;
        }

        if (repeatedCount != 0)
        {
            if (repeatedCount >= 16)
            {
                MyCompression(out, repeatedCount, previousChar);
            }
            else
            {
                for (int i = 0; i < repeatedCount; i++)
                {
                    putc(previousChar, out);
                }
            }
        }
        close(fd[0]);
    }

    return (0);
}
