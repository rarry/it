#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "huffman.h"
#include "crc.h"


#define len(x) ((int)log10(x)+1)

void printNodeValues(Node *nodes[])
{
    int i;
    printf("Node values: ");
    for(i=0; i<LETTERS_COUNT; i++)
    {
        printf("%d ",nodes[i]->value);
    }
    printf("\n");
}

int findSmallest(Node *nodes[], int skipIndex)
{

    int indexOfSmallest = -1;
    int i;
    for(i=0; i<LETTERS_COUNT; i++)
    {

        if(i == skipIndex)
        {
            continue;
        }
        if(nodes[i]->value == -1 || nodes[i]->value == 0)
        {
            continue;
        }
        if(indexOfSmallest == -1 || nodes[i]->value < nodes[indexOfSmallest]->value)
        {
            indexOfSmallest = i;
        }
    }
    return indexOfSmallest;
}

Node * buildHuffmanTree(Node *nodes[])
{
    int i;
    for(i=0; i<LETTERS_COUNT-1; i++)
    {
        int indexOfSmallest = findSmallest(nodes, -1);
        int indexOfSecondSmallest = findSmallest(nodes, indexOfSmallest);

        if(indexOfSmallest < 0 || indexOfSecondSmallest < 0){
            break;
        }
        //printf("smallest: %d\n", indexOfSmallest);
        //printf("second smallest: %d\n", indexOfSecondSmallest);

        Node *smallest = nodes[indexOfSmallest];
        Node *secondSmallest = nodes[indexOfSecondSmallest];

        // merge nodes
        Node *tree = malloc(sizeof(Node));
        tree->value = smallest->value + secondSmallest->value;
        tree->letterIndex = -1;
        tree->left = smallest;
        tree->right = secondSmallest;

        nodes[indexOfSmallest] = tree;
        secondSmallest->value = -1;
        //printNodeValues(nodes);
    }

    Node * tree;
    for(i=0; i<LETTERS_COUNT-1; i++)
    {
        if(nodes[i]->value > 0)
        {
            tree = nodes[i];
            break;
        }
    }

    return tree;
}



void fillTable(int codeTable[], Node *tree, int code)
{
    int letterIndex = tree->letterIndex;
    //int freq = tree->value;
    if(letterIndex >= 0)
    {
        codeTable[letterIndex] = code;
    }
    else
    {
        Node *leftNode = tree->left;
        fillTable(codeTable,leftNode,10*code+1);

        Node *rightNode = tree->right;
        fillTable(codeTable,rightNode,10*code+2);
    }
}

void printLetterIndices(Node *nodes[])
{
    int i;
    for(i=0; i<LETTERS_COUNT; i++)
    {
        printf("%d ", nodes[i]->letterIndex);
    }
    printf("\n");
}

void compress(FILE *input, FILE *output, int codeTable[]){

    char bit, x = 0;
    int bitsLeft = 8;
    int c;
    do
    {
        c = fgetc(input);
        if( feof(input) )
        {
            break ;
        }

        int code = codeTable[c];
        //int orgCode = code;
        int length = len(code);
        //printf("%d\t\t%d\n", code, length);

        //x = 0;
        while(length >0)
        {
            //printf("length %d\n",length);
            length--;

            bit = code % 10 - 1;
            code /= 10;
            //printf("bit %d\n",bit);
            x = x | bit;
            bitsLeft--;
            if(bitsLeft == 0)
            {
                //printf("character %c coded as %d saved as %d (dec), bin= ", c, orgCode,x);
                //printbits(x);
                fputc(x, output);
                bitsLeft = 8;
                x=0;
            }

            x = x << 1;
            //printf("x %d\n",x);
        }
    }
    while(1);

    if(bitsLeft != 8)
    {
        x = x << (bitsLeft-1);
        fputc(x, output);
    }
}

void compressFile(char *inputFileName, char * outputFileName, int codeTable[])
{

    FILE * input;
    FILE * output;

    if((input = fopen(inputFileName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(outputFileName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    compress(input, output, codeTable);

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}



void decompressFile(char *inputFileName, char * outputFileName, Node *root)
{
    FILE * input;
    FILE * output;

    if((input = fopen(inputFileName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(outputFileName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    fseek(input, 0L, SEEK_END);
    int fileSize = ftell(input);
    rewind(input);

    int c;
    //int x = 0;
    int mask = 1 << 7;
    Node * node = root;


    while((c = fgetc(input)) != EOF)
    {
    //int fileIter;
    //for(fileIter=0; fileIter<fileSize - 4; fileIter++)
    //{
    //    c = fgetc(input);


        int i=0;
        for(i=0; i<8; i++)
        {
            int bit = c & mask;
            c = c << 1;

            if(bit == 0)
            {
                node = node->left;
                if(node->letterIndex >= 0)
                {
                    //printf("found %d\n", node->letterIndex);
                    int idx = node->letterIndex;
                    printf("%c", idx);
                    fputc(idx, output);
                    node = root;
                }
            }
            else
            {
                node = node->right;
                if(node->letterIndex >= 0)
                {
                    //printf("found %d\n", node->letterIndex);
                    int idx = node->letterIndex;
                    printf("%c", idx);
                    fputc(idx, output);
                    node = root;
                }
            }
        }
    }

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

void invertCodeTable(int codeTable[],int codeTable2[]){
    int i, n, copy;

    for (i=0;i<LETTERS_COUNT;i++){
        n = codeTable[i];
        copy = 0;
        while (n>0){
            copy = copy * 10 + n %10;
            n /= 10;
        }
        codeTable2[i]=copy;
    }

    return;
}

void calculateFreq(char *from, int freq[]){

    int i=0;
    for(i=0; i<LETTERS_COUNT; i++){
        freq[i] = 0;
    }

    FILE * input;

    if((input = fopen(from, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int c;
    do
    {
        c = fgetc(input);
        if( feof(input) )
        {
            break ;
        }

        freq[c] = freq[c] + 1;
        //printf("Frequency of %d is %d", c, freq[c]);

    }while(1);

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}
