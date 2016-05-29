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

void appendFileToFile(FILE *from, FILE *to)
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

void calculateFreq(FILE *from, int freq[]){

    FILE * input;
    FILE * output;

    if((input = fopen(from, "rb")) == NULL)
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
        freq[c]++;

    }while(1);

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }


}

