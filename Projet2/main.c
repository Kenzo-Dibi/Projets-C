/**
 * \file main.c
 * 
 * \brief Ce fichier contient la fonction main() du programme de manipulation de matricule.
 *
 * \author: Dibi Kenzo s210122
 * \date: 4/04/2022
 * projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <errno.h>
#include "pnm.h"
#include "codeBarre.h"


int main(int argc, char *argv[]) {
   /*
    * -f <format>
    * -c <qrcode recovery>
    * -i <image_input>
    * -o < image_output >
    */ 
   const char *optstring = ":f:o:c:";
   int val;
   int inputFile = 0, output = 0, recovery = 0;//Used to indicate if the content of an argument has been parsed.
   char fArgument[MAX_CHAR], oArgument[MAX_CHAR], cArgument[MAX_CHAR];
   while((val = getopt(argc, argv, optstring)) != EOF){   /*Author: Mr.Donnet*/
      switch(val){                                       /*the functions of argument i and o has been modified*/      
         case 'f'://the format of the input file  
            strcpy(fArgument, optarg);          /*f argument has been added*/
            inputFile = 1;
            break;
         case 'o'://the output file
            strcpy(oArgument, optarg);
            output = 1;
            break;
         case 'c'://recovery mode
            strcpy(cArgument, optarg);
            recovery = 1;
            break;
         case '?':
            printf("unknown option: %c\n", optopt); 
            break;
         case ':':
            printf("missing arg: %c\n", optopt);
            break;
      }// end switch
   }// end while
   PNM* qrcode = create_pnm();
   if(qrcode == NULL){
      printf("Error message\n");
   }
   else{
      int check;
      if(inputFile || recovery){
         if(output){
            printf("checkpoint\n");
            check = mkdir(oArgument, S_IRWXU);// make it so it only creates the folder if it doesn't exist //test with 0777
            if(check != 0){
               switch (errno) {
                  case EACCES :
                     printf("This directory does not allow write.\n");
                     break;
                  case EEXIST:
                     if(inputFile){
                        check = generate_qrcode(&qrcode, fArgument, oArgument);
                        if(!check)
                           printf("The QR codes have been created\n");
                     }
                     if(recovery)
                        fix_qrcode(&qrcode, cArgument, oArgument);
                     break;
                  case ENAMETOOLONG:
                     printf("The pathname is too long.\n");
                     break;
                  default:
                     printf("unknown error\n");
                     break;
               }
            }
            else{
               if(check != 0)
                  printf("The output folder already exists.\n");
               else{
                  if(inputFile){
                        check = generate_qrcode(&qrcode, fArgument, oArgument);
                        if(!check)
                           printf("The QR codes have been created\n");
                  }
                  if(recovery)
                     fix_qrcode(&qrcode, cArgument, oArgument);
               }
            }
         }// end if output
      }// end if inputFIle
      if(!inputFile && !recovery)
         printf("Please make sure to use either the argument -f <file> or -c <file_to_be_recovered.pbm>.\n");
      if(!output)
         printf("Please make sure to use the argument -o <output folder>.\n");
   }
   free_pnm(qrcode);
   qrcode = NULL;
   return 0;
}
