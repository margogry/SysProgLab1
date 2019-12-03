#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//Переменна, для подсчета числа замен
int numberOfChanges = 0;
//
//Функция для вывода инстукции
//
void help(){
    fprintf(stdout, "Эта программа выполняет замены в тексте.\n");
    fprintf(stdout, "%%date%% заменять на текущую дату;\n");
    fprintf(stdout, "%%time%% заменять на текущее время;\n");
    fprintf(stdout, "%%line%% заменять на номер текущей строки;\n");
    fprintf(stdout, "%%counter%% заменять на значение счетчика, который увеличивается на\n");
    fprintf(stdout, "единицу после каждой замены, начальное значение счетчика - ноль.\n");
    fprintf(stdout, "Для начала работы введите: ./main.exe [исходный файл [результирующий файл]]\n");
}
//
//Функция, обрабатывающая поступившее слово на предмет совпадения с ключевами
//
char* plusWord(char *word, int numberOfLine){//, int *numberOfSymbols){
    if (!strcmp(word, "%date%")){
        numberOfChanges++;
        time_t rawDate;
        struct tm * dateInfo;
        char *buffer = NULL;
        buffer = (char*)malloc(9*sizeof(char));
        time ( &rawDate );
        dateInfo = localtime (&rawDate );
        strftime (buffer, 9, "%x", dateInfo);
        return buffer;
        }
    else
        if (!strcmp(word,"%time%\0")) {
            numberOfChanges++;
            time_t rawTime;
            struct tm * timeInfo;
            char *buffer = NULL;
            buffer = (char*)malloc(9*sizeof(char));
            time ( &rawTime );
            timeInfo = localtime ( &rawTime );
            strftime (buffer,9,"%X",timeInfo);
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

//
//Функция для чтения потока входных данных и их вывода
//
void readText(FILE *fileInput, FILE *fileOutput){
    char *inputText = NULL;
    inputText = (char*)malloc(sizeof(char));
    int numberOfSymbolsInText = 0;
    char currentSymbol = fgetc(fileInput);

    while (currentSymbol != EOF)//чтение
    {
        inputText = (char *) realloc(inputText, (numberOfSymbolsInText + 1) * sizeof(char));
        inputText[numberOfSymbolsInText] = currentSymbol;
        currentSymbol = fgetc(fileInput);
        numberOfSymbolsInText++;
    }

    if (fileOutput == stdout)
        fprintf(fileOutput, "\n");

    int k = 0;
    int numberOfLines = 1;
    while (k < numberOfSymbolsInText){ //обработка
        if (inputText[k] == '%'){
            char *wordOnly = NULL;
            wordOnly = (char *) malloc(sizeof(char));

            int numberOfSymbolsInWord = 0;
            int isPersent = 0;
            int tmpK = k, tmpChanges = numberOfChanges;
            while (tmpK < numberOfSymbolsInText && (isPersent != 1) && (numberOfSymbolsInWord < 10) ) { //запись слова с %%
                wordOnly = (char *) realloc(wordOnly, (numberOfSymbolsInWord + 1) * sizeof(char));
                wordOnly[numberOfSymbolsInWord] = inputText[tmpK];
                if (wordOnly[numberOfSymbolsInWord] == '%' && numberOfSymbolsInWord != 0)
                    isPersent = 1;
                numberOfSymbolsInWord++;
                tmpK++;
            }
            wordOnly = (char *) realloc(wordOnly, (numberOfSymbolsInWord+1) * sizeof(char));
            wordOnly[numberOfSymbolsInWord] = '\0';

            char *newWord = NULL;
            newWord = (char *) malloc(sizeof(char));
            newWord = plusWord(wordOnly, numberOfLines);

            if (tmpChanges == numberOfChanges){ //вывод
                fprintf(fileOutput, "%c", inputText[k]);
                k++;
            }
            else{
                k = tmpK;
                fprintf(fileOutput, "%s", newWord);
            }

            free(wordOnly);
        }
        else{
            fprintf(fileOutput, "%c", inputText[k]);//вывод
            if (inputText[k] == '\n')
                numberOfLines++;
            k++;
        }

    }
    free(inputText);
    return;
}



int main(int argc, char **argv){
    FILE *fileInput = 0;
    FILE *fileOutput = 0;
    //
    //Оператор для выбора потоков считывания и записи данных.
    //
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
        default:
            help();
            break;
    };
    return 0;
}