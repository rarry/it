#include <stdio.h>
#include "encoder.h"
#include "arithmeticCoding.h"

int * findInterval(int x[], int xLength, int c[], int d[])
{

    int index=0;
    int binaryInterval[1000];
    long a = 0;
    long b = WHOLE;
    int s = 0;

    int i;
    for(i=0; i < xLength; ++i)
    {
        // w zawsze bedzie przynajmniej QUARTER
        long w = b - a;
        int xi = x[i];
        int dxi = d[xi];
        int cxi = c[xi];
        double tmp1 = (w*dxi)/(double)R;
        double tmp2 = (w * cxi)/(double)R;
        b = a + roundl(tmp1);
        a = a + roundl(tmp2);

        while(b < HALF || a > HALF)
        {
            if(b < HALF)
            {
                binaryInterval[index++] = 0;
                a = 2*a;
                b = 2*b;
                int i;
                for(i=0; i<s; i++)
                {
                    binaryInterval[index++] = 1;
                }
                s = 0;
            }
            else if(a > HALF)
            {
                binaryInterval[index++] = 1;
                a = 2*(a - HALF);
                b = 2*(b - HALF);
                int i;
                for(i=0; i<s; i++)
                {
                    binaryInterval[index++] = 0;
                }
                s = 0;
            }
        }

        while(a > QUARTER && b < 3*QUARTER)
        {
            s = s+1;
            a = 2*(a - QUARTER);
            b = 2*(b - QUARTER);
        }
    }

    s = s+1;
    if(a <= QUARTER)
    {
        binaryInterval[index++] = 0;
        int i;
        for(i=0; i<s; i++)
        {
            binaryInterval[index++] = 1;
        }
    }
    else
    {
        binaryInterval[index++] = 1;
        int i;
        for(i=0; i<s; i++)
        {
            binaryInterval[index++] = 0;
        }
    }
    binaryInterval[index++] = -1;

    printf("Interval: %d, %d\n", a, b);
    return binaryInterval;
}
