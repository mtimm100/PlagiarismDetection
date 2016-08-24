/***************************************************************
  Student Name: Mikayla Timm
  File Name: ComparingFilesTest.c
  Assignment number 1

 This is the driver file for the ComparingFiles project. It utilizes all of the other files in the project.
 * There are defined constants at the top of the file that are used throughout the project.
 * These were specified in class and adjusted for my algorithm (+1 for null characters, etc).
 * Hashsize was determined based off of the maxcharsperfile. It is a prime number.
 * 
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "StringProcessing.h"
#include "FileIO.h"
#include "Hash.h"

#define MAXNAMELEN 61 //50 is max file name length, plus enough room for "datafiles/" (10) plus 1 for the null character I add at the end
#define MAXFILES 30 //30 is the max number of files to be read in
#define MAXCHARSPERWORD 30 //30 is max number of character in a word
#define MAXCHARSPERFILE 20001 //20000 is the max number of chars in a file, plus null char
#define HASHSIZE 20089 //a large prime number
/*
 * printResults will print all of the similarity values in the upper triangle
 * of the matrix.
 */
void printResults(int **, int);
/*
 * initializeSimilarityMatrix allocates space for the 2d array (similarity matrix) 
 * of size numFiles x numFiles. Returns the pointer to the space.
 */
int **initializeSimilarityMatrix(int);

int main() {
    FILE *inputfile, *file1, *file2;
    int i, j, phraseLength;
    HashP hash;
    do{
        printf("What is the number of words to analyze (2 - 10)? ");
        scanf("%d", &phraseLength);
    }while(phraseLength < 2 || phraseLength > 10);
    
    WordsP words = newWords(MAXCHARSPERFILE, MAXCHARSPERWORD);
    int numFiles = setupInputFile();
    inputfile = openInputFile();
    char** fileNames = getFileNames(inputfile, numFiles, MAXNAMELEN);
    char* masterBuffer = initializeMasterBuffer(MAXCHARSPERFILE);
    int **similarityMatrix = initializeSimilarityMatrix(numFiles);
    
    for(i = 0; i < numFiles; i++){
        //populate masterBuffer with all characters from file
        masterBuffer = getAllChars(masterBuffer, fileNames[i], MAXNAMELEN);
        words = tokenize(words, masterBuffer, MAXCHARSPERFILE, MAXCHARSPERWORD);
        //insert n-word phrases to hash table
        hash = newHash(HASHSIZE);
        hash =  insertPhrases(hash, getTokenizedWords(words), getNumWords(words), phraseLength, MAXCHARSPERWORD);
        for(j = i+1; j < numFiles; j++){
            //process each file j with the current file i
            masterBuffer = getAllChars(masterBuffer, fileNames[j], MAXNAMELEN);
            words = tokenize(words, masterBuffer, MAXCHARSPERFILE, MAXCHARSPERWORD);
            similarityMatrix[i][j] = getSimilarity(hash, getTokenizedWords(words), getNumWords(words), phraseLength, MAXCHARSPERWORD);
        }
        hash = freeHash(hash);
    }
    free(masterBuffer);
    printResults(similarityMatrix, numFiles);
    free(similarityMatrix);
    return 0;
}
//description of function in prototype
void printResults(int **similarityMatrix, int numFiles){
    //display results 5 field for each result
    printf("\n  ");
    int i;
    int j;
    for(i = 0; i < numFiles; i++){
        printf("      f%d", i+1);
    }
    for(i = 0; i < numFiles; i++){
        printf("\nf%d", i+1);
        for(j=0; j < numFiles; j++){
            if(similarityMatrix[i][j] == -1){
                //replace with a -
                printf("       -");
            }
            else{
                printf("%8d", similarityMatrix[i][j]);
            }
        }
    }
    printf("\n");
}
//description of function in prototype
int **initializeSimilarityMatrix(int numFiles){
    int **similarityMatrix = (int**) malloc(sizeof(int*) *numFiles);
    int i;
    int j;
    //allocate space for similarity matrix
    for(i = 0; i < numFiles; i++){
        similarityMatrix[i] = (int *)malloc(numFiles*sizeof(int));
        if(similarityMatrix[i] == NULL){
            fprintf(stderr, "Memory for similarityMatrix[i] could not be allocated\n");
            return NULL;
        }
    }
    //initialize all values to -1. lower triangle of matrix will be replaced with -'s at the end
    for(i = 0; i < numFiles; i++){
        for(j=0; j< numFiles; j++){
            similarityMatrix[i][j] = -1;
        }
    }
    return similarityMatrix;
}