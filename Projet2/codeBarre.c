/**
 * \file codeBarre.c
 * 
 * \brief Ce fichier contient les définitions de types et les fonctions de créations de code barre.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 4/04/2022
 * projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <math.h>

#include "codeBarre.h"

/**
 * \fn static int check_errors(FILE **fp)
 *
 * \brief Check if the lines contains a registration number.
 * \param fp a file descriptor
 *
 * \pre: fp != NULL
 * \post: the errors have been detected detected.
 *
 * \return: 
 *      1 success
 *      0 failure
 *
 */
static int check_errors(FILE **fp){
   assert(fp != NULL);
   char number[N];
   //parses a line then checks if the operation didn't fail.
   int check = fscanf(*fp,"%[^\n]", number);
   if(check == EOF || check != 1 || strlen(number) == 0){
      return 0;
   }
   //checks if it's the correct size.
   if(strlen(number) != 8){
      printf("The size is incorect.\n");
      return 0;
   }
   //checks if it's a number or not. 
   for(unsigned i = 0; i < strlen(number); i++){
      if(!isdigit(number[i])){
         printf("This is not a number.\n");
         return 0;
      }
   }//end for
   if(fseek(*fp, -strlen(number), SEEK_CUR) != 0){
      printf("The number could not be skipped.\n");
      return 0;
   }
   return 1;
}//end check_errors

/**
 * \fn static int line_parity(int  **Tab, int line, int n)
 *
 * \brief returns the parity of the specified line in a matrix
 * \param Tab the matrix
 * \param n the size of the matrix
 * \param line the line of the matrix
 *
 * \pre: Tab != NULL && n > 0 && line > 0
 * \post: the parity of the line is returned
 *
 * \return: 
 *    odd:   1
 *    even : 0
 *    error:-1
 *
 */
static int line_parity(int  **Tab, int line, int n){
   assert(Tab != NULL && line >= 0 && n > 0);
   
   int cnt = 0;
   for(int i = 0; i < n - 1; i++){
      if(Tab[line][i] == 1)
         cnt++;
   }//end for

   return (cnt % 2 == 1);
}

/**
 * \fn static int column_parity(int  **Tab, int column, int n)
 *
 * \brief returns the parity of the specified column in a matrix
 * \param Tab the matrix
 * \param n the size of the matrix
 * \param column the column of the matrix
 *
 * \pre: Tab != NULL && n > 0 && column > 0
 * \post: the parity of the column is returned
 *
 * \return: 
 *    odd:   1
 *    even : 0
 *    error:-1
 */

static int column_parity(int  **Tab, int column, int n){
   assert(Tab != NULL && column >= 0 && n > 0);

   int cnt = 0;
   for(int i = 0; i < n - 1; i++){
      if(Tab[i][column] == 1)
         cnt++;
   }//end for

   return (cnt % 2 == 1);
}

/**
 * \fn static int last_line_column_parity(int ** Tab, int n)
 *
 * \brief returns the parity of the last line and column of the matrix
 * \param Tab the matrix
 * \param n the size of the matrix
 *
 * \pre: Tab != NULL  &&  n > 0
 * \post: the parity of the column is returned
 *
 * \return: 
 *    odd:   1
 *    even : 0
 *    error:-1
 */
static int last_line_column_parity(int ** Tab, int n){
   assert(Tab != NULL && n > 0);

   int cnt1 = 0,cnt2 = 0;
   for(unsigned i = 0; i < SIZE_MINI_MATRIX - 1; i++){
         if(Tab[i][SIZE_MINI_MATRIX -1] == 1)
               cnt1 += 1;
         if(Tab[SIZE_MINI_MATRIX - 1][i] == 1)
               cnt2 += 1;
   }//end for

   return (cnt1 % 2 == 1 && cnt2 % 2 == 1);
}

/**
 * \fn static int **decimal_to_binary(int number)
 *
 * \brief a matrix containing the conversion of number from decimal to binary is created.
 * \param number a decimal number
 *
 * \pre: number >= 0
 * \post: the matrix containing the binary representation of number is created
 *
 * \return: Tab or NULL
 *
 */
