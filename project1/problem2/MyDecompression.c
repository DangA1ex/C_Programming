#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MyDecompression(FILE *out, int repeatedCount, char previousChar) {
    if (repeatedCount >= 16) {
        if (previousChar == '-') {
            for(int i = 0; i < repeatedCount; i++) {
                putc('0', out);
            }
        }
        else if (previousChar == '+') {
            for(int i = 0; i < repeatedCount; i++) {
                putc('1', out);
            }
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
    printf("CS4440 MyDecompression Program\n");
    printf("Input File: %s \n", argv[1]);
    printf("Output File: %s \n", argv[2]);
    printf("<-----------------------------------------------------------> \n");

    fp = fopen(argv[1], "r");
    
    // Handle file output
    FILE *out;
    out = fopen(argv[2], "w");

    char tempChar;
    char previousChar = ' ';
    char currentChar;
    char numberString[20];
    int numberFlag = 0;
    int tempIndex = 0;

    while ((tempChar = fgetc(fp)) != EOF) {
        currentChar = tempChar;
        if(currentChar == '-') {
            if(numberFlag == 0) {
                numberFlag = 1;
            } else {
                MyDecompression(out, atoi(numberString), '-');
                tempIndex = 0;
                numberFlag = 0;
            }
        }

        if(currentChar == '+') {
            if(numberFlag == 0) {
                numberFlag = 1;
            } else {
                MyDecompression(out, atoi(numberString), '+');
                tempIndex = 0;
                numberFlag = 0;
            }
        }

        if(numberFlag == 1 && currentChar != '-') {
            numberString[tempIndex] = currentChar;
            tempIndex++;
        } else if(numberFlag == 1 && currentChar != '+') {
            numberString[tempIndex] = currentChar;
            tempIndex++;
        } else {
            if(currentChar != '-' && currentChar != '+') {
                putc(currentChar, out);
            }
        }
        previousChar = currentChar;
    }

    fclose(out);
}