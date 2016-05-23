#include "utils.h"

void printTabInt(int *tab, int length){
    int i;
    for(i=0; i<length; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void printTabChar(char *tab, int length){
    int i;
    for(i=0; i<length; i++){
        printf("%c ", tab[i]);
    }
    printf("\n");
}

void printbits(int i) {

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


