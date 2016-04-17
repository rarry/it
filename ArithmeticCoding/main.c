#include <stdio.h>
#include <stdlib.h>

typedef struct{
	double a ;
	double b;
}Interval;

Interval findInterval(int x[], int xLength, double c[], double d[]);
int * findBinaryInterval(Interval interval);
void printBinaryInterval(int *tab);

double * calculateD(double p[], int length){
    int i;
    double d[length];
    double cumulative = 0.0;
    for(i=0; i<length; i++){
        cumulative += p[i];
        d[i] = cumulative;
    }
    return d;
}

int main()
{

    //int xLength = 4;
	//int x[4] = {2,3,2,0};
	//double p[4] = {.05, .05, .5, .4};
	//double c[4] = {0, .05, .1, .6};
	//double d[4] = {.05, .1, .6, 1.0};

	int xLength = 3;
	int x[3] = {2,1,0};
	double p[3] = {.2, .4, .4};
	double c[3] = {0, 0.2, 0.6};
	double *d = calculateD(p, 3);

	Interval interval = findInterval(x, xLength, c, d);
    printf("%f, %f\n\n", interval.a, interval.b);

    printf("Binary representation of the interval (%f,%f) is:\n", interval.a, interval.b);
	int * binaryInterval = findBinaryInterval(interval);
    printBinaryInterval(binaryInterval);
    return 0;
}

Interval findInterval(int x[], int xLength, double c[], double d[]) {

	double a = 0.0;
	double b = 1.0;

	int i;
	for(i=0; i < xLength; ++i) {
		double w = b - a;
		b = a + w * d[x[i]];
		a = a + w * c[x[i]];
	}

	Interval interval = {a,b};
	return interval;
}

int * findBinaryInterval(Interval interval) {

    int index=0;
    int binaryInterval[1000];
    int s = 0;
    double a = interval.a;
    double b = interval.b;

    while(b < 0.5 || a > 0.5){
        if(b < 0.5) {
            binaryInterval[index++] = 0;
            a = 2*a;
            b = 2*b;
        }else if(a > 0.5) {
            binaryInterval[index++] = 1;
            a = 2*(a - 0.5);
            b = 2*(b - 0.5);
        }
    }

    while(a > 0.25 && b < 0.75){
        s = s+1;
        a = 2*(a - 0.25);
        b = 2*(b - 0.25);
    }

    s = s+1;
    if(a <= 0.25){
        binaryInterval[index++] = 0;
        int i;
        for(i=0;i<s;i++){
           binaryInterval[index++] = 1;
        }
    }else{
        binaryInterval[index++] = 1;
        int i;
        for(i=0;i<s;i++){
           binaryInterval[index++] = 0;
        }
    }
    binaryInterval[index++] = -1;
    return binaryInterval;
}

void printBinaryInterval(int *tab){
    int index = 0;
    while(1){
        int v = tab[index++];
        if(v >= 0){
            printf("%d", v);
        }else{
            break;
        }
    }
}
