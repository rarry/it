#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#define LETTERS_COUNT   255

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

void fillTable(int codeTable[], Node *tree, int code);

void printLetterIndices(Node *nodes[]);

void compressFile(char *inputFileName, char * outputFileName, int codeTable[]);

void decompressFile(char *inputFileName, char * outputFileName, Node *root);

void invertCodeTable(int codeTable[],int codeTable2[]);

void calculateFreq(char *from, int freq[]);

#endif // HUFFMAN_H_INCLUDED
