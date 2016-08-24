/***************************************************************
  Student Name: Mikayla Timm
  File Name: Hash.h - Adapted from DSA1 Hash project with Mr. Lewis
  Assignment number 1

 Hash.h is the header file for Hash.c. It allows the ComparingFilesTest.c file to
 * utilize Hash operations by creating a hash table. This file outlines the 
 * functions implemented in Hash.c.
***************************************************************/
 
#ifndef _hash_h
#define _hash_h

/*
 * Definition for a pointer to a Hash struct.
 */
typedef struct Hash *HashP;

/*
 * Hash Interface
 */

/*
 * Returns a pointer to a new empty Hash
 * Parameters: integer indicating desired size of table
 * If memory cannot be allocated, returns a NULL pointer
 */
HashP newHash(int);

/*
 * Locates and displays the desired contact from the hash table
 * If entry is not found, display an appropriate message
 * Parameters: hash, phrase, similarities
 */
int findMatchesHash(HashP, char *, int);

/*
 * Creates a new entry for the hash table using provided data
 * Parameters: hash, phrase, phrase length
 */
void insertHash(HashP, char *, int);

/*
 * Removes the entry containing the matching names
 * Parameters: hash, phrase
 */
void removeHash(HashP, char *);

/*
 * Displays all the entries in the hash table
 * Note: they need not be in any order
 */
void displayHash(HashP);

/*
 * Displays statistics for hash table
 *      Key count
 *      Bucket count (table size)
 *      Used bucket count
 *      Empty bucket count
 *      Collision count
 *      Longest chain length
 *      Average chain length of "used" buckets
 * Parameters: hash
 */
void displayStatisticsHash(HashP);

/*
 * Frees the memory used by this hash
 * Frees all the nodes
 * Parameters: hash
 * Returns NULL
 */
HashP freeHash(HashP);

/*
 * insertPhrases extracts phraseLength-word phrases from the tokenizedWords character array
 * and inserts them into the hash table. Returns a pointer to the hash
 */
HashP insertPhrases(HashP, char **, int, int, int);
/*
 * getSimilarity extracts phraseLength-word phrases from the tokenizedWords array and
 * looks up the phrases in the hash table. it returns a similarity value for that file.
 */
int getSimilarity(HashP, char **, int, int, int);

#endif
