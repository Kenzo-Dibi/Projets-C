/**
 * \file model-treasurehunt.c
 * 
 * \brief This file contains the type definitions and functions for the treasure hunt program.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 19/04/2022
 * projet: INFO0030 Projet 3
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include "model-treasurehunt.h"

struct model_t{
   SCORE score;/*!< The score(Win/Loss) */
};

TREASUREHUNTMODEL* create_treasurehunt_model(void){
   TREASUREHUNTMODEL* thm = malloc(sizeof(TREASUREHUNTMODEL));
   if(thm == NULL){
      printf("Failed to allocate TREASUREHUNTMODEL.\n");
      return NULL;
   }
   return thm; 
}//end create_treasurehunt_model

TREASUREHUNTMODEL* increment_wins(TREASUREHUNTMODEL* thm){
   assert(thm != NULL);
   thm->score.wins++;
   return thm;
}//end increment_wins

TREASUREHUNTMODEL* increment_losses(TREASUREHUNTMODEL* thm){
   assert(thm != NULL);
   thm->score.losses++;
   return thm;
}//end increment_losses

TREASUREHUNTMODEL* set_wins_score(TREASUREHUNTMODEL* thm, int numberWins){
   assert(thm != NULL && numberWins >= 0);

   thm->score.wins = numberWins;
   return thm;
}//end set_wins_score

TREASUREHUNTMODEL* set_losses_score(TREASUREHUNTMODEL* thm, int numberLosses){
   assert(thm != NULL && numberLosses >= 0);
   
   thm->score.losses = numberLosses;
   return thm;
}//end set_losses_score

unsigned int get_wins_score(TREASUREHUNTMODEL* thm){
   assert(thm != NULL);
   
   return thm->score.wins;
}//end get_wins_score

unsigned int get_losses_score(TREASUREHUNTMODEL* thm){
   assert(thm != NULL);

   return thm->score.losses;
}//end get_losses_score

void destroy_model(TREASUREHUNTMODEL* thm){
   assert(thm != NULL);

   free(thm);
   thm = NULL;
}//end destroy_model