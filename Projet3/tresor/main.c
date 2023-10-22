/**
 *  \file file main.c
 * 
 * \brief This file contains the main function use to make the the game.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 19/04/2022
 * projet: INFO0030 Projet 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "controller-treasurehunt.h"
#include "model-treasurehunt.h"
#include "view-treasurehunt.h"

int main(int argc, char **argv){

   //creation of the treasurehunt model
   TREASUREHUNTMODEL *thm = create_treasurehunt_model();
   if(thm == NULL){
      printf("Failed to create the model.\n");
      return EXIT_FAILURE;
   }

   //creation of the treasurehunt view
   VIEWTREASUREHUNT *thv = create_treasurehunt_view(thm);
   if(thv == NULL){
      printf("Failed to create the view.\n");
      return EXIT_FAILURE;
   }

   //creation of the treasurhunt controller
   TREASUREHUNTCONTROLLER *thc = create_treasurehunt_controller(thv, thm);
   if(thc == NULL){
      printf("Failed to create the controller.\n");
      return EXIT_FAILURE;
   }

   //IHM creation
   GtkWidget *pWindow;
   GtkWidget *pTable;

   //Initialisation of GTK environment
   gtk_init(&argc, &argv);

   //creation of the window
   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pWindow), "Le jeu du trésor\n");
   gtk_window_set_default_size(GTK_WINDOW(pWindow), 400, 250);

   g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

   pTable = gtk_table_new(4, 3, TRUE);
   gtk_table_attach(GTK_TABLE(pTable), get_state_label(thc, 0), 0, 3, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
   gtk_table_attach(GTK_TABLE(pTable), get_state_label(thc, 1), 0, 3, 0, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);
   gtk_table_attach(GTK_TABLE(pTable),get_restart(thc), 0, 3, 1, 2, GTK_FILL, GTK_EXPAND, 0, 0);
   gtk_table_attach(GTK_TABLE(pTable), get_chest(thc, 0), 0, 1, 1, 4, GTK_EXPAND, GTK_EXPAND, 0, 0);
   gtk_table_attach(GTK_TABLE(pTable), get_chest(thc, 1), 1, 2, 1, 4, GTK_EXPAND, GTK_EXPAND, 0, 0);
   gtk_table_attach(GTK_TABLE(pTable), get_chest(thc, 2), 2, 3, 1, 4, GTK_EXPAND, GTK_EXPAND, 0, 0);
   gtk_container_add(GTK_CONTAINER(pWindow), pTable);
   gtk_widget_show_all(pWindow);
   
   //main
   gtk_main();

   //frees allocated memory
   destroy_model(thm);
   destroy_view(thv);
   destroy_controller(thc);

   return EXIT_SUCCESS;
}// end of program