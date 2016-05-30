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




