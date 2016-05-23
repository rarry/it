#include<stdlib.h>
#include <stdio.h>

#define BUFSIZE 1000
#define kropka 46



struct galaz
{
       int ojciec;
       int potomek1;
       int potomek2;
};
struct galaz drzewo_kodowania[255];


int nazwa_pliku(char *nazwa_pliku, char *rozszerzenie, char *nazwa_pliku_nowa) 
{
    int i,n;
   	char *w_nazwy;
    
    for (n=0; n<24; n++)
       nazwa_pliku_nowa[n]=0;

    n=0;
    w_nazwy=nazwa_pliku;
    nazwa_pliku_nowa[n]=*w_nazwy;
    while ((nazwa_pliku_nowa[n]!=kropka)&&(nazwa_pliku_nowa[n]!='\0'))
           {
           n++;
           w_nazwy++;
           nazwa_pliku_nowa[n]=*w_nazwy;
           }
    n++;
    i=0;
    nazwa_pliku_nowa[n]=rozszerzenie[i];
    while (rozszerzenie[i]!='\0')
           {
           n++;
           i++;
           nazwa_pliku_nowa[n]=rozszerzenie[i];
           }         
    return 0;
}    

int czytaj_drzewo( char *nazwapliku_drzewo, struct galaz drzewo_kodowania[])
{
int licz_galezie;
int pater,syn1,syn2;
    
    FILE *wskaznik_pliku=NULL;
	wskaznik_pliku=fopen(nazwapliku_drzewo,"rb"); 

    if (wskaznik_pliku == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", nazwapliku_drzewo);
		exit(EXIT_FAILURE);
	}
	else
	{
    licz_galezie=0;
    printf("Odczyt drzewa kodowania z pliku: %s  \n", nazwapliku_drzewo);    
//Format zapisu do pliku byl nastepujacy
//fprintf(wskaznikpliku_drzewo, "%d %d %d\n ", drzewo_kodowania[k].ojciec, drzewo_kodowania[k].potomek1, drzewo_kodowania[k].potomek2 );  

    while (fscanf(wskaznik_pliku,"%d %d %d\n", &pater, &syn1,&syn2)!=EOF)
    {
      //printf("%d %d %d\n ", pater, syn1,syn2);     
 
      drzewo_kodowania[licz_galezie].ojciec=pater;
      drzewo_kodowania[licz_galezie].potomek1=syn1;
      drzewo_kodowania[licz_galezie].potomek2=syn2;
      licz_galezie++;
     }
    printf("liczba odczytanych galezi drzewa: %d\n", licz_galezie);
    }
    fclose(wskaznik_pliku);
    return (licz_galezie);
}   


int dekompresja(char *nazwa_pliku_skom, char *nazwa_pliku_dekom, struct galaz drzewo_kodowania[], int liczba_galezi_drzewa, int ile_symboli)
{
    unsigned char bajt_out, bit1, bajt_in;
    int m,n,suma_symboli=0,suma_bitow=0;
    int indeks_drzewa;
    int kursor_in;//pozycja bitu w bajcie wejsciowym
    int pater, syn1, syn0;;
    unsigned char maska=128;

    FILE *wskaznik_pliku_skom=NULL;
	wskaznik_pliku_skom=fopen(nazwa_pliku_skom,"rb"); 

    if (wskaznik_pliku_skom == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", nazwa_pliku_skom);
		exit(EXIT_FAILURE);
	}
    
 
    FILE *wskaznik_pliku_dekom=NULL;
	wskaznik_pliku_dekom=fopen(nazwa_pliku_dekom,"wb"); 

    if (wskaznik_pliku_dekom == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", nazwa_pliku_dekom);
		exit(EXIT_FAILURE);
	}
		
    printf( "Czytanie pliku skompresowanego %s po jednym bajcie. \n", nazwa_pliku_skom); 
    printf( "Po zdekodowaniu pisanie bajtu do pliku %s. \n", nazwa_pliku_dekom); 	
    
    suma_symboli=0;
    indeks_drzewa=liczba_galezi_drzewa-1;
    pater=drzewo_kodowania[indeks_drzewa].ojciec;
    syn1=drzewo_kodowania[indeks_drzewa].potomek1;
    syn0=drzewo_kodowania[indeks_drzewa].potomek2;
    
    //printf("Tyle ma byc bajtow po zdekodowaniu:  %d a tyle zdekodowano: %d\n", ile_bajtow, suma_symboli); 
            
    while(suma_symboli<ile_symboli) 
    {
    //printf("Tyle ma byc bajtow:  %d a tyle juz zdekodowano: %d\n", ile_bajtow, suma_symboli);                               
    n=fread(&bajt_in,sizeof(unsigned char),1,wskaznik_pliku_skom);             
    if (n==1)
      {
        for (int k=0;k<8; k++)
        {
            bit1=bajt_in&maska;
            //printf("Galaz %d %d %d  bajt_in %x bit1 %x\n",pater, syn1, syn0, bajt_in, bit1);
            bajt_in=bajt_in<<1;
            suma_bitow++;
            if (bit1)
              pater=syn1;
            else
              pater=syn0;
            
            if (pater<256)
            {
               bajt_out=pater;
               //printf("Galaz %d %d %d symbol %d\n",pater, syn1, syn0, bajt_out);
               fwrite(&bajt_out,sizeof(unsigned char),1,wskaznik_pliku_dekom);
               suma_symboli++;
               indeks_drzewa=liczba_galezi_drzewa-1;
               pater=drzewo_kodowania[indeks_drzewa].ojciec;
               syn1=drzewo_kodowania[indeks_drzewa].potomek1;
               syn0=drzewo_kodowania[indeks_drzewa].potomek2; 
               if (suma_symboli == ile_symboli)
               break;//wyjscie z for         
            }
            else
            {
            m=liczba_galezi_drzewa-1;
            while (m>=0)
            {
               if  (drzewo_kodowania[m].ojciec==pater)
               {
                 indeks_drzewa=m;
                 m=-1;                                   
               } 
               m=m-1;
            }        
            //pater=drzewo_kodowania[indeks_drzewa].ojciec;
            syn1=drzewo_kodowania[indeks_drzewa].potomek1;
            syn0=drzewo_kodowania[indeks_drzewa].potomek2;
            }//end else
          }//end for
        } //end if
      }//end while  

      printf("Liczba odczytanych bitow: %d, liczba zdekodowanych symboli %d.\n", suma_bitow, suma_symboli);       
      fclose(wskaznik_pliku_skom);
      fclose(wskaznik_pliku_dekom);
      
      return (suma_symboli);
}     
        
