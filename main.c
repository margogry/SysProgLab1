#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void help() {
    printf("This function \n");
    printf("usage:\n");
}

int isEnd(char c){
    if((c == ' ')||(c == '\n')||(c == '\t')||(c == '\r')||(c == '\0')||(c == EOF))
        return 1;
    else
        return 0;
}


char* plusWord(char *word){//, int *numberOfSymbols){
    if (!strcmp(word, "%date%"))
            return "date"; // date();
    else
        if (!strcmp(word,"%time%")) {
            //*numberOfSymbols = 4;
            return "time";
        }
        else {
            return word;
        };
    /*
else
if (!strcmp(word, "%line%"))
    return line();
else
    if(!strcmp(word, "%counter%"))
        return counter();*/
}

void readText(FILE *fileInput, FILE *fileOutput)
{
    char *inputText = NULL;
    inputText = (char*)malloc(sizeof(char));
    int numberOfSymbolsInText = 0;
    char currentSymbol = fgetc(fileInput);
    while (currentSymbol != EOF)
    {
        inputText = (char *) realloc(inputText, (numberOfSymbolsInText + 1) * sizeof(char));
        inputText[numberOfSymbolsInText] = currentSymbol;
        currentSymbol = fgetc(fileInput);
        numberOfSymbolsInText++;
    }

    fprintf(fileOutput, "\n");

    int k = 0;
    while (k < numberOfSymbolsInText){
        char *wordOnly = NULL;
        wordOnly = (char *) malloc(sizeof(char));// */
        int numberOfSymbolsInWord = 0;

        while (k < numberOfSymbolsInText  && !isEnd(inputText[k])) {
            wordOnly = (char *) realloc(wordOnly, (numberOfSymbolsInWord + 1) * sizeof(char));
            wordOnly[numberOfSymbolsInWord] = inputText[k];
            numberOfSymbolsInWord++;
            k++;
        }
        fprintf(fileOutput, "%s", wordOnly);
        if (!strcmp(wordOnly, "%time%"))
        {
            wordOnly = "time";
            numberOfSymbolsInWord = 4;
            fprintf(fileOutput, "\ntit\n");
        }

        //wordOnly = plusWord(wordOnly);//, &numberOfSymbolsInWord);
        //numberOfSymbolsInWord = strlen(wordOnly);

        for (int i = 0; i < numberOfSymbolsInWord; i++) {
            fprintf(fileOutput, "%c", wordOnly[i]);
        }//*/
        fprintf(fileOutput, "%c", inputText[k]);
        k++;
        free(wordOnly);
    }

    free(inputText);
// */
    return;
};



int main(int argc, char **argv){
    FILE *fileInput = 0;
    FILE *fileOutput = 0;

    switch (argc){
        case 1:
            readText(stdin, stdout);
            break;
        case 2:
            fileInput = fopen(argv[1],"r");
            if (fileInput != NULL) {
                  //из файла в консоль
                readText(fileInput, stdout);
                fclose(fileInput);
            }
            else {
                fprintf(stderr, "Unable to open file %s", argv[1]);
            }
            break;
        case 3:
                fileInput = fopen(argv[1],"r");
                if (fileInput != NULL) {
                    fileOutput = fopen(argv[2],"w");
                    if (fileOutput != NULL) {
                        //ввод и вывод в файл
                        readText(fileInput, fileOutput);
                        fclose(fileOutput);
                    }
                    fclose(fileInput);
                }
                else {
                    fprintf(stderr, "Unable to open file %s", argv[2]);
                }
            break;
        default: break;
    };
    return 0;
}