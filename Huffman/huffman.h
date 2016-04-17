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

void fillTable(int codeTable[], Node *tree, int code);

void printLetterIndices(Node *nodes[]);

#endif // HUFFMAN_H_INCLUDED