static int **decimal_to_binary(int number){
   assert(number >= MIN_REG_NUMBER && number <= MAX_REG_NUMBER);

   int **Tab = calloc(SIZE_MINI_MATRIX, sizeof(int *));
   if(Tab == NULL)
      return NULL;

   for(unsigned int i = 0; i < SIZE_MINI_MATRIX; i++){
      Tab[i] = calloc(SIZE_MINI_MATRIX, sizeof(int));
      if(Tab[i] == NULL){
         for(unsigned j = 0; j< SIZE_MINI_MATRIX; j++){
               if(Tab[j] != NULL){
                  free(Tab[j]);
                  Tab[j] = NULL;
               }
         }// end for
         free(Tab);
         Tab = NULL;
         return NULL;
      }
   }//end for

   for(unsigned int i = 0; number && i < SIZE_MINI_MATRIX - 1; i++){
      for(unsigned int j = 0; number && j < SIZE_MINI_MATRIX - 1; j++){
         if(number % 2 == 1)
               Tab[i][j] = 1;
         number >>= 1;
      }//end for
   }//end for

   for(unsigned int i = 0; i < SIZE_MINI_MATRIX -1; i++){
      Tab[i][SIZE_MINI_MATRIX -1] = line_parity(Tab, i, SIZE_MINI_MATRIX); // fills the last element of a line with  1 if the parity of the line is an odd number
      Tab[SIZE_MINI_MATRIX - 1][i] = column_parity(Tab, i, SIZE_MINI_MATRIX); // fills the last element of a column with  1  if the parity of the column is an odd number
   }

   Tab[SIZE_MINI_MATRIX - 1][SIZE_MINI_MATRIX - 1] = last_line_column_parity(Tab, SIZE_MINI_MATRIX);

   return Tab;
}// end decimal_to_binary

/**
 * \fn static char* create_file_name(int registrationNumber)
 *
 * \brief Concatenates the registration number and the file extension to form the filename.
 * \param registrationNumber a decimal number
 *
 * \pre: registrationNumber >= 0
 * \post: the filename is created
 *
 * \return: filename or NULL
 *
 */
static char* create_file_name(int registrationNumber){
   assert(registrationNumber >= MIN_REG_NUMBER);

   char extension[] = ".pbm";
   char *filename = malloc((SIZE_REG + FILE_EXTENSION + 1) * sizeof(char));
   if(filename == NULL)
      return NULL;
   else{
      for(int i = SIZE_REG - 1; i >= 0; i--){
         if(registrationNumber == 0)
               filename[i] = '0';
         else{
               filename[i] = registrationNumber % 10  + '0';// transforms integers into chars
               registrationNumber /= 10;
         }
      }// end for

      strncat(filename, extension, FILE_EXTENSION + 1);
   }
   return filename;
}// end create_file_name

/**
 * \fn static char* concatenate_char1_char2(char* filename,char* filedest)
 *
 * \brief Concatenates the filenamer and the filedest to form the filename.
 * \param filename the name of pbm file
 * \param filedest the folder where the pbm will be created
 * \pre: filename !!= NULL && filedest != NULL
 * \post: the filename is created
 *
 * \return: dest or NULL
 *
 */
static char* concatenate_char1_char2(char* filename,char* filedest){
   assert(filename != NULL && filedest != NULL);

   char backslash[] = "/";
   char* dest = malloc(MAX_CHAR  * sizeof(char));
   if(dest == NULL)
      return NULL;
      
   strcat(dest, filedest);
   strcat(dest, backslash);
   strcat(dest, filename);

   return dest;
}// end concatenate_char1_char2

/**
 * \fn static int fixed_qrcode_number(int **array, int n)
 *
 * \brief Creates the filename of the fixed qrcode .
 * \param array the array containing the representation of the number in qrcode format
 * \param n the size of the array (n x n)
 * \pre: array != NULL & n > 0
 * \post: the recovered qrcode filename is created
 *
 * \return: the filename
 *
 */
static int fixed_qrcode_number(int **array, int n){
   assert(array != NULL && n > 0);

   int number = 0, squared = 0;

   for(int i = 0; i < n - 1; i++){
      for(int j = 0; j < n - 1; j++){
         number += array[i][j] * pow(2, squared);
         squared++;
      }
   }
   return number;
}// end fixed_qrcode_filename

