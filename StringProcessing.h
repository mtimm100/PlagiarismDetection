/***************************************************************
  Student Name: Mikayla Timm
  File Name: StringProcessing.h
  Assignment number 1

 Header file for StringProcessing.c. Outlines the functions implemented in the .c file.
 * StringProcessing.c exists to perform operations on the strings/characters read in from the files.
 * It will read in all content from the files and tokenize the characters.
***************************************************************/
 
#ifndef _stringprocessing_h
#define _stringprocessing_h

typedef struct Words *WordsP;

/*
 * Initialize Master Buffer creates space in memory for the array that will hold all the chars from the file
 */
char *initializeMasterBuffer(int MAXCHARSPERFILE);
/*
 * NewWords will create a space in memory for all of the words taken from a file and store the count
 * it stores it in a new struct Words, returns the pointer to the struct
 */
WordsP newWords(int MAXCHARSPERFILE, int MAXCHARSPERWORD);
/* Two getters for the struct Word. return the array of words and the num of words*/
char **getTokenizedWords(WordsP words);
int getNumWords(WordsP words);
/* 
 * Tokenize separates the characters from the file (allChars) into single words
 * the words are then stored in a 2d char array in the words struct
 * */
WordsP tokenize(WordsP words, char *allChars, int MAXCHARSPERFILE, int MAXCHARSPERWORD);



#endif