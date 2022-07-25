/**
 * \file main.c
 * 
 * \brief This is the main file of the connect four game.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 16/07/2022
 * project: INFO0030 Project 4
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "model-connect4.h"
#include "view-connect4.h"
#include "controller-connect4.h"


/**
* 
* \param argc the number of arguments
* \param argv the arguments
* \return EXIT_FAILURE an error has occured
*         EXIT_SUCCES no error
*/
int main(int argc, char **argv){

   gtk_init(&argc, &argv);

   char *optstring = ":n:l:c:f:H::";
   int val;
   unsigned int nInput = 0,lInput = 0, cInput = 0, fInput = 0, hInput = 0;
   unsigned int lines = 0,columns = 0;
   char playerName[MAXCHARACTER];
   char bestScores[MAXCHARACTER];
   
   while((val = getopt(argc, argv, optstring)) != EOF){
      switch(val){
         case 'n':
            strcpy(playerName, optarg);
            nInput = 1;
            break;
         case 'l':
            lines = atoi(optarg);
            lInput = 1;
            break;
         case 'c':
            columns = atoi(optarg);
            cInput = 1;
            break;
         case 'f':
            strcpy(bestScores, optarg);
            fInput = 1;
            break;
         case 'H':
            hInput = 1;
            break;
         case '?':
            printf("Invalid option!: %c\n",optopt);
            break;
         default:
            printf("Unknown option\n");
            break;
      }
   }
   if(nInput == 0){
      strcpy(playerName, "anonymous");
   }
   if(lInput == 0){
      lines = DEFAULT_LINES;
   }
   if(cInput == 0){
      columns = DEFAULT_COLUMNS;
   }
   if(lines * columns <= MINIMUM_LINES * MINIMUM_COLUMNS){
      printf("The size of the board is too small.\n Default settings will used instead\n.");
      lines = DEFAULT_LINES;
      columns = DEFAULT_COLUMNS;
   }
   if(fInput == 0){
      printf("Please input the file containing the best scores using -f <file>.\n");
      return EXIT_FAILURE;
   }
   if(hInput == 1){
      printf("The list of parameters are the following.\n");
      printf("-n <the name you want to be reffered as>\n");
      printf("-f <best score file> (Necessary)\n");
      printf("-l <the number of lines of the board >\n");
      printf("-c <the number of columns of the board>\n");
   }
   
   //the model
   MODELCONNECT4 *MC4 = create_model(lines, columns, playerName, bestScores);
   if(MC4 == NULL)
      return EXIT_FAILURE;

   //the view
   VIEWCONNECT4 *VC4 = create_view(MC4);
   if(VC4 == NULL){
      destroy_model(MC4);
      return EXIT_FAILURE;
   }
   //the controller
   CONTROLLERCONNECT4 *CC4 = create_controller(VC4, MC4);
   if(CC4 == NULL){
      destroy_model(MC4);
      destroy_view(VC4);
      return EXIT_FAILURE;
   }
   
   gtk_main();
   
   //write scores
   write_top_10_score(MC4, bestScores);

   //free allocated memory
   if(MC4 != NULL)
      destroy_model(MC4);
   if(VC4 != NULL)
      destroy_view(VC4);
   if(CC4 != NULL)
      destroy_controller(CC4);
   
   return EXIT_SUCCESS;
}