int generate_qrcode(PNM **qrcode, char *filename, char* output){
   assert(qrcode != NULL && filename != NULL && output != NULL);

   FILE* fp = fopen(filename, "r");
   if(fp == NULL){
      printf("Unable to access file.\n");
      return -1;
   }
   else{
      if(!check_errors(&fp))
         return -1;
      *qrcode = set_magicnumber(get_pnm(*qrcode), P1);// magic number
      if(qrcode == NULL){
         fclose(fp);
         fp = NULL;
         return -1;
      }
      
      *qrcode = set_lines_columns(get_pnm(*qrcode), SIZE_MATRIX);// lines and columns of the matrix
      if(qrcode == NULL){
         fclose(fp);
         fp = NULL;
         return -1;
      }

      *qrcode = create_matrix(*qrcode, SIZE_MATRIX, SIZE_MATRIX);//the matrix
      if(qrcode == NULL){
         fclose(fp);
         fp = NULL;
         return -1;
      }

      while(!feof(fp)){
         if(!check_errors(&fp)){
            fclose(fp);
            fp = NULL;
            return -1;
         }
         int check, registrationNumber;
         check = fscanf(fp,"%d\n", &registrationNumber);
         if(check == EOF || check != 1){
            fclose(fp);
            fp = NULL;
            return -1;
         }
         else if(registrationNumber > MAX_REG_NUMBER || registrationNumber < MIN_REG_NUMBER){
            fclose(fp);
            fp = NULL;
            return -1;
         }
         else{
               int **binaryNumber = decimal_to_binary(registrationNumber);// binary representation of registrationNumber
               if(binaryNumber == NULL){
                  fclose(fp);
                  fp = NULL;
                  return -1;
               }

               *qrcode = set_value_matrix(get_pnm(*qrcode),binaryNumber, SIZE_MATRIX, SIZE_MATRIX);//generates a 70x70 matrix from 7x7 binaryNumber
               if(qrcode == NULL){
                  fclose(fp);
                  fp = NULL;
                  free_matrix(binaryNumber, SIZE_MINI_MATRIX);
                  binaryNumber = NULL;
                  return -1;
               }

               char *file = create_file_name(registrationNumber);//generate a filename according to the registration number
               if(file == NULL){
                  fclose(fp);
                  fp = NULL;
                  free_matrix(binaryNumber, SIZE_MINI_MATRIX);
                  binaryNumber = NULL;
                  return -1;
               }
               char *filedest = concatenate_char1_char2(file, output);
               if(filedest == NULL){
                  fclose(fp);
                  fp = NULL;
                  free_matrix(binaryNumber, SIZE_MINI_MATRIX);
                  binaryNumber = NULL;
                  return -1;
               }
               write_pnm(get_pnm(*qrcode), filedest);

               free(file);
               file = NULL;
               free_matrix(binaryNumber, SIZE_MINI_MATRIX);
               binaryNumber = NULL;
               free(filedest);
         }
      }// end while
   //destroy_matrix(get_pnm(*qrcode));
   fclose(fp);
   fp = NULL;
   }
   return 0;
}// end generate_qrcode

