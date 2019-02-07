#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *input, *output;

    input = fopen("input.txt", "r");

    /* checks if input file is valid */
    if (input == NULL){
        printf("Cannot find input file...\n");
        exit(1);
    }

    output = fopen("output.txt", "w+");

    // temp strings to hold input, current string, and compressed string
    char text[9999], current, compressed[7];
    int counter = 0;

    // checks each string in input file
    while(fgets(text, 9999, input)){
        current = text[0];

        /* scans through text string, if char at index doesnt match current char then writes
        current string to output file. resets counter and sets the current char new char*/
        for (int i = 0; i < strlen(text); i++) {
            if (text[i] != current){
                if (counter < 16) {
                    for (int j = 0; j < counter; j++){
                        fputc(current, output);
                    }
                } else {
                    if (current == '0') {
                        snprintf(compressed, 6, "-%d-", counter);
                    } else if (current == '1') {
                        snprintf(compressed, 6, "+%d+", counter);
                    }
                    fputs(compressed, output);
                }
                current = text[i];
                counter = 1;
            } else {
                counter++;
            }
            if (i == strlen(text) - 1) {
                for (int j = 0; j < counter; j++){
                    fputc(current, output);
                }
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}