/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Dibi Kenzo s210122
 * @date: 18/03/2022
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"

#define MAX_CHAR 301

int main(int argc, char *argv[]) {
   /*
    * -f <format>
    * -i <image_input>
    * -o < image_output >
    */ 
   const char *optstring = ":f:i:o:";
   int val;
   int format = 0, input = 0, output = 0;//Used to indicate if the content of an argument has been parsed.
   char fArgument[MAX_CHAR], iArgument[MAX_CHAR], oArgument[MAX_CHAR];
   while((val = getopt(argc, argv, optstring)) != EOF){   /*Author: Mr.Donnet*/
      switch(val){                                       /*the functions of argument i and o has been modified*/      
         case 'f'://the format of the input file  
            strcpy(fArgument, optarg);          /*f argument has been added*/
            format = 1;
            break;
         case 'i'://the input file
            strcpy(iArgument, optarg);
            input = 1;
            break;
         case 'o'://the output file
            strcpy(oArgument, optarg);
            output = 1;
            break;
         case '?':
            printf("unknown option: %c\n", optopt); 
            break;
         case ':':
            printf("missing arg: %c\n", optopt);
            break;
      }
   }
   PNM *myImage;
   int feedback1, feedback2, feedback3, feedback4;
   //Executes code depending on what has been parsed
   if(input){
      feedback2 = load_pnm(&myImage, iArgument);
      load_feedback(feedback2);
      if(format){
         feedback1 = verify_format(fArgument, iArgument);
         format_feedback(feedback1);
      }
   }
   else{
      printf("Please make sure to use the -i argument followed by the path to the file you want to copy.\n");
   }

   if(!format){
      printf("Please make sure to use the -f argument followed by the format.\n");
   }

   if(output){
      if(input && feedback2 != -3){
         feedback4 = write_pnm(myImage, oArgument);
         write_feedback(feedback4);
      }
      feedback3 = verify_filename(oArgument);
      filename_feedback(feedback3);
   }
   else{
      printf("Please make sure to use the -o argument followed by the path to where you want your file to be copied.\n");
   }
   if(input){
      free_pnm(myImage);
      myImage = NULL;
   }
   return 0;
}
