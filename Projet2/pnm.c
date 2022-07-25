/**
 * \file pnm.c
 * 
 * \brief Ce fichier contient les définitions de types et  les fonctions de manipulation d'images PNM.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 4/04/2022
 * projet: INFO0030 Projet 1
 */

/**
 * \brief La nombre maximum de case dans un tableau
 */
#define N 1000

/**
 * \brief la valeur maximale d'un pixel dans un fichier pgm
 */
#define MAX_VALUE_PGM 255

/**
 * \brief La valeur maximale d'un pixel dans un fichier ppm
 */
#define MAX_VALUE_PPM 65535

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "pnm.h"

/**
 * \struct matrix
 * \brief Définition de la structure matrice
 */
typedef struct matrix{
   int lines; /*!< the number of lines of the matrix */
   int columns; /*!< the number of columns of the matrix */
   int **matrix; /*!< the matrix */
}MATRIX;

/**
 * \struct PNM_t
 * \brief Définition du type opaque PNM
 */
struct PNM_t {
   MagicNumber magicNumber; /*!< the format of the file */
   int maxvaluePixel; /*!< the maximum value of a pixel in the matrix */
   MATRIX matrix; /*!< a pointer to the structure matrix*/
};

/**
 * \fn static void skip_comment(FILE **fp)
 *
 * \brief Skips comment lines.
 * \param fp a file descriptor
 *
 * \pre: fp != NULL
 * \post: the comment line is skipped.
 *
 * \return: /
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
}// end skip_comment

PNM* set_magicnumber(PNM* image, MagicNumber magicNumber){
   assert(image != NULL);
   image->magicNumber = magicNumber;
   return image;
}// end set_magicnumber

PNM* set_lines_columns(PNM* image, int size){
   assert(image != NULL && size > 0);
   
   image->matrix.columns = size;
   image->matrix.lines = size;
   return image;
}//end set_lines_columns

/**
 * \fn static char *file_format(MagicNumber magicNumber)
 *
 * \brief Return the magic number according to the file format.
 * \param magicNumber the format of the file
 *
 * \pre: magicNumber == 0 || magicNumber == 1 || magicNumber == 2.
 * \post: the magic number is returned.
 *
 * \return:the magic number (P1, P2 or P3)
 *
 *
 */
static char *file_format(MagicNumber magicNumber){
   assert(magicNumber == P1 || magicNumber == P2 || magicNumber == P3);
   switch(magicNumber){
      case P1:
         return "P1";

      case P2:
         return "P2";

      case P3:
         return "P3";

      default:
         return "unknown";
   }
}// end file_format

void get_type(char **inputFormat, char *inputFileformat){
   assert(inputFormat != NULL && inputFileformat != NULL);

   const unsigned int SIZE = 5;
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
}// end get_type


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
         }// end for - j
      }
   }// end for - i

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
}// end verify_format

int verify_filename(char *outputFilename){
   assert(outputFilename != NULL);

   char unauthorized[] = {':', '*', '?', '"', '<','>', '|', '\\'};
   for(unsigned int i = 0; i < strlen(outputFilename);i++){
      for(unsigned int j = 0; j < strlen(unauthorized); j++){
         if(outputFilename[i] == unauthorized[j])
            return -1;
      }//end for - j
   }//end for - i
   return 0;
}// end verify_filename

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
}// end filename_feedback

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
}// end format_feedback

int **allocate_matrix(int lines,int columns){
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
            for(int j = 0; j < lines; j++){
               if((matrix)[j] != NULL)
                  free((matrix)[i]);
            }// end for - j
            free((matrix));
            return NULL;
         } 
      }//end for -i
   }
   return matrix;
}// end allocate_matrix

void free_pnm(PNM *image){
   assert(image != NULL);
      for(int i = 0; i < (image)->matrix.lines; i++){
         if((image)->matrix.matrix[i] != NULL)
            free((image)->matrix.matrix[i]);
      }// end for - i

      free((image)->matrix.matrix);
      (image)->matrix.matrix = NULL;
      free(image);
      image = NULL;
      return;
}// end free_pnm

void destroy_matrix(PNM* image){
   assert(image != NULL);

   for(int i = 0; i < image->matrix.lines; i++){
      if(image->matrix.matrix[i] != NULL){
         free(image->matrix.matrix[i]);
         image->matrix.matrix[i] = NULL;
      }
   }//end for - i
   free(image->matrix.matrix);
   image->matrix.matrix = NULL;
}//end destroy_matrix

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
}// end load_feedback

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
}// end write_feedback

PNM* create_pnm(){
   PNM* qrcode = malloc(sizeof(PNM));
   if(qrcode == NULL){
      return NULL;
   }
   return qrcode;
}// end create_pnm

MagicNumber get_magic_number(PNM* qrcode){
   assert(qrcode != NULL);

   return qrcode->magicNumber;
}// end get_magic_number

int get_lines(PNM* qrcode){
   assert(qrcode != NULL);

   return qrcode->matrix.lines;
}// end get_lines

