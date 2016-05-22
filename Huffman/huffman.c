#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "huffman.h"

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
        if(nodes[i]->value == -1)
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
        printf("smallest: %d\n", indexOfSmallest);
        printf("second smallest: %d\n", indexOfSecondSmallest);

        Node *smallest = nodes[indexOfSmallest];
        Node *secondSmallest = nodes[indexOfSecondSmallest];

        // merge nodes
        Node *tree = malloc(sizeof(Node));
        tree->value = smallest->value + secondSmallest->value;
        tree->letterIndex = 127;
        tree->left = smallest;
        tree->right = secondSmallest;

        nodes[indexOfSmallest] = tree;
        secondSmallest->value = -1;
        printNodeValues(nodes);
    }

    Node * tree;
    for(i=0; i<LETTERS_COUNT-1; i++)
    {
        if(nodes[i]->value >= 0)
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
    if(letterIndex < 27)
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



void compressFile2(char *inputFileName, char * outputFileName, int codeTable[])
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
    char bit, x = 0,code;
    int bitsLeft = 8;
    int c;
    do
    {
        c = fgetc(input);
        if( feof(input) )
        {
            break ;
        }


        int code = codeTable[c-97];
        int length = len(code);
        printf("%d\t\t%d\n", code, length);

        x = 0;
        while(length >0)
        {
            printf("length %d\n",length);
            length--;

            bit = code % 10 - 1;
            code /= 10;
            printf("bit %d\n",bit);
            x = x | bit;
            bitsLeft--;
            if(bitsLeft == 0)
            {
                fputc(x, output);
                bitsLeft = 8;
                x=0;
            }

            x = x << 1;
            printf("x %d\n",x);
        }
    }
    while(1);

    if(bitsLeft != 8)
    {
        x = x << (bitsLeft-1);
        fputc(x, output);
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



void decompressFile(char *inputFileName, Node *root)
{
    FILE * input;

    if((input = fopen(inputFileName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int c;
    int x = 0;
    int mask = 1 << 7;
    Node * node = root;

    while((c = fgetc(input)) != EOF)
    {
        int i=0;
        for(i=0; i<8; i++)
        {
            int bit = c & mask;
            c = c << 1;

            if(bit == 0)
            {
                node = node->left;
                if(node->letterIndex < 27)
                {
                    printf("found %d\n", node->letterIndex);
                    printf("%c\n", node->letterIndex+97);
                    node = root;
                }
            }
            else
            {
                node = node->right;
                if(node->letterIndex < 27)
                {
                    printf("found %d\n", node->letterIndex);
                    printf("%c\n", node->letterIndex+97);
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
}


/*function to compress the input*/
void compressFile(FILE *input, FILE *output, int codeTable[])
{
    char bit, c, x = 0;
    int n,length,bitsLeft = 8;
    int originalBits = 0, compressedBits = 0;

    while ((c=fgetc(input))!=10)
    {
        originalBits++;
        if (c==32)
        {
            length = len(codeTable[26]);
            n = codeTable[26];
        }
        else
        {
            length=len(codeTable[c-97]);
            n = codeTable[c-97];
        }

        while (length>0)
        {
            compressedBits++;
            bit = n % 10 - 1;
            n /= 10;
            x = x | bit;
            bitsLeft--;
            length--;
            if (bitsLeft==0)
            {
                fputc(x,output);
                x = 0;
                bitsLeft = 8;
            }
            x = x << 1;
        }
    }

    if (bitsLeft!=8)
    {
        x = x << (bitsLeft-1);
        fputc(x,output);
    }

    /*print details of compression on the screen*/
    fprintf(stderr,"Original bits = %dn",originalBits*8);
    fprintf(stderr,"Compressed bits = %dn",compressedBits);
    fprintf(stderr,"Saved %.2f%% of memoryn",((float)compressedBits/(originalBits*8))*100);

    return;
}
