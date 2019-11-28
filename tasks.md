Выполнить замены в тексте:

 %date% заменять на текущую дату;

 %time% заменять на текущее время;

 %line% заменять на номер строки;

 %counter% заменять на значение счетчика, который увеличивается на
единицу после каждой замены, начальное значение счетчика – ноль.

1. разобраться с файлами

2. Разобратьс с чтением из файлой

3. реализовать нужный алгоритм

void readText(FILE *fileInput, FILE *fileOutput)
{
    char *outputText = NULL;
    outputText = (char*)malloc(sizeof(char));
    int numberOfSymbolInText = 0;
    int stdinFlag = 1;
    while (stdinFlag == 1 && !feof(fileInput))
    {
        char *wordOnly = NULL;
        wordOnly = (char*)malloc(sizeof(char));
        //wordOnly = (char*)realloc(wordOnly, 0);
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
        numberOfSymbolsInWord = strlen(wordOnly);

        int sizeB = (numberOfSymbolInText + numberOfSymbolsInWord) * sizeof(char) ;// размер всего сообщения в бит
        int size = sizeB/sizeof(char);
        outputText=(char*)realloc(outputText, sizeB);
        for (int j = numberOfSymbolInText, k = 0; k < numberOfSymbolsInWord; j++, k++)
        {
            outputText[j] = wordOnly[k];
        }
        outputText=(char*)realloc(outputText, sizeB + 1);
        outputText[size] = currentSymbol;
        //
        numberOfSymbolInText = size + 1;
        if (fileInput == stdin && isEnd(currentSymbol) == 2)
            stdinFlag = 0;
    }
    int i = 0;
    while (i < numberOfSymbolInText-1)
    {
        fprintf(fileOutput,"%c",outputText[i]);
        i++;
    }

    //free(outputText);
    return;
};