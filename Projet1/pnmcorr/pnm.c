/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Dibi Kenzo s210122
 * @date: 18/03/2022
 * @projet: INFO0030 Projet 1
 */
#define N 1000
#define MAX_VALUE_PGM 255
#define MAX_VALUE_PPM 65535

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "pnm.h"


typedef struct matrix{
   int lines;
   int columns;
   int **matrix;
}MATRIX;
/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
   MagicNumber magicNumber;
   int maxvaluePixel;
   MATRIX matrix;
};

/**
 * skip_comment
 *
 * Skips comment lines.
 * @param fp a file descriptor
 *
 * @pre: fp != NULL
 * @post: the comment line is skipped.
 *
 * @return: /
 *
 */
static void skip_comment(FILE **fp){
   assert(fp != NULL);

   char comment[N];
   while(fscanf(*fp,"%[^\n]", comment) != EOF){
      if(comment[0] != '#'){
         if(fseek(*fp, -strlen(comment), SEEK_CUR) != 0){
            printf("The comments could not be skipped.\n");
            return;
         }
         return;
      }
      fscanf(*fp,"\n");
   }
}
/**
 * file_format
 *
 * Return the magic number according to the file format.
 * @param magicNumber
 *
 * @pre: magicNumber == 0 || magicNumber == 1 || magicNumber == 2.
 * @post: the magic number is returned.
 *
 * @return:the magic number (P1,P2 or P3)
 *
 *
 */
static char *file_format(MagicNumber magicNumber){
   switch(magicNumber){
      case 0:
         return "P1";
      case 1:
         return "P2";
      case 2:
         return "P3";
      default:
         return "unknown";
   }
}

void get_type(char **inputFormat, char *inputFileformat){
   assert(inputFormat != NULL && inputFileformat != NULL);

   const unsigned int SIZE = 4;
   *inputFormat = malloc(SIZE * sizeof(char));
   if(inputFormat == NULL)
      return;

   for(unsigned int i = 0; i < strlen(inputFileformat); i++)
      inputFileformat[i] = tolower(inputFileformat[i]);

   for(unsigned int i = 0; i < strlen(inputFileformat); i++){
      if(inputFileformat[i] == '.'){
         unsigned int k = 0;
         for(unsigned int j = i+1; j< strlen(inputFileformat) && k < SIZE-1; j++){
            (*inputFormat)[k] = inputFileformat[j];
            k++;
         }
      }
   }
}


int verify_format(char *inputFormat, char *inputFileformat){
   assert(inputFormat != NULL && inputFileformat != NULL);

   for(unsigned int i = 0; i < strlen(inputFileformat); i++)
      inputFileformat[i] = tolower(inputFileformat[i]);

   for(unsigned int i = 0; i < strlen(inputFormat); i++)
      inputFormat[i] = tolower(inputFormat[i]);

   char type[4];
   unsigned int ctr = 0;
   unsigned int k = 0;
   for(unsigned int i = 0; i < strlen(inputFileformat); i++){
      if(inputFileformat[i] == '.'){
            k = 0;
         for(unsigned int j = i+1; j< strlen(inputFileformat) && k < strlen(inputFormat); j++){
            type[k] = inputFileformat[j];
            if(inputFileformat[j] == inputFormat[k])
               ctr++;
            k++;
         }
      }
   }
   if(ctr == strlen(inputFormat))
      return 0;
   else{
      if(strcmp(type, "ppm") == 0)
         printf("The input extension should be ppm instead of %s.\n", inputFormat);
      else if(strcmp(type, "pgm") == 0)
         printf("The input extension should be pgm instead of %s.\n", inputFormat);
      else if(strcmp(type, "pbm") == 0)
         printf("The input extension should be pbm instead of %s.\n", inputFormat);
      return -1;
   }
}
//the rest of the code is turned into a comment if '\'  is added to the array
// can't check '/' if the user inputs an absolute file path
int verify_filename(char *outputFilename){
   assert(outputFilename != NULL);

   char unauthorized[] = {':', '*', '?', '"', '<','>', '|'};
   for(unsigned int i = 0; i < strlen(outputFilename);i++){
      for(unsigned int j = 0; j < strlen(unauthorized); j++){
         if(outputFilename[i] == unauthorized[j])
            return -1;
      }
   }
   return 0;
}

