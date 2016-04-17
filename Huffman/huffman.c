#include "utils.h"
#include "huffman.h"

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
        if(indexOfSmallest == -1 || nodes[i]->value < nodes[indexOfSmallest]->value){
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
    for(i=0; i<LETTERS_COUNT-1; i++){
        if(nodes[i]->value >= 0){
            tree = nodes[i];
            break;
        }
    }

    return tree;
}



void fillTable(int codeTable[], Node *tree, int code){
    int letterIndex = tree->letterIndex;
    if(letterIndex < 27){
        codeTable[letterIndex] = code;
    }else{
        Node *leftNode = tree->left;
        int leftValue = leftNode->value;
        int leftLetterIndex = leftNode->letterIndex;

        fillTable(codeTable,leftNode,10*code+1);

        Node *rightNode = tree->right;
        int rightValue = rightNode->value;
        int rightLetterIndex = rightNode->letterIndex;
        fillTable(codeTable,rightNode,10*code+2);
    }
}

void printLetterIndices(Node *nodes[]){
    int i;
    for(i=0; i<LETTERS_COUNT; i++){
        printf("%d ", nodes[i]->letterIndex);
    }
    printf("\n");
}
