/***************************************************************
  Student Name: Mikayla Timm
  File Name: Node.h - Adapted from DSA1 Hash project with Mr. Lewis
  Assignment number 1

 Node.h is the header file for Node.c. This file outlines all of the functions 
 * implemented in Node.c. The Hash file utilizes this header file for
 * performing node operations.
***************************************************************/

#ifndef NODE_H
#define	NODE_H

/*
 * Defines a pointer to one node struct
 */

typedef struct Node *NodeP;
/*
 * Defines node struct
 */
struct Node
{
    NodeP L;
    NodeP R;
    char *phrase;
};

/* Creates a new node with a char *phrase.
 * Phrase length (int) must be specified in order to allocate enough space for
 * the phrase in the node.
 */
NodeP newNode(char *,int);
/* 
 * Getters and setters for Left node pointer, Right node pointer, and phrase
 */
NodeP getLeft(NodeP);
void setLeft(NodeP, NodeP);
NodeP getRight(NodeP);
void setRight(NodeP, NodeP);
char *getPhrase(NodeP);
//void setInfo(NodeP, char *); 
/* 
 * Display function used mostly for debugging in this project.
 */
void displayNodeInfo(NodeP);
/* 
 * Free node frees the space allocated for the node from newNode.
 */
NodeP freeNode(NodeP);
/*Compares two phrases to see if they are the same.
 * Returns:
 *    negative if phraseToFind < current
 *    zero if phraseToFind == current
 *    positive if phraseToFind > current
 */
int comparePhrases(char *, char *);

#endif	/* NODE_H */