int fix_qrcode(PNM **qrcode, char* input, char* output){
   assert(qrcode != NULL && input != NULL && output != NULL);

   printf("ici\n");
   int check = load_pnm(qrcode, input);
   if(check == -1 || check == -2 || check == -3){
      load_feedback(check);
      return -1;
   }

   int **binaryMatrix = allocate_matrix(SIZE_MINI_MATRIX, SIZE_MINI_MATRIX);
   if(binaryMatrix == NULL){
      printf("Failed to allocate binaryMatrix\n");
      return -1;
   }
   //downscales the 70x70 matrix to 7x7
   for(unsigned int i = 0; i < SIZE_MINI_MATRIX; i++){
      //printf("i: %u\n", i);
      printf("[ ");
      for(unsigned int j = 0; j < SIZE_MINI_MATRIX; j++){
         //printf("j: %u\n", j);
         binaryMatrix[i][j] = get_value_matrix(get_pnm(*qrcode), i * 10, j * 10);
         printf("%d ", binaryMatrix[i][j]);
      }
      printf("]\n");
   }

   int cntErrorline = 0, cntErrorcolumn = 0, line, column;
   
   for(unsigned int i = 0; i < SIZE_MINI_MATRIX - 1; i++){
      if(line_parity(binaryMatrix, i, SIZE_MINI_MATRIX) != binaryMatrix[i][SIZE_MINI_MATRIX - 1]){
         line = i;
         cntErrorline++;
      }
      if(column_parity(binaryMatrix, i, SIZE_MINI_MATRIX) != binaryMatrix[SIZE_MINI_MATRIX - 1][i]){
         column = i;
         cntErrorcolumn++;
      }
   }
   printf("linerr : %d\n", cntErrorline);
   printf("columnerr: %d\n", cntErrorcolumn);
   printf("line %d\n", line);
   printf("column: %d\n", column);

   if(cntErrorline <= 1 && cntErrorcolumn <= 1){
      printf("needs to be recovered\n");
      //first case scenerio
      if(cntErrorline == 1 && cntErrorcolumn == 1){
         if(binaryMatrix[line][column])
            binaryMatrix[line][column] = 0;
         else
            binaryMatrix[line][column] = 1;

         binaryMatrix[SIZE_MINI_MATRIX - 1][SIZE_MINI_MATRIX - 1] = last_line_column_parity(binaryMatrix, SIZE_MINI_MATRIX);
      }
      //second case scenario
      else if(cntErrorline == 1 && cntErrorcolumn == 0){
         binaryMatrix[line][SIZE_MINI_MATRIX - 1] = line_parity(binaryMatrix,line, SIZE_MINI_MATRIX);
         binaryMatrix[SIZE_MINI_MATRIX - 1][SIZE_MINI_MATRIX - 1] = last_line_column_parity(binaryMatrix, SIZE_MINI_MATRIX);
      }
      else if(cntErrorline == 0 && cntErrorcolumn == 1){
         binaryMatrix[SIZE_MINI_MATRIX - 1][column] = column_parity(binaryMatrix, column, SIZE_MINI_MATRIX);
         binaryMatrix[SIZE_MINI_MATRIX - 1][SIZE_MINI_MATRIX - 1] = last_line_column_parity(binaryMatrix, SIZE_MINI_MATRIX);
      }
      //third case scenario
      else if(cntErrorline == 0 && cntErrorcolumn == 0){
         if(binaryMatrix[SIZE_MINI_MATRIX - 1][SIZE_MINI_MATRIX - 1] == last_line_column_parity(binaryMatrix, SIZE_MINI_MATRIX))
            printf("The qrcode seems to already be correct\n");
         else
            binaryMatrix[SIZE_MINI_MATRIX - 1][SIZE_MINI_MATRIX - 1] = last_line_column_parity(binaryMatrix, SIZE_MINI_MATRIX);
      }
   }
   else{
      printf("There seems to be more than one error.\n Unfortunately it is impossible to recover.\n");
      free_matrix(binaryMatrix, SIZE_MINI_MATRIX);
      binaryMatrix = NULL;
      return -1;
   }

   *qrcode = set_value_matrix(get_pnm(*qrcode),binaryMatrix, SIZE_MATRIX, SIZE_MATRIX);//generates a 70x70 matrix from 7x7 binaryNumber
   if(qrcode == NULL){
      free_matrix(binaryMatrix, SIZE_MINI_MATRIX);
      binaryMatrix = NULL;
      return -1;
   }

   for(unsigned int i = 0; i < SIZE_MINI_MATRIX; i++){
   //printf("i: %u\n", i);
   printf("[ ");
   for(unsigned int j = 0; j < SIZE_MINI_MATRIX; j++){
      //printf("j: %u\n", j);
      printf("%d ", binaryMatrix[i][j]);
   }
   printf("]\n");
}  
   char *file = create_file_name(fixed_qrcode_number(binaryMatrix, SIZE_MINI_MATRIX));

   char *filedest = concatenate_char1_char2(file, output);
   if(filedest == NULL){
      free_matrix(binaryMatrix, SIZE_MINI_MATRIX);
      binaryMatrix = NULL;
      free(file);
      file = NULL;
      return -1;
   }
   printf("filedest: %s \n", filedest);
   check = write_pnm(get_pnm(*qrcode), filedest);
   write_feedback(check);

   free_matrix(binaryMatrix, SIZE_MINI_MATRIX);
   binaryMatrix = NULL;
   free(file);
   file = NULL;
   free(filedest);
   filedest = NULL;

   return 0;
}// end fix_qrcode