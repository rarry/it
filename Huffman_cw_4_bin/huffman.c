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



void compressFile(char *inputFileName, char * outputFileName, int codeTable[])
{
	printf("Compressing file %s\n", inputFileName);
}



void decompressFile(char *inputFileName, Node *root)
{
	printf("Decompressing file %s\n", inputFileName);
}


