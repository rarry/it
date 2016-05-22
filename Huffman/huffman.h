#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#define LETTERS_COUNT   27

struct node{
    int value;
    int letterIndex;
    struct node *left, *right;
};

struct mapEntry{
    int * binaryEncoding;
    char letter;
};

typedef struct node Node;

typedef struct mapEntry Entry;

int findSmallest(Node *nodes[], int skipIndex);

Node * buildHuffmanTree(Node *nodes[]);

Entry ** encodeLetters(Node *tree);

int ** encode(Node *tree, char * text);

int ** decode(Node *tree, char * text);

void compressFile2(char *inputFileName, char * outputFileName, int codeTable[]);

void fillTable(int codeTable[], Node *tree, int code);

void printLetterIndices(Node *nodes[]);

void compressFile(FILE *input, FILE *output, int codeTable[]);

#endif // HUFFMAN_H_INCLUDED
