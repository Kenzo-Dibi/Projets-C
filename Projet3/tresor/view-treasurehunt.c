/**
 * \file view-treasurehunt.c
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
#include <gtk/gtk.h>

#include "model-treasurehunt.h"
#include "controller-treasurehunt.h"

/**
 * \brief The maximum number of characters you can put into this array.
 */
#define MAX_CHAR 1001

/**
 * \struct view_t
 * \brief Implementation of the view for the treasurehunt.
 */
struct view_t{
   TREASUREHUNTMODEL* thm; /*!< model of treasurehunt */
   GtkWidget *pLabel[2]; /*!< shows the number of wins, losses and the game state */
};

VIEWTREASUREHUNT* create_treasurehunt_view(TREASUREHUNTMODEL* thm){
   assert(thm != NULL);

   VIEWTREASUREHUNT* vt = malloc(sizeof(VIEWTREASUREHUNT));
   if(vt == NULL){
      printf("Failed to allocate vt.\n");
      return NULL;
   }
   else{
      vt->thm = thm;
      vt->thm = set_wins_score(vt->thm, 0);
      vt->thm = set_losses_score(vt->thm, 0);
      vt->pLabel[0] = gtk_label_new("Victoires: 0 Défaites: 0");
      vt->pLabel[1] = gtk_label_new("Choisissez un coffre!");

   }
   return vt;
}//end create_treasurehunt_view

VIEWTREASUREHUNT* redraw_score(VIEWTREASUREHUNT* vt){
   assert(vt != NULL);

   char message[MAX_CHAR];
   sprintf(message, "Victoires: %d Défaites: %d", get_wins_score(vt->thm), get_losses_score(vt->thm));
   gtk_label_set_text(GTK_LABEL(vt->pLabel[0]), message);
   //gtk_label_set_text(GTK_LABEL(vt->pLabel[1]), "Choisissez un coffre!");

   return vt;
}//end redraw_score

GtkWidget *get_label(VIEWTREASUREHUNT *vt, int number){
   assert(vt != NULL && number >= 0 && number < 2);

   return vt->pLabel[number];
}//end get_label

void destroy_view(VIEWTREASUREHUNT* vt){
   assert(vt != NULL);

   /*if(vt->thm != NULL){
      destroy_model(vt->thm);
      vt->thm = NULL;
   }
   if(vt->pLabel[FIRST] != NULL){
      free(vt->pLabel[FIRST]);
      vt->pLabel[FIRST] = NULL;
   }
   if(vt->pLabel[SECOND] != NULL){
      free(vt->pLabel[SECOND]);
      vt->pLabel[SECOND] = NULL;
   }*/
   free(vt);
   vt = NULL;
}//end destroy_view