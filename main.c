#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int numberOfChanges = 0;

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


char* plusWord(char *word, int numberOfLine){//, int *numberOfSymbols){
    if (!strcmp(word, "%date%\0")){
        numberOfChanges++;
        time_t rawDate;
        struct tm * dateInfo;
        char *buffer = NULL;
        buffer = (char*)malloc(9*sizeof(char));// строка, в которой будет храниться текущее время

        time ( &rawDate );                               // текущая дата в секундах
        dateInfo = localtime (&rawDate );               // текущее локальное время, представленное в структуре

        strftime (buffer, 9, "%x", dateInfo); // форматируем строку времени
        return buffer;
        }
    else
        if (!strcmp(word,"%time%\0")) {
            numberOfChanges++;
            time_t rawTime;
            struct tm * timeInfo;
            char *buffer = NULL;
            buffer = (char*)malloc(9*sizeof(char));// строка, в которой будет храниться текущее время

            time ( &rawTime );                               // текущая дата в секундах
            timeInfo = localtime ( &rawTime );               // текущее локальное время, представленное в структуре

            strftime (buffer,9,"%X",timeInfo); // форматируем строку времени
            return buffer;
        }
        else
            if (!strcmp(word,"%line%\0")) {
                numberOfChanges++;
                char *buffer = NULL;
                buffer = (char*)malloc(100*sizeof(char));
                sprintf(buffer, "%d", numberOfLine);
                return buffer;
            }
            else
                if (!strcmp(word, "%counter%")){
                    char *buffer = NULL;
                    buffer = (char*)malloc(100*sizeof(char));
                    sprintf(buffer, "%d", numberOfChanges);
                    numberOfChanges++;
                    return buffer;
                }
                else
                    return word;
};


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
    int numberOfLines = 1;
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

        wordOnly = (char *) realloc(wordOnly, (numberOfSymbolsInWord + 1) * sizeof(char));
        wordOnly[numberOfSymbolsInWord] = '\0';

        fprintf(fileOutput, "%s", plusWord(wordOnly, numberOfLines));

        fprintf(fileOutput, "%c", inputText[k]);
        if (inputText[k] == '\n')
            numberOfLines++;
        k++;
        free(wordOnly);
    }

    free(inputText);
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