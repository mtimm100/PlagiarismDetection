/***************************************************************
  Student Name: Mikayla Timm
  File Name: FileIO.h
  Assignment number 1

 This is the header file for FileIO.c. It outlines the functions used in FileIO.c
 * FileIO.c exists to perform file operations, such as obtaining access to the files,
 * opening the files, and reading content in from the files.
***************************************************************/
 
#ifndef _fileio_h
#define _fileio_h


/*
 * Performs the setup of the inputfile for reading the data files in the datafiles subfolder,
 * along with getting the number of files in the subfolder for use later.
 * Uses 2 system commands to accomplish this.
 */
int setupInputFile();
/*
 * Opens the input file containing all the data filenames. returns file pointer to the file.
 */
FILE *openInputFile();
/*
 * getFileNames gets the filenames from the inputfile and puts them into a 2D 
 * character array for opening later.
 */
char **getFileNames(FILE *inputfile, int numFiles, int MAXNAMELEN);
/*
 * getAllChars gets all of the characters from 1 file (filename) and puts them into the
 * masterBuffer character array.
 */
char *getAllChars(char *masterBuffer, char *filename, int MAXNAMELEN);
/*
 * freeFileNames frees the space allocated for the fileNames array.
 */
char **freeFileNames(char **fileNames, int numFiles);


#endif
