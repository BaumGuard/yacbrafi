#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "read_file.h"

#define ENHANCE_RANGE   10
#define BAND_WIDTH      10
#define INIT_BAND_PTR    4


// Global variables
int* band; // Band of cells
int it = INIT_BAND_PTR; // Band iterator
int band_length = 0; // Length of band
int sign_it = 0; // Program iterator
int prog_length = 0; // Length of program


// Command line argument list
struct args {
        bool arg_char;
        bool arg_pap;
        bool arg_pt;
        bool arg_file;
};

struct args a;





// Check if the given program is correct (Equal number of [ and ])
bool check_correctness(char* str) {

    int i = 0;
    int countOpen = 0;
    int countClosed = 0;

    while (str[i] != '\0') {
        switch (str[i]) {
            case '[':
                countOpen++;
                break;
            case ']':
                countClosed++;
                break;
        }

        i++;
    }

    if (countOpen == countClosed)
        return true;
    else
        return false;
}







// Allocate memory for band
void allocBand(int length) {
    band = (int*)malloc(length*sizeof(int));

    for (int i=0; i<length; i++)
        band[i] = 0;

    band_length = length;
}

// Enhance band to the left and to the right
void enhanceBand(int length) {
    void* ra = realloc(band, (band_length+2*length)*sizeof(int));

    for (int i=0; i<band_length; i++) {
        band[i+length] = band[i];
    }

    for (int i=0; i<length; i++) {
        band[i] = 0;
        band[band_length+length] = 0;
    }


    it += length;
    band_length += 2*length;
}



void determine_prog_length(char* str) {

    int i = 0;

    while (str[i] != '\0') {
        prog_length++;
        i++;
    }
}


void print_active_position(char* inp, int place) {
    for (int i=0; i<prog_length; i++) {
        if (i == place) printf("\033[1;32m%c\033[1;0m", inp[i]);
        else printf("%c", inp[i]);
    }
    printf("\n");
}





void runBrainfuck (char* str, int i) {

    sign_it = i;

    while (str[sign_it] != '\0') {

        if (a.arg_pap == true) print_active_position(str, sign_it);
        if (a.arg_pt == true) printf("%c", str[sign_it]);

        switch (str[sign_it]) {
            case '+':
                band[it]++;
                break;
            case '-':
                band[it]--;
                break;
            case '<':
                if (it == 0) enhanceBand(ENHANCE_RANGE); // Enhance the band if the pointer reaches the margin
                it--;
                break;
            case '>':
                if (it == band_length-1) enhanceBand(ENHANCE_RANGE); // Enhance the band if the pointer reaches the margin
                it++;
                break;
            case ',':
                printf("Input: ");
                scanf("%d", &band[it]);
                break;
            case '.':
                if (a.arg_char == true)
                    printf("%c\n", band[it]);
                else
                    printf("%d\n", band[it]);
                break;
            case '[':
                // If the current cell is 0, run to the end of the current loop
                if (band[it] == 0) {
                    int count = 0;
                    do {
                        switch (str[sign_it++]) {
                            case '[':
                                count++; break;
                            case ']':
                                count--; break;
                        }
                    }
                    while (count != 0);
                    sign_it--;
                }
                break;
            case ']':
                // Run to the beginning of the current loop
                int count = 0;
                do {
                    switch (str[sign_it--]) {
                        case ']':
                            count++; break;
                        case '[':
                            count--; break;
                    }
                }
                while (count != 0);
                break;
        }

        sign_it++; // Increment the program iterator
    }
}


int main (int argc, char** argv) {
    allocBand(BAND_WIDTH);

    char* input;

    int file_index;

    // Parsing the command line arguments
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-c") == 0)
            a.arg_char = true;
        else if (strcmp(argv[i], "-pap") == 0)
            a.arg_pap = true;
        else if (strcmp(argv[i], "-pt") == 0)
            a.arg_pt = true;
        else if (strcmp(argv[i], "-f") == 0) {
            a.arg_file = true;
            file_index = ++i;
        }
        else
            input = argv[i];
    }

    // Read the file if available
    if (a.arg_file == true)
        input = read_file(argv[file_index]);


    determine_prog_length(input);

    // If the program is correct, run it
    if (check_correctness(input))
        runBrainfuck(input, 0);
    else {
        fprintf(stderr, "\033[1;31mNot a correct program (Missing square bracket)\033[1;0m\n");
        return 1;
    }

    // Freeing the memory of the band
    free(band);

    return 0;
}
