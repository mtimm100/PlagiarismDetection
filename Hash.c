
/***************************************************************
  Student Name: Mikayla Timm
  File Name: Hash.c - Adapted from DSA1 Hash project with Mr. Lewis
  Assignment number 1

 Hash.c exists to create a hash that allows for efficient lookup of the phrases
 * from the files. Hash operations are implemented here, including finding matches 
 * to evaluate similarity, inserting into hash, removing, freeing, as well as other functions that were 
 * utilized in a previous project (displayStatistics).
***************************************************************/

#include "Hash.h"
#include "Node.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Definition for a pointer to a Hash struct.
 * //size of array determined by newHash function. parameter
 */
int hashFunction(HashP, char phrase[]);

struct Hash{
    int size;
    NodeP* hashTable;   
};

/*
 * Hash Interface
 */

/*
 * Returns a pointer to a new empty Hash
 * Parameters: integer indicating desired size of table
 * If memory cannot be allocated, returns a NULL pointer
 */
HashP newHash(int s){
    HashP hash = (HashP)malloc(sizeof(struct Hash));
    if(hash == NULL){
        fprintf(stderr, "Memory for hash could not be allocated\n");
        return NULL;
    }
    hash->hashTable = (NodeP*)(malloc(s*sizeof(NodeP)));
    if(hash->hashTable == NULL){
        fprintf(stderr, "Memory for hash TABLE could not be allocated\n");
        return NULL;
    }
    hash->size = s;
    return hash;
}

/*
 * Locates and displays the desired phrase from the hash table, increments number similarities
 * If entry is not found, display an appropriate message
 * Parameters: hash, phrase to find
 */
int findMatchesHash(HashP hashPtr, char *phraseToFind, int similarities){
    int index = hashFunction(hashPtr, phraseToFind);
    //fprintf(stderr, "Index of [%s] is %d\n", phraseToFind, index);
    int previousSimCount = similarities;
    NodeP ptr = hashPtr->hashTable[index];
    while(ptr != NULL){
        //fprintf(stderr, "ptr->phrase is %s\n", getPhrase(ptr));
        if(comparePhrases(phraseToFind, getPhrase(ptr)) == 0){
            //displayNodeInfo(ptr);
            similarities++;
            //fprintf(stderr, "Found [%s] in table, matched with [%s]\n",phraseToFind, getPhrase(ptr));
            //fprintf(stderr, "similarities: %d\n", similarities);
            return similarities;
            //ptr = ptr->R;
        }
        else{
            ptr = ptr->R;
        }
    }
    //if(previousSimCount == similarities) fprintf(stderr, "Did not find %s in hash table.\n", phraseToFind);
    return similarities;
}

/*
 * Creates a new entry for the hash table using provided data
 * Parameters: hash, phrase
 */
void insertHash(HashP hashPtr, char *phrase, int phraseLength){
    int index = hashFunction(hashPtr, phrase);
    
    NodeP* ptr = &(hashPtr->hashTable[index]);
    while((*ptr) != NULL){
        ptr = &((*ptr)->R);
    }
    *ptr = newNode(phrase, phraseLength);
    //fprintf(stderr,"Inserted %s at %d\n", phrase, index);
}

/*
 * Removes the entry containing the matching phrase
 * Parameters: hash, phrase to remove
 */
void removeHash(HashP hashPtr, char *phraseToRemove){
    int index = hashFunction(hashPtr, phraseToRemove);
    int i = 0;
    NodeP* ptr = &(hashPtr->hashTable[index]);
    NodeP temp;
    while(i < hashPtr->size){
        while((*ptr) != NULL){
            if(comparePhrases(phraseToRemove, (*ptr)->phrase) == 0){
                //found it, remove
                temp = (*ptr)->R;
                *ptr = freeNode(*ptr);
                (*ptr) = temp;
                return;
            }
            else{
                ptr = &((*ptr)->R);
            }
        }
        i++;
    }
    //didn't find if it comes to this point
    fprintf(stderr, "\nCannot remove %s from hash table (not found).\n", phraseToRemove);
    return;
}

/*
 * Displays all the entries in the hash table
 * Note: they need not be in any order
 */
void displayHash(HashP hashPtr){
    int i;
    NodeP ptr;
    for(i = 0; i < hashPtr->size; i++){
        ptr = hashPtr->hashTable[i];
        while(ptr != NULL){
            displayNodeInfo(ptr);
            ptr = ptr->R;
        }
    }
}

