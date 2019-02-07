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
    char text[9999];

    // checks each string in input file
    while(fgets(text, 9999, input)){

        char current, compressed[7];
        char word[] = "0101110010010-13-010111 0111100010+10+1000101";
        int flag = 0;
        int size = strlen(word);

        /* scans through text(input) string, if + or - then flag will be set to true
        and the compressed number will be set to compressed*/
        for (int i = 0; i < size; i++) {
            if (flag != 1){
                if (word[i] != '+' && word[i] != '-'){
                    fputc(word[i], output);
                } else {
                    if (word[i] == '+'){
                        current = '1';
                    } else {
                        current = '0';
                    }
                    flag = 1;
                    memset(compressed, 0, sizeof(compressed));
                }
            } else {
                if (word[i] != '+' && word[i] != '-'){
                    strncat(compressed, &word[i], 1);
                } else {
                    for (int j = 0; j < atoi(compressed); j++){
                        fputc(current, output);
                    }
                    flag = 0;
                    memset(compressed, 0, sizeof(compressed));
                }
            }
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}