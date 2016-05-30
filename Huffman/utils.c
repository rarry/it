#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void printCodeTable(char letters[], int *codeTable, int length)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("%c\t%d\n", letters[i], codeTable[i]);
    }
    printf("\n");
}

void printCodeTableForIdx(int *codeTable, int length)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("%c\t%d\n", i, codeTable[i]);
    }
    printf("\n");
}

void printTabInt(int *tab, int length)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void printTabChar(char *tab, int length)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("%c ", tab[i]);
    }
    printf("\n");
}

void printbits(int i)
{
    char str[16];
    getBin(i, str);
    printf("%s\n", str);
}

void getBin(int num, char *str)
{
    *(str+5) = '\0';
    int mask = 0x10 << 1;
    while(mask >>= 1)
        *str++ = !!(mask & num) + '0';
}

void printPolynomial(unsigned char * restPolynomial, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("Bajt %d wartosci CRC: %#x\n", i, restPolynomial[i]);
    }
}

void appendFileToFile(char *from, char *to)
{
    FILE * input;
    FILE * output;

    if((input = fopen(from, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(to, "a")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int c;
    do
    {
        c = fgetc(input);
        if( feof(input) )
        {
            break ;
        }
        fputc(c, output);
    }while(1);

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

void resetIntTable(int table[], int length){

    int i;
    for(i=0; i<length; i++)
    {
        table[i] = 0;
    }
}

void copyFile(char *from, char *to)
{
    FILE * input;
    FILE * output;

    if((input = fopen(from, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(to, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int c;
    do
    {
        c = fgetc(input);
        if( feof(input) )
        {
            break ;
        }
        fputc(c, output);
    }while(1);

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

void appendZeroes(char *fileName, int zeroesCount){

    FILE * fp;

    if((fp = fopen(fileName, "a")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int i;
    for(i=0; i<zeroesCount; i++){
        fputc(0, fp);
    }

    if(fclose(fp) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

void copySkip(char * inputName, char * outputName, int skipBytes)
{

    FILE * input;
    FILE * output;

    if((input = fopen(inputName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(outputName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }


    fseek(input, 0L, SEEK_END);
    int fileSize = ftell(input);
    rewind(input);

    int c;
    int i;

    for(i=0; i<fileSize-skipBytes; i++)
    {
        c = fgetc(input);
        fputc(c, output);
    }

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

