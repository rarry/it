#include "utils.h"
#include "arithmeticCoding.h"

void printTab(int *tab, int length){
    int i;
    for(i=0; i<length; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int * createC(int * r){
    static int c[SIZE];
    c[0] = 0;
    int i,j;
    for(i=1; i<SIZE; i++)
    {
        c[i] = 0;
        for(j=0; j < i; j++)
        {
            c[i] = c[i] + r[j];
        }
    }
    return c;
}

int * createD(int * r){
    static int d[SIZE];

    int i,j;
    for(i=0; i<SIZE; i++)
    {
        d[i] = 0;
        for(j=0; j <= i; j++)
        {
            d[i] = d[i] + r[j];
        }
    }
    return d;
}

void printBinaryInterval(int *tab)
{
    printf("binary interval:\t");
    int index = 0;
    while(1)
    {
        int v = tab[index++];
        if(v >= 0)
        {
            printf("%d", v);
        }
        else
        {
            break;
        }
    }
    printf("\n");
}

void printdecoded(int *tab)
{
    printf("decoded:\t");
    int index = 0;
    while(1)
    {
        int v = tab[index++];
        if(v > 0)
        {
            printf("%d", v);
        }
        else
        {
            break;
        }
    }
    printf("\n");
}
