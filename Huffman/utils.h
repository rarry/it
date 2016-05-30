#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void printCodeTable(char letters[], int *codeTable, int length);

void printCodeTableForIdx(int *codeTable, int length);

void printTabInt(int *tab, int length);

void printTabChar(char *tab, int length);

void getBin(int num, char *str);

void printPolynomial(unsigned char * restPolynomial, int size);

void appendFileToFile(char *from, char *to);

void resetIntTable(int table[], int length);

void copyFile(char *from, char *to);

void appendZeroes(char *fileName, int zeroesCount);

#endif // UTILS_H_INCLUDED