/*
 * Displays statistics for hash table
 *      Key count
 *      Bucket count (table size)
 *      Used bucket count
 *      Empty bucket count
 *      Collision count
 *      Longest chain length
 *      Average chain length of "used" buckets - ???? keys / usedCount?
 * Parameters: hash
 */
void displayStatisticsHash(HashP hashPtr){
    int i;
    NodeP ptr;
    int keyCount = 0, usedCount = 0, emptyCount = 0, collisionCount = 0, longestChainLen = 0;
    int currentChain;
    double averageChainLen;
    for(i = 0; i < hashPtr->size; i++){
        ptr = hashPtr->hashTable[i];
        if(ptr != NULL){
            currentChain = 0; //start new chain at 0
            usedCount++; //add one to used bucket count
            while(ptr != NULL){
                if(currentChain > 0){
                    collisionCount++;
                }
                keyCount++;
                currentChain++;
                ptr = ptr->R;
            }
            if(currentChain > longestChainLen){ //if that chain was longer than longest chain so far, set it to the longest
                longestChainLen = currentChain;
            }
        }
        else{
            emptyCount++;
        }
    }
    if(usedCount == 0){
        averageChainLen = 0;
    }
    else{
        averageChainLen = (double)keyCount/usedCount;
    }
    printf("Statistics\n");
    printf("Key Count:                  %d\n", keyCount);
    printf("Bucket Count (table size):  %d\n", hashPtr->size);
    printf("Used bucket count:          %d\n", usedCount);
    printf("Empty bucket count:         %d\n", emptyCount);
    printf("Longest chain length:       %d\n", longestChainLen);
    printf("Average chain length:       %lf\n", averageChainLen);
    
}

/*
 * calculates an index for the key
 */
int hashFunction(HashP hashPtr, char phrase[]){
    int total = 1;
    int len = strlen(phrase);
    int i;
    for(i = 0; i < len; i++){
        total += phrase[i]*(i+1);
    }
    if (total < 0){ //arithmetic overflow, multiply by -1
        total = total * -1;
    }
    return total % hashPtr->size;
}
/*
 * Frees the memory used by this hash
 * Frees all the nodes
 * Parameters: hash
 * Returns NULL
 */
HashP freeHash(HashP hashPtr){ //collisions, size, 
    int i;
    NodeP ptr;
    NodeP temp;
    for(i = 0; i < hashPtr->size; i++){
        ptr = hashPtr->hashTable[i];
        while(ptr != NULL){
            temp = ptr->R;
            freeNode(ptr);
            ptr = temp;
        }
    }    
    free(hashPtr);
    return NULL;
}

/*
 * insertPhrases extracts phraseLength-word phrases from the tokenizedWords character array
 * and inserts them into the hash table. Returns a pointer to the hash
 */
HashP insertPhrases(HashP hash, char **tokenizedWords, int numWords, int phraseLength, int MAXCHARSPERWORD){
    int i;
    int j;
    int maxSizeOfPhrase = MAXCHARSPERWORD*phraseLength + phraseLength; //add phraseLength for added spaces
    char *phrase = (char *)malloc((maxSizeOfPhrase)*sizeof(int));
    for(i = 0; i <= (numWords-phraseLength); i++){
        //keep track of where you are starting with i. copy first word in
        strcpy(phrase, tokenizedWords[i]);
        for(j = 1; j < phraseLength; j++){
            strcat(phrase, tokenizedWords[i+j]);
        }
        //insert phrase into hash
        //fprintf(stderr, "Phrase to insert: [%s]\n", phrase);
        insertHash(hash, phrase, phraseLength);
    }
    return hash;
}
/*
 * getSimilarity extracts phraseLength-word phrases from the tokenizedWords array and
 * looks up the phrases in the hash table. it returns a similarity value for that file.
 */
int getSimilarity(HashP hash, char **tokenizedWords, int numWords, int phraseLength, int MAXCHARSPERWORD){
    int i;
    int j;
    int similarity = 0;
    int maxSizeOfPhrase = MAXCHARSPERWORD*phraseLength + phraseLength; //add phraseLength for added spaces
    char *phrase = (char *)malloc((maxSizeOfPhrase)*sizeof(char));
    for(i = 0; i <= (numWords-phraseLength); i++){
        //keep track of where you are starting with i. copy first word in
        strcpy(phrase, tokenizedWords[i]);
        for(j = 1; j < phraseLength; j++){
            strcat(phrase, tokenizedWords[i+j]);
        }
        //find similarity by finding matches in hash table
        //fprintf(stderr, "Searching for [%s] in hash.\n", phrase);
        similarity = findMatchesHash(hash, phrase, similarity);
    }
    return similarity;
}