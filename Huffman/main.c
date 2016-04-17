#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "huffman.h"

int main()
{
    printf("Hello world!\n");
    int lettersFrequencies[LETTERS_COUNT] = {81, 15, 28, 43, 128, 23, 20, 61, 71, 2, 1, 40, 24, 69, 76, 20, 1, 61, 64, 91, 28, 10, 24, 1, 20, 1, 130};;
    char letters[LETTERS_COUNT] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
    printTabInt(lettersFrequencies, LETTERS_COUNT);
    printTabChar(letters, LETTERS_COUNT);

    printf("Letter indices: ");



    Node *nodes[LETTERS_COUNT];
    int i;
    for(i=0; i<LETTERS_COUNT; i++){
        nodes[i] = malloc(sizeof(Node));
        nodes[i]->value = lettersFrequencies[i];
        nodes[i]->letterIndex = i;
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    printLetterIndices(nodes);
    Node *tree = buildHuffmanTree(nodes);

    int codeTable[LETTERS_COUNT];
    fillTable(codeTable, tree, 0);

    printf("codeTable: ");
    printTabInt(codeTable, LETTERS_COUNT);
    return 0;
}
