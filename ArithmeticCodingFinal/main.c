#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "arithmeticCoding.h"
#include "encoder.h"


int * findInterval(int x[], int xLength, int c[], int d[]);
int * decode(int * binaryCode, int length, int c[], int d[]);

int main()
{
    int x[SIZE] = {2,1,4,3,0};
    printf("message:\t");
    printTab(x, SIZE);
    //double p[3] = {.2, .4, .4};
    int r[SIZE] = {10,20,20,35,15};
    int *c = createC(r);
    printf("c:\t");
    printTab(c, SIZE);
    int *d = createD(r);
    printf("d:\t");
    printTab(d, SIZE);


    printf("%d\n", WHOLE);
    int * binaryInterval = findInterval(x,SIZE,c,d);
    int length = calculateLength(binaryInterval);
    printBinaryInterval(binaryInterval);
    int * decoded = decode(binaryInterval, length, c, d);
    printf("\n\n");
    printdecoded(decoded);
    return 0;
}



int calculateLength(int *tab)
{
    int length = 0;
    int index = 0;
    while(1)
    {
        int v = tab[index++];
        if(v >= 0)
        {
            length++;
        }
        else
        {
            return length;
        }
    }
}