int main(int argc, char *argv[])
{

    char rozszerzenie_d[]= "tree";
    char rozszerzenie_ile[]= "ile";
    char nazwapliku_drzewo[24];
    char *nazwa_pliku_dekom;
    char *nazwa_pliku_skom;
    char nazwa_ile[24];
    int liczba_galezi_drzewa=0;
    int ile_bajtow_ma_byc, ile_bajtow_zrobiono;
 	
    int n;
   	
          
    if(argc==3)
      {
        nazwa_pliku_skom=argv[1];
        nazwa_pliku_dekom=argv[2];
        printf("Parametry programu:  %d   %s  %s \n",  argc, nazwa_pliku_skom, nazwa_pliku_dekom);
        
      }
	else
    {
   		printf("Zla liczba parametrow.  ","%d", argc);
		exit(EXIT_FAILURE);
    }

    
    n=nazwa_pliku(nazwa_pliku_skom, rozszerzenie_d,nazwapliku_drzewo);
    liczba_galezi_drzewa = czytaj_drzewo( nazwapliku_drzewo, drzewo_kodowania);

    if (liczba_galezi_drzewa>0)
     printf("Drzewo kodowania odczytane z pliku %s\n", nazwapliku_drzewo);
    else
    {
     printf("Odczytanie drzewa kodowania z pliku %s nie powiodlo sie.\n", nazwapliku_drzewo);
     exit(EXIT_FAILURE);
    }
   
    n=nazwa_pliku(nazwa_pliku_skom, rozszerzenie_ile,nazwa_ile);
    FILE *wskaznik_ile=NULL;
	wskaznik_ile=fopen(nazwa_ile,"rb"); 
    if (wskaznik_ile == NULL)
	{
		printf("Nie mozna otworzyc pliku: %s  \n", nazwa_ile);
		exit(EXIT_FAILURE);
	}
	else
	{
      printf("Odczyt, ile bajtow nalezy odkodowac, z pliku: %s\n", nazwa_ile);    
      n=fscanf(wskaznik_ile,"%d\n",&ile_bajtow_ma_byc);
      printf("Tyle bajtow nalezy odkodowac: %d\n", ile_bajtow_ma_byc);     
    }
    fclose(wskaznik_ile);
    
    ile_bajtow_zrobiono=dekompresja(nazwa_pliku_skom, nazwa_pliku_dekom,drzewo_kodowania,liczba_galezi_drzewa, ile_bajtow_ma_byc);
    
    
    if (ile_bajtow_zrobiono==ile_bajtow_ma_byc)
      printf("Liczba bajtow prawidlowa. Wynik dekompresji zapisany do pliku: %s. \n\n\n", nazwa_pliku_dekom);
    else
      printf("Liczba bajtow nieprawidlowa. Wynik dekompresji zapisany do pliku: %s. \n\n\n", nazwa_pliku_dekom);

    return 0;
} 
