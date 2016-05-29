#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void printCodeTable(char letters[], int *codeTable, int length);

void printTabInt(int *tab, int length);

void printTabChar(char *tab, int length);

void getBin(int num, char *str);

void printPolynomial(unsigned char * restPolynomial, int size);

void appendFileToFile(FILE *from, FILE *to);

void calculateFreq(FILE *from, int freq[]);

#endif // UTILS_H_INCLUDED
