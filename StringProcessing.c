/***************************************************************
  Student Name: Mikayla Timm
  File Name: StringProcessing.c
  Assignment number 1

 This file exists to perform operations on the strings/characters read in from the files.
 * It will read in all content from the files and tokenize the characters.
***************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Hash.h"
#include "StringProcessing.h"

/*
 * Words struct for holding both the tokenized words taken from the character array master buffer AND word count
 */
struct Words{
	char **tokenizedWords;
	int numWords;
};
/*
 * Initialize Master Buffer creates space in memory for the array that will hold all the chars from the file
 */
char *initializeMasterBuffer(int MAXCHARSPERFILE){
    char *masterBuffer = (char *)malloc(MAXCHARSPERFILE*sizeof(char));
    return masterBuffer;
}

/*
 * NewWords will create a space in memory for all of the words taken from a file and store the count
 * it stores it in a new struct Words, returns the pointer to the struct
 */
WordsP newWords(int MAXCHARSPERFILE, int MAXCHARSPERWORD){
    WordsP words = (WordsP)malloc(sizeof(struct Words));
    if(words == NULL){
        fprintf(stderr, "Memory for words could not be allocated\n");
        return NULL;
    }
    //allocate space for tokenizedWords array
    words->tokenizedWords = (char**) malloc(sizeof(char*) *MAXCHARSPERFILE);
    int i;
    int j;
    for(i = 0; i < MAXCHARSPERFILE; i++){
        words->tokenizedWords[i] = (char *)malloc(MAXCHARSPERWORD*sizeof(char));
        if(words->tokenizedWords[i] == NULL){
            fprintf(stderr, "Memory for tokenizedWords[i] could not be allocated\n");
            return NULL;
        }
    }
    words->numWords = 0; //initialize to 0
    return words;
    
}

/* Two getters for the struct Word. return the array of words and the num of words*/
char **getTokenizedWords(WordsP words){
    return words->tokenizedWords;
}
int getNumWords(WordsP words){
    return words->numWords;
}
/* 
 * Tokenize separates the characters from the file (allChars) into single words
 * the words are then stored in a 2d char array in the words struct
 * */
WordsP tokenize(WordsP words, char *allChars, int MAXCHARSPERFILE, int MAXCHARSPERWORD){
    char *token;
    char *delim = " \r\n\t"; //had to add \r because enter on my keyboard is carriage return, not newline
    //Fill information into words->tokenizedWords from allChars using strtok
    int i = 0;
    token = strtok(allChars, delim);
    while(token != '\0')
    {
            strcpy(words->tokenizedWords[i], token); //put token into current location in tokenizedWords
            strcat(words->tokenizedWords[i], " "); //add space after the word before hashing to maintain spacing
            i++;
        token = strtok(NULL, delim);
    }
    words->numWords = i;
    /*
    int k;
    fprintf(stderr, "Num words: %d\n", words->numWords);
    for(k = 0; k < words->numWords; k++){
        fprintf(stderr, "[%s]", words->tokenizedWords[k]);
    }*/
    
    return words;
}
