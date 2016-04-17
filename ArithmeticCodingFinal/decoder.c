#include <stdio.h>
#include "decoder.h"
#include "arithmeticCoding.h"

int * decode(int * binaryCode, int length, int c[], int d[])
{
    static int decoded[SIZE];
    int index = 0;
    int a = 0;
    int b = WHOLE;
    //int z = binaryToInt(binaryCode, length);

    int z = 0;
    int i;
    for(i=0; i < PRECISION && i<length; i++)
    {
        int v = pow(2,PRECISION - 1 - i);
        int bit = binaryCode[i];
        z = z +  bit * v;
    }

    printf("z:\t%d", z);
    while(1)
    {
        int j;
        for(j=0; j<length; j++)
        {
            long w = b - a;
            double tmp1 = (w*d[j])/(double)R;
            double tmp2 = (w * c[j])/(double)R;
            int b0 = a + roundl(tmp1);
            int a0 = a + roundl(tmp2);
            if(z < b0 && z >= a0)
            {
                decoded[index++] = j;
                a = a0;
                b = b0;
                if(j == 0)
                {
                    return decoded;
                }
            }
        }

        while(b < HALF || a > HALF)
        {
            if(b < HALF)
            {
                a = 2*a;
                b = 2*b;
                z = 2*z;
            }
            else if(a > HALF)
            {
                a = 2*(a - HALF);
                b = 2*(b - HALF);
                z = 2*(z - HALF);
            }
            if(i < length && binaryCode[i] == 1)
            {
                z++;
            }
            i++;
        }

        while(a > QUARTER && b < 3 * QUARTER)
        {
            a = 2*(a - QUARTER);
            b = 2*(b - QUARTER);
            z = 2*(z-QUARTER);
            if(i < length && binaryCode[i] == 1)
            {
                z++;
            }
            i++;
        }
    }
    return decoded;
}
