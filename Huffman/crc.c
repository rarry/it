#include <stdio.h>
#include <stdlib.h>
#include "crc.h"



int dzielenie(char *nazwa_pliku_in, unsigned char reszta[], unsigned char wielomian[])
{
    unsigned char bufor_wejscia[BUFSIZE], kolejka[SIZECRC+BUFSIZE];
    unsigned char maska=128, ostatni_bit, pierwszy_bit;
    int n;
    int licznik_bitow=0;
    int licznik_bajtow_in=0, licznik_buforu=0;

    int i;
    for (i=0; i<SIZECRC; i++)
        reszta[i]=0;

    for (i=0; i<SIZECRC+BUFSIZE; i++)
        kolejka[i]=0;

    FILE *wskaznik_pliku_in=NULL;
    wskaznik_pliku_in=fopen(nazwa_pliku_in,"rb");

    if (wskaznik_pliku_in == NULL)
    {
        printf("Nie mozna otworzyc pliku: %s  \n", nazwa_pliku_in);
        exit(EXIT_FAILURE);
    }

    while((n=fread(bufor_wejscia,sizeof(unsigned char),BUFSIZE,wskaznik_pliku_in)))
    {
        //printf("Return fread %d\n",n);
        for (i=0; i<n; i++)
            kolejka[SIZECRC+i]=bufor_wejscia[i];
        licznik_bitow=8*n;
        licznik_bajtow_in+=n;

        while (licznik_bitow)
        {
            licznik_buforu=1+(licznik_bitow-1)/8;
            //printf("Liczba bitow %d. Licznik buforu %d. \n", licznik_bitow, licznik_buforu);
            pierwszy_bit=maska&kolejka[0];

            for (i=0; i<SIZECRC+licznik_buforu; i++)
            {
                kolejka[i]=(kolejka[i]<<1);
                ostatni_bit=kolejka[i+1]>>7;
                kolejka[i]=kolejka[i]|ostatni_bit;
                //printf("Bajt %d kolejki po przesunieciu: %#x\n", i, kolejka[i]);
            }
            if (pierwszy_bit!=0)  //jesli pierwszy bit jest jedynka
                for(i=0; i<SIZECRC; i++)
                {
                    kolejka[i]=kolejka[i]^wielomian[i];
                    //printf("Bajt %d kolejki po xorowaniu: %#x\n", i, kolejka[i]);
                }
            licznik_bitow--;

        } // end while
    } // end while

    //printf("Sukcesywne dopisywanie degreegen zer na koncu kolejki.\n");
    licznik_bitow=degreegen;

    while (licznik_bitow>0)
    {
        //printf("Liczba bitow %d\n", licznik_bitow);

        pierwszy_bit=maska&kolejka[0];
        //printf("Pierwszy bit %#x\n", pierwszy_bit);
        for (i=0; i<SIZECRC; i++)
        {
            kolejka[i]=(kolejka[i]<<1);
            ostatni_bit=kolejka[i+1]>>7;
            kolejka[i]=kolejka[i]|ostatni_bit;
        }
        //for(int i=0; i<SIZECRC+n; i++)
        //   printf("Po przesunieciu bajt %d kolejki: %#x\n", i, kolejka[i]);
        //Zero na koncu jest dopisywane z definicji przesuniecia
        if (pierwszy_bit!=0)  //jesli pierwszy bit jest jedynka
            for(i=0; i<SIZECRC; i++)
            {
                kolejka[i]=kolejka[i]^wielomian[i];
                //printf("Bajt %d kolejki po xorowaniu: %#x\n", i, kolejka[i]);
            }
        licznik_bitow--;

    }// end while

    for(i=0; i<SIZECRC; i++)
        reszta[i]=kolejka[i];

    return licznik_bajtow_in;

}

unsigned char * calculateCrc(char *fileName)
{
    unsigned char genPolynomial[SIZECRC];
    unsigned char * restPolynomial =(unsigned char *) malloc (SIZECRC * sizeof (unsigned char));

    genPolynomial[0]=0x00;
    genPolynomial[1]=0x00;
    genPolynomial[2]=0x00;
    genPolynomial[3]=0x0b;

    int bytesCount = dzielenie(fileName, restPolynomial, genPolynomial);
    printf("Signed %d bytes\n", bytesCount);
    return restPolynomial;
}

void printCrcToFile(FILE *fp, unsigned char * crc){
    int i;
    for(i=0; i<SIZECRC; i++){
        fputc(crc[i], fp);
    }
}

void createCrcFile(char * fileName, int crcSizeInBytes, unsigned char crc[]){

    FILE * fp;

    if((fp = fopen(fileName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int c;
    int i;
    for(i=0;i<SIZECRC;i++){
        c = crc[i];
        fputc(c, fp);
    }
    if(fclose(fp) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}
