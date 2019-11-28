#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void help() {
    printf("This function \n");
    printf("usage:\n");
}

int isEnd(char c){
    if (c == ' ')
        return 1;
    if((c == '\n')||(c == '\t')||(c == '\r')||(c == '\0'))
        return 2;
    else
        return 0;
}

char *date(){
    return "date";
}
char *time(){
    return "time";
}
char *line(){
    return "line";
}
char *counter(){
    return "counter";
}

char *plusWord(char *word, int num){
    if (!strcmp(word, "%date%"))
            return date();
    else
        if (!strcmp(word,"%time%"))
            return time();
        else
            if (!strcmp(word, "%line%"))
                return line();
            else
                if(!strcmp(word, "%counter%"))
                    return counter();
                else
                {
                   /* char *result;
                    result = (char*)malloc(sizeof(char));
                    result = (char*) realloc(result, num*sizeof(char));
                    for (int j = 0; j < num; j++)
                    {
                        result[j] = word[j];
                    }
                    return result;*/
                   return word;
                }

}

void readText(FILE *fileInput, FILE *fileOutput)
{

    int stdinFlag = 1;
    while (stdinFlag == 1 && !feof(fileInput))
    {
        char *wordOnly = NULL;
        wordOnly = (char*)malloc(sizeof(char));
        int numberOfSymbolsInWord = 0;
        char currentSymbol = fgetc(fileInput);

        while (!feof(fileInput) && !isEnd(currentSymbol))
        {
            wordOnly = (char *) realloc(wordOnly, (numberOfSymbolsInWord + 1) * sizeof(char));
            wordOnly[numberOfSymbolsInWord] = currentSymbol;
            currentSymbol = fgetc(fileInput);
            numberOfSymbolsInWord++;
        }

        wordOnly = (char *) realloc(wordOnly, sizeof(plusWord(wordOnly, numberOfSymbolsInWord)));
        wordOnly = plusWord(wordOnly, numberOfSymbolsInWord);

       for (int k = 0; k < strlen(wordOnly); k++)
        {
            fprintf(fileOutput,"%c", wordOnly[k]);
        }//*/
        //fprintf(fileOutput,"%s", wordOnly);
        free(wordOnly);

       //до контрл д
        fprintf(fileOutput,"%c", currentSymbol);
    }

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