/***************************************************************
  Student Name: Mikayla Timm
  File Name: FileIO.c
  Assignment number 1

 This file exists to perform file operations, including obtaining the datafiles
 * used in the project, opening data files, and reading in characters from the 
 * data files.
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileIO.h"

/*
 * Performs the setup of the inputfile for reading the data files in the datafiles subfolder,
 * along with getting the number of files in the subfolder for use later.
 * Uses 2 system commands to accomplish this.
 */
int setupInputFile(){
    FILE *filecount;
    int numFiles = 0;
    system("ls ./datafiles/ > inputfile.txt");
    system("ls ./datafiles/ | wc -l > filecount.txt");
    filecount = fopen("filecount.txt", "r");
    fscanf(filecount, "%d", &numFiles);
    return numFiles;
}
/*
 * Opens the input file containing all the data filenames. returns file pointer to the file.
 */
FILE *openInputFile(){
    FILE *inputfile = fopen("inputfile.txt", "r");
    if(inputfile == NULL){
        fprintf(stderr, "Cannot open input file - exiting!\n");
        exit(1);
    }
    return inputfile;
}
/*
 * getFileNames gets the filenames from the inputfile and puts them into a 2D 
 * character array for opening later.
 */
char **getFileNames(FILE *inputfile, int numFiles, int MAXNAMELEN){
    //allocate space for fileNames array
    int i;
    int j;
    char** fileNames = (char**) malloc(sizeof(char*) *numFiles);
    for(i = 0; i < numFiles; i++){
        fileNames[i] = (char *)malloc(MAXNAMELEN*sizeof(char));
    }   
    //Fill information in from inputfile
    for(i = 0; i < numFiles; i++){
        j = 0;
        while((fileNames[i][j] = fgetc(inputfile)) != '\n'){
            j++; //character was not newline, increment to next char
        }
        //found newline. replace with null char.
        fileNames[i][j] = '\0';
    }
    return fileNames;
}

/*
 * getAllChars gets all of the characters from 1 file (filename) and puts them into the
 * masterBuffer character array.
 */
char *getAllChars(char *masterBuffer, char *filename, int MAXNAMELEN){
    //open the file with directory name in front
    char filePath[MAXNAMELEN];
    const char *directory = "datafiles/";
    strcpy(filePath, directory);
    strcat(filePath, filename);
    FILE *fileP = fopen(filePath, "r");
    //fprintf(stderr, "[%s]", filePath);
    if(fileP == NULL){
        fprintf(stderr, "Error: Could not open %s. Exiting.\n", filePath);
        exit(1);
    }
    int i = 0;
    while ((masterBuffer[i] = fgetc(fileP)) != EOF){
        //fprintf(stderr, "masterBuffer[%d] = [%c]\n",i,masterBuffer[i]);
        i++;
    }
    masterBuffer[i] = '\0'; //replace last char with null char 
    fclose(fileP); //finished with reading file. close.
    return masterBuffer;
}

/*
 * freeFileNames frees the space allocated for the fileNames array.
 */
char **freeFileNames(char **fileNames, int numFiles){
    int i;
    for(i = 0; i < numFiles; i++){
        free(fileNames[i]);
    }
    free(fileNames);
    return fileNames;
}