void filename_feedback(int result) {
   switch(result){
      case 0:
         printf("The output file name is correct.\n");
         break;
      case -1:
         printf("The output file name is incorrect please make sure it doesn't contain unauthorized characters.\n");
         break;
      default:
         printf("Unknown error.\n");
         break;
   }
}

void format_feedback(int result) {
   switch(result){
      case 0:
         printf("The input extension is correct.\n");
         break;
      case -1:
         printf("The input extension is incorrect please make sure it matches the input file's extension.\n");
         break;
      default:
         printf("Unknown error.\n");
         break;
   }
}
//Author: Mr.Donnet
/**
 * allocate_matrix
 *
 * allocates a matrix
 *
 * @param lines the number of lines the matrix will have.
 * @param columns the number of columns the matrix will have.
 *
 * @pre: lines > 0 && columns > 0
 * @post: the matrix has been created
 *
 * @return:the matrix
 *
 *
 */
static int **allocate_matrix(int lines,int columns){
   assert(lines > 0 && columns > 0);

   int **matrix;
   matrix = malloc(lines* sizeof(int *));
   if(matrix == NULL){
      printf("Unable to generate a matrix.\n");
      return NULL;
   }
   else{
      for(int i = 0; i < lines; i++){
         matrix[i] = malloc(columns * sizeof(int));
         if((matrix)[i] == NULL){
            for(int i = 0; i < lines; i++){
               if((matrix)[i] != NULL)
                  free((matrix)[i]);
            }
            free((matrix));
         } 
      }
   }
   return matrix;
}
//Author Mr.Donnet
void free_pnm(PNM *image){
   assert(image != NULL);
      for(int i = 0; i < (image)->matrix.lines; i++){
         if((image)->matrix.matrix[i] != NULL)
            free((image)->matrix.matrix[i]);
      }
      free((image)->matrix.matrix);
      (image)->matrix.matrix = NULL;
      free(image);
      image = NULL;
      return;
}

void load_feedback(int result){
   switch(result){
      case 0:
         printf("Your file was copied successfully.\n");
         break;
      case -1:
         printf("Unable to allocate memory for the image.\n");
         break;
      case -2:
         printf("The input filename is incorrect.\n");
         break;
      case -3:
         printf("The content of the file is incorrect or inadequate.\n");
         break;
      default:
         printf("Unknown error.\n");
         break;
   }
}

void write_feedback(int result){
   switch(result){
      case 0:
         printf("The image has been saved successfully.\n");
         break;
      case -1:
         printf("The file name in output is incorrect and may contain unauthorized characters.\n");
         break;
      case -2:
         printf("The image could not be saved in a file.\n");
         break;
      default:
         printf("Unknown error.\n");
         break;
   }
}

