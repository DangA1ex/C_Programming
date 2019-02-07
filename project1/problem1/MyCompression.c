#include <stdio.h>

void MyCompression(FILE *out, int repeatedCount, char previousChar) {
    if (repeatedCount >= 16) {
        if (previousChar == '0') {
            putc('-', out);
            fprintf(out, "%d", repeatedCount);
            putc('-', out);
        }
        else if (previousChar == '1') {
            putc('+', out);
            fprintf(out, "%d", repeatedCount);
            putc('+', out);
        }
    }
}

int main(int argc, char **argv) {
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

    while ((tempChar = fgetc(fp)) != EOF) {
        currentChar = tempChar;
        printf("%c", currentChar);
        if (currentChar != previousChar) {
            if (repeatedCount >= 16) {
                MyCompression(out, repeatedCount, previousChar);
            }
            else {
                for (int i = 0; i < repeatedCount; i++) {
                    putc(previousChar, out);
                }
            }
            repeatedCount = 0;
        }
        repeatedCount++;
        previousChar = currentChar;
    }

    if (repeatedCount != 0) {
        if (repeatedCount >= 16) {
            MyCompression(out, repeatedCount, previousChar);
        }
        else {
            for (int i = 0; i < repeatedCount; i++) {
                putc(previousChar, out);
            }
        }
    }

    fclose(out);
}