#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    FILE *output;
    int i = 0;
    time_t t;

    output = fopen("input.txt", "w+");

    // preset values to randomize
    char *str[7]; 
    str[0] = "000000000000100101111110";
    str[1] = "01011111111111000000000000";
    str[2] = "00000001010111111111";
    str[3] = "111111111001100";
    str[4] = "11010110";
    str[5] = "00110111001";
    str[6] = " ";
    
    // initialize rand
    srand((unsigned) time(&t));

    printf("Creating File...\n");

    while(1) {
        char temp[300];
        // assemble strings randomly using str array
        for (int j = 0; j < rand() % 50; j++) {
            snprintf(temp, 300, "%s", str[rand() % 7]);
        }

        fputs(temp, output);

        i++;
        
        // ends program when i reaches a certain point and newline after 10 loops
        if (i > 1700000) {
            break;
        } else if (i % 10 == 0) {
            fputs("\n", output);
        }
    }

    printf("File Created!\n");

    fclose(output);
    return 0;
}