#include <stdio.h>

int main(int argc, char* argv[]) {
    char * inputFile = "stdin";
    char *outputFile = "stdout";

    if (argc > 1){
        inputFile = argv[1];
        if (argc > 2){
            outputFile = argv[2];
        }
    };

    printf(inputFile);
    printf(outputFile);
    return 0;
}