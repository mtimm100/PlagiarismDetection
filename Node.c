/***************************************************************
  Student Name: Mikayla Timm
  File Name: Node.c - Adapted from DSA1 Hash project with Mr. Lewis
  Assignment number 1 

 Node.c exists to create new nodes to be inserted into the hash table, along with getting/setting/comparing
 * operations on the node's contents. The node contains a phrase (character array) and a left
 * and right node pointer.
***************************************************************/
#include "Node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHARSPERWORD 30

NodeP newNode(char *phrase, int phraseLength){
    NodeP nodePtr = (NodeP)malloc(sizeof(struct Node));
    if(nodePtr == NULL ) 
    {
        fprintf(stderr, "\nNode allocation failed.\n");
        return NULL;
    }
    int maxSizeOfPhrase = MAXCHARSPERWORD*phraseLength + phraseLength; //add phraseLength for added spaces
    nodePtr->phrase = (char *)malloc((maxSizeOfPhrase)*sizeof(int));
    strcpy(nodePtr->phrase, phrase); //set node's phrase to point at phrase
    nodePtr->L = NULL;
    nodePtr->R = NULL;
    return nodePtr;
}
NodeP getLeft(NodeP node){
    return node->L;
}
void setLeft(NodeP node, NodeP newLeftNode){
    node->L = newLeftNode;
}
NodeP getRight(NodeP node){
    return node->R;
}
void setRight(NodeP node, NodeP newRightNode){
    node->R = newRightNode;
}
char *getPhrase(NodeP node){
    return node->phrase;
}
void displayNodeInfo(NodeP node){ //not sure if need
    fprintf(stderr, "%s\n", node->phrase);
}
NodeP freeNode(NodeP node){
    free(node); //then free the node
    return NULL;
}
/*Compares two phrases to see if they are the same.
 * Returns:
 *    negative if phraseToFind < current
 *    zero if phraseToFind == current
 *    positive if phraseToFind > current
 */
int comparePhrases(char *phraseToFind, char *currentPhrase){
    return strcmp(phraseToFind, currentPhrase);
}