int load_pnm(PNM **image, char* filename) {
   assert(image != NULL && filename != NULL);

   (*image) = malloc(sizeof(PNM));
   if(image == NULL){
      printf("Unable to open the file.\n");
      return -1;
   }
   FILE *fp = fopen(filename, "r");//opening file;
   char magicnumber[3];
   int columns;
   if(fp == NULL){
      return -2;
   }
   else{
      skip_comment(&fp);
      int check = fscanf(fp,"%s\n",magicnumber);//reads magicnumber in the file
         if(check == EOF || check != 1){
         return -3;
         }
      char *type;
      get_type(&type, filename);

      //Checks if the file extension and the magic number matches
      if(strcmp(magicnumber, "P1") == 0 && strcmp(type, "pbm") == 0)//magicNumber takes a value according to the file type
         (*image)->magicNumber = P1;
      else if(strcmp(magicnumber, "P2") == 0 && strcmp(type, "pgm") == 0)
         (*image)->magicNumber = P2;
      else if(strcmp(magicnumber, "P3") == 0 && strcmp(type, "ppm") == 0)
         (*image)->magicNumber = P3;
      else{
         return -2;
      }
      skip_comment(&fp);
      //reads the number of columns and lines of the matrix
      check = fscanf(fp,"%d %d\n",&((*image)->matrix.columns),&((*image)->matrix.lines));
      if(check != 2 || check == EOF)
         return -3;

      columns = (*image)->matrix.columns;
      if((*image)->magicNumber == P3){//PPM type's pixels are triplets
         columns *= 3;
         //allcating memory to the matrix
         (*image)->matrix.matrix = allocate_matrix((*image)->matrix.lines,columns);
      }
      else {
         //allcating memory to the matrix
         (*image)->matrix.matrix = allocate_matrix((*image)->matrix.lines,columns);
      }

      //checking memory allocation to the matrix
      if((*image)->matrix.matrix == NULL)
         return -1;

      //reads the maximum value for a pixel if the file type is ppm or pgm
      if((*image)->magicNumber == P2 || (*image)->magicNumber == P3){
         skip_comment(&fp);
         check = fscanf(fp,"%d\n",&(*image)->maxvaluePixel);
         if(check != 1 || check == EOF)
            return -3;
      }

      //filling the matrix
      skip_comment(&fp);
      for(int i = 0; i < (*image)->matrix.lines; i++){
         for(int j = 0; j < columns; j++){
            check = fscanf(fp,"%d",&((*image)->matrix.matrix[i][j])); 
            if(check != 1 || check == EOF)
               return -3;
            //checks conditions for each file type
            if((*image)->magicNumber == P1){
               if((*image)->matrix.matrix[i][j] != 0 && (*image)->matrix.matrix[i][j] != 1){
                  return -3;
               }
            }
            if((*image)->magicNumber == P2){
               if((*image)->matrix.matrix[i][j] > MAX_VALUE_PGM){
                  return -3;
               }
            }
            if((*image)->magicNumber == P3){
               if((*image)->matrix.matrix[i][j] > MAX_VALUE_PPM){
                  return -3;
               }
            }
            if((*image)->magicNumber != P1){
               if((*image)->matrix.matrix[i][j] > (*image)->maxvaluePixel)
                  return -3;
            }
         }
         if(fscanf(fp,"\n") == EOF){
            printf("The end of the file has been reached\n");
            return -3;
         }
      }
      free(type);
      type = NULL;
   }
   fclose(fp);
   fp = NULL;
   return 0;
}

int write_pnm(PNM *image, char* filename){
   assert(image != NULL && filename != NULL);
   FILE *fp;
   fp = fopen(filename, "w");
   if(fp == NULL){
      printf("Unable to create the file.\n");
      return -2;
   }
   else{

      char *type;
      get_type(&type, filename);

      //checks if the output file extension and the magic number matches.
      if((image->magicNumber == P1) && strcmp(type, "pbm") != 0)
         printf("The output file extension should be pbm instead of %s.\n", type);
      else if((image->magicNumber == P2) && strcmp(type, "pgm") != 0)
         printf("The output file extension should be pgm instead of %s.\n", type);
      else if((image->magicNumber == P3) && strcmp(type, "ppm") != 0)
         printf("The output file extension should be ppm instead of %s.\n", type);
      else
         printf("The output file extension is correct.\n");

      int columns = image->matrix.columns;
      if(image->magicNumber == P3)//PPM type's pixels are triplets
         columns *= 3;

      //reconstructing the file without comments
      fprintf(fp,"%s\n",file_format(image->magicNumber));
      fprintf(fp,"%d %d\n",image->matrix.columns, image->matrix.lines);

      if(image->magicNumber == P2 || image->magicNumber == P3)
         fprintf(fp,"%d\n",image->maxvaluePixel);

      for(int i = 0; i < image->matrix.lines; i++){
         for(int j = 0; j < columns; j++){
            fprintf(fp,"%d ",image->matrix.matrix[i][j]);
         }
         fprintf(fp,"\n");
      }
      free(type);
      type = NULL;
   }
   fclose(fp);
   fp = NULL;
   return 0;
}