int get_columns(PNM* qrcode){
   assert(qrcode != NULL);

   return qrcode->matrix.columns;
}// end get_columns

 // calloc
PNM* create_matrix(PNM* image, int lines , int columns){
   assert(lines > 0 && columns > 0);

   image->matrix.matrix = malloc(lines * sizeof(int *));
   if(image->matrix.matrix == NULL)
      return NULL;
   for(int i = 0; i < lines; i++){
      image->matrix.matrix[i] = malloc(columns * sizeof(int));
      if(image->matrix.matrix[i] == NULL){
         for(int j = 0; j < lines; j++){
            if(image->matrix.matrix[j] != NULL){
               free(image->matrix.matrix[j]);
               image->matrix.matrix[j] = NULL;
            }
         }//end for - j
         free(image->matrix.matrix);
         image->matrix.matrix = NULL;
         return NULL;
      } 
   }//end for - i
   return image;
}// end create_matrix

PNM* set_value_matrix(PNM* image, int** binaryNumber,  int lines, int columns){
   assert(image != NULL && binaryNumber != NULL && columns > 0 && lines > 0);

   int begin1 = 0, begin2 = 0;
   for(unsigned int i = 0; i < 7; i++){
      for(unsigned int j = 0; j < 7; j++){
         for(int k = begin1; k < begin1 + 10 && k < lines; k++){
            for(int l = begin2; l < begin2 + 10 && l < columns; l++){
               image->matrix.matrix[k][l] = binaryNumber[i][j];
            }
         }
         begin2 += 10;
      }
      begin1 += 10;begin2 = 0;
   }
   return image;
}// end set_value_matrix

int get_value_matrix(PNM* qrcode, int lines, int columns){
   assert(lines >= 0 && columns >= 0);

   return qrcode->matrix.matrix[lines][columns];
}// end get_value_matrix

PNM* get_pnm(PNM* image){
   assert(image != NULL);

   return image;
}//end get_pnm

void free_matrix(int **matrix, int size){
    assert(matrix != NULL);

      for(int i = 0; i < size; i++){
         if(matrix[i] != NULL)
            free(matrix[i]);
      }// end for - i
      free(matrix);
      return;

}// end free_matrix

int load_pnm(PNM **image, char* filename){
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
            fclose(fp);
            fp = NULL;
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
         fclose(fp);
         fp = NULL;
         return -2;
      }
      skip_comment(&fp);
      //reads the number of columns and lines of the matrix
      check = fscanf(fp,"%d %d\n",&((*image)->matrix.columns),&((*image)->matrix.lines));
      if(check != 2 || check == EOF){
         fclose(fp);
         fp = NULL;
         return -3;
      }

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
      if((*image)->matrix.matrix == NULL){
         fclose(fp);
         fp = NULL;
         return -1;
      }

      //reads the maximum value for a pixel if the file type is ppm or pgm
      if((*image)->magicNumber == P2 || (*image)->magicNumber == P3){
         skip_comment(&fp);
         check = fscanf(fp,"%d\n",&(*image)->maxvaluePixel);
         if(check != 1 || check == EOF){
            fclose(fp);
            fp = NULL;
            return -3;
         }
      }

      //filling the matrix
      skip_comment(&fp);
      for(int i = 0; i < (*image)->matrix.lines; i++){
         for(int j = 0; j < columns; j++){
            check = fscanf(fp,"%d",&((*image)->matrix.matrix[i][j])); 
            if(check != 1 || check == EOF){
               fclose(fp);
               fp = NULL;
               return -3;
            }
            //checks conditions for each file type
            if((*image)->magicNumber == P1){
               if((*image)->matrix.matrix[i][j] != 0 && (*image)->matrix.matrix[i][j] != 1){
                  fclose(fp);
                  fp = NULL;
                  return -3;
               }
            }
            if((*image)->magicNumber == P2){
               if((*image)->matrix.matrix[i][j] > MAX_VALUE_PGM){
                  fclose(fp);
                  fp = NULL;
                  return -3;
               }
            }
            if((*image)->magicNumber == P3){
               if((*image)->matrix.matrix[i][j] > MAX_VALUE_PPM){
                  fclose(fp);
                  fp = NULL;
                  return -3;
               }
            }
            if((*image)->magicNumber != P1){
               if((*image)->matrix.matrix[i][j] > (*image)->maxvaluePixel){
                  fclose(fp);
                  fp = NULL;
                  return -3;
               }
            }
         }
         if(fscanf(fp,"\n") == EOF){
            printf("The end of the file has been reached\n");
            fclose(fp);
            fp = NULL;
            return -3;
         }// end for j
      }// end for i
      free(type);
      type = NULL;
   }
   fclose(fp);
   fp = NULL;
   return 0;
}// end load_pnm

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
         }// end for
         fprintf(fp,"\n");
      }
      free(type);
      type = NULL;
   }
   fclose(fp);
   fp = NULL;
   return 0;
}// end write_pnm
