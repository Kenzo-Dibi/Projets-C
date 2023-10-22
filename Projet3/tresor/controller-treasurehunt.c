/**
 * \file controller-treasurehunt.c
 * 
 * \brief This file contains the type definitions and functions for the treasure hunt program.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 19/04/2022
 * projet: INFO0030 Projet 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "controller-treasurehunt.h"

struct controller_t{
   struct view_t *thv; /*!< shows the number of wins, losses and the game state */
   TREASUREHUNTMODEL *thm; /*!< shows the number of wins, losses and the game state */
   CHEST chest[3]; /*!< shows the number of wins, losses and the game state */
   GtkWidget *restart; /*!< shows the number of wins, losses and the game state */
};

/**
 * \fn static GtkWidget* load_button_image(void)
 * \brief draws the unopened chest on a button.
 * \author Mr.Donnet
 * \pre /
 * \post the image has been loaded onto the button
 * \return 
 *       pButton the button
 */
static GtkWidget* load_button_image(void){

   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file("images_coffrets/coffre_ferme.jpg", NULL);
   if(pb_temp == NULL){
      printf("Failed to load image coffre_ferme.jpg.\n");
      return NULL;
   }
   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, IMG_SIZE, IMG_SIZE, GDK_INTERP_NEAREST);
   GtkWidget* pButton = gtk_button_new();
   GtkWidget* image = gtk_image_new_from_pixbuf(pb);
   gtk_button_set_image(GTK_BUTTON(pButton), image);
   
   return pButton;
}//end load_button_image

/**
 * \fn static TREASUREHUNTCONTROLLER* randomize_chests(TREASUREHUNTCONTROLLER* thc)
 * \brief randomizes the content of the chests
 * \param thc a pointer to TREASUREHUNTCONTROLLER
 * \pre thc != NULL
 * \post the content of the chest has been randomized
 * \return
 *    pButton the button
 */
static TREASUREHUNTCONTROLLER* randomize_chests(TREASUREHUNTCONTROLLER* thc){
   assert(thc != NULL);

   srand(time(NULL));//randmizes based on time
   unsigned int i = rand() % 3;
   thc->chest[i].content = gold;//assigns the chest containing the gold randomly
   for(unsigned int j = 0; j < NUMBER_CHEST; j++){
      if(j != i)
         thc->chest[j].content = empty;
   }
   return thc;
}//end randomize_Chests

/**
 * \fn static unsigned int opened_chests_counter(TREASUREHUNTCONTROLLER* thc)
 * \brief the number of opened chest
 * \param thc a pointer to TREASUREHUNTCONTROLLER
 * \pre thc != NULL
 * \post the number of opened chest is returned
 * \return
 *    cpt number of opened chest
 */
static unsigned int opened_chests_counter(TREASUREHUNTCONTROLLER* thc){
   assert(thc != NULL);
   unsigned cpt = 0;
   for(unsigned i = 0; i < NUMBER_CHEST; i++){
      if(thc->chest[i].state == opened)
         cpt++;
   }
   return cpt;
}//end opened_chests_counter

/**
 * \fn static GtkWidget* set_chest_image(GtkWidget *pButton,char *image)
 * \brief sets a new image on the button
 * \param pButton the button that'll contain the image
 * \param image the image to put on the button
 * \pre pButton != NULL && image != NULL
 * \post the button image has been updated
 * \return
 *       pButton the button
 *    
 */
static GtkWidget* set_chest_image(GtkWidget *pButton,char *image){
   assert(pButton != NULL && image != NULL);

   GdkPixbuf *pb_temp = gdk_pixbuf_new_from_file(image, NULL);
   if(pb_temp == NULL){
      printf("Failed to load image %s.\n", image);
      return NULL;
   }
   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pb_temp, IMG_SIZE, IMG_SIZE, GDK_INTERP_NEAREST);
   GtkWidget* img = gtk_image_new_from_pixbuf(pb);//Assigns image to the button
   gtk_button_set_image(GTK_BUTTON(pButton), img);
   
   return pButton;
}

TREASUREHUNTCONTROLLER* create_treasurehunt_controller(VIEWTREASUREHUNT *thv, TREASUREHUNTMODEL* thm){
   assert(thv != NULL && thm != NULL);

   TREASUREHUNTCONTROLLER *thc = malloc(sizeof(TREASUREHUNTCONTROLLER));
   if(thc == NULL){
      printf("Failed to allocate tv.\n");
      return NULL;
   }
   else{
         thc->thm = thm;
         thc->thv = thv;

         for(unsigned int i = 0; i < NUMBER_CHEST; i++){
            thc->chest[i].pChest = load_button_image();
            thc->chest[i].state = unopened;
         }
         randomize_chests(thc); //randomizes the content of the chests
         //links the action and the objects
         g_signal_connect(G_OBJECT(thc->chest[FIRST].pChest), "clicked", G_CALLBACK(click_first_chest), thc);
         g_signal_connect(G_OBJECT(thc->chest[SECOND].pChest), "clicked", G_CALLBACK(click_second_chest), thc);
         g_signal_connect(G_OBJECT(thc->chest[THIRD].pChest), "clicked", G_CALLBACK(click_third_chest), thc);

         
         thc->restart = gtk_button_new_with_label("Recommencer");
         g_signal_connect(G_OBJECT(thc->restart), "clicked", G_CALLBACK(restart_click), thc);//links the action and the objects
         gtk_widget_set_sensitive(thc->restart, FALSE);//invalidates the button until a game has been played
      }
   return thc;
}//end create_treasurehunt_controller

void restart_click(GtkWidget* pW, gpointer data){
   assert(pW != NULL);

   TREASUREHUNTCONTROLLER *thc = (TREASUREHUNTCONTROLLER *)data;
   if(thc == NULL){
      printf("Failed to acces treasurehunt model.\n");
      return;
   }
   else{
      gtk_widget_set_sensitive(thc->restart, FALSE);//Invalidates the restart button
      for(unsigned int i = 0; i < NUMBER_CHEST; i++){
         thc->chest[i].pChest = set_chest_image(thc->chest[i].pChest, "images_coffrets/coffre_ferme.jpg");//switches all the buttons image back to the default closed chest
         thc->chest[i].state = unopened; //'closes' all the chests
      }
      gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Choisissez un coffre!");//reverts label to default state
      thc = randomize_chests(thc);//randomizes the content of the chests
   }
}//end restart_click

void click_first_chest(GtkWidget* pW, gpointer data){
   assert(pW != NULL);

   TREASUREHUNTCONTROLLER *thc = (TREASUREHUNTCONTROLLER *)data;
   if(thc == NULL){
      printf("Failed to acces treasurehunt model.\n");
      return;
   }
   unsigned cpt = opened_chests_counter(thc);
   if(cpt){
      if(thc->chest[FIRST].state == unopened){
         if(thc->chest[FIRST].content == gold){
            thc->chest[FIRST].pChest = set_chest_image(thc->chest[FIRST].pChest, "images_coffrets/coffre_plein.jpg");
            //make all the chests unclickable
            thc->chest[FIRST].state = opened;
            thc->chest[SECOND].state = opened;
            thc->chest[THIRD].state = opened;
            //increment wins
            thc->thm = increment_wins(thc->thm);
            gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Gagné");
         }
         else{
            thc->chest[FIRST].pChest = set_chest_image(thc->chest[FIRST].pChest, "images_coffrets/coffre_vide.jpg");
            //make all the chests unclickable
            thc->chest[FIRST].state = opened;
            thc->chest[SECOND].state = opened;
            thc->chest[THIRD].state = opened;
            //increment loss
            thc->thm = increment_losses(thc->thm);
            gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Perdu");
         }
         thc->thv = redraw_score(thc->thv);
         gtk_widget_set_sensitive(thc->restart, TRUE);
      }
   }
   unsigned int random;
   srand(time(NULL));
   if(thc->chest[FIRST].state == unopened){
      do{
         random = rand() % (2 - 1 + 1) + 1;
         if(random != FIRST && thc->chest[random].content == empty && thc->chest[random].state == unopened){
            thc->chest[random].pChest = set_chest_image(thc->chest[random].pChest, "images_coffrets/coffre_vide.jpg");
            thc->chest[random].state = opened;
            return;
         }
      }while(thc->chest[random].content == gold || random == FIRST);
   }
   //open one of the two other chests
}//end click_chest

void click_second_chest(GtkWidget* pW, gpointer data){
   assert(pW != NULL);

   TREASUREHUNTCONTROLLER *thc = (TREASUREHUNTCONTROLLER *)data;
   if(thc == NULL){
      printf("Failed to acces treasurehunt model.\n");
      return;
   }
   unsigned cpt = opened_chests_counter(thc);
   if(cpt){
      if(thc->chest[SECOND].state == unopened){
         if(thc->chest[SECOND].content == gold){
            thc->chest[SECOND].pChest = set_chest_image(thc->chest[SECOND].pChest, "images_coffrets/coffre_plein.jpg");
            //make all the chests unclickable
            thc->chest[FIRST].state = opened;
            thc->chest[SECOND].state = opened;
            thc->chest[THIRD].state = opened;
            //increment wins
            thc->thm = increment_wins(thc->thm);
            gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Gagné");
         }
         else{
            thc->chest[SECOND].pChest = set_chest_image(thc->chest[SECOND].pChest, "images_coffrets/coffre_vide.jpg");
            //make all the chests unclickable
            thc->chest[FIRST].state = opened;
            thc->chest[SECOND].state = opened;
            thc->chest[THIRD].state = opened;
            //increment loss
            thc->thm = increment_losses(thc->thm);
            gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Perdu");
         }
         thc->thv = redraw_score(thc->thv);
         gtk_widget_set_sensitive(thc->restart, TRUE);
      }
   }
   unsigned int random;
   srand(time(NULL));
   if(thc->chest[SECOND].state == unopened){
      do{
         random = rand() % (2 - 0 + 1) + 0;
         if(random != SECOND && thc->chest[random].content == empty && thc->chest[random].state == unopened){
            thc->chest[random].pChest = set_chest_image(thc->chest[random].pChest, "images_coffrets/coffre_vide.jpg");
            thc->chest[random].state = opened;
            return;
         }
      }while(thc->chest[random].content == gold || random == SECOND);
   }
}//end click_second_chest

void click_third_chest(GtkWidget* pW, gpointer data){
   assert(pW != NULL);

   TREASUREHUNTCONTROLLER *thc = (TREASUREHUNTCONTROLLER *)data;
   if(thc == NULL){
      printf("Failed to acces treasurehunt model.\n");
      return;
   }
   unsigned cpt = opened_chests_counter(thc);
   if(cpt){
      if(thc->chest[THIRD].state == unopened){
         if(thc->chest[THIRD].content == gold){
            thc->chest[THIRD].pChest = set_chest_image(thc->chest[THIRD].pChest, "images_coffrets/coffre_plein.jpg");
            //make all the chests unclickable
            thc->chest[FIRST].state = opened;
            thc->chest[SECOND].state = opened;
            thc->chest[THIRD].state = opened;
            //increment wins
            thc->thm = increment_wins(thc->thm);
            gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Gagné");
         }
         else{
            thc->chest[THIRD].pChest = set_chest_image(thc->chest[THIRD].pChest, "images_coffrets/coffre_vide.jpg");
            //make all the chests unclickable
            thc->chest[FIRST].state = opened;
            thc->chest[SECOND].state = opened;
            thc->chest[THIRD].state = opened;
            //increment loss
            thc->thm = increment_losses(thc->thm);
            gtk_label_set_text(GTK_LABEL(get_state_label(thc, 1)), "Perdu");
         }
         thc->thv = redraw_score(thc->thv);
         gtk_widget_set_sensitive(thc->restart, TRUE);
      }
   }
   unsigned int random;
   srand(time(NULL));
   if(thc->chest[THIRD].state == unopened){
      do{
         random = rand() % (1 - 0 + 1) + 0;
         if(random != THIRD && thc->chest[random].content == empty && thc->chest[random].state == unopened){
            thc->chest[random].pChest = set_chest_image(thc->chest[random].pChest, "images_coffrets/coffre_vide.jpg");
            thc->chest[random].state = opened;
            return;
         }
      }while(thc->chest[random].content == gold || random == THIRD);
   }
}//End click_third_chest

GtkWidget *get_chest(TREASUREHUNTCONTROLLER *thc, int number){
   assert(thc != NULL && number >= 0 && number < NUMBER_CHEST);

   return thc->chest[number].pChest;
}

GtkWidget *get_restart(TREASUREHUNTCONTROLLER *thc){
   assert(thc != NULL);

   return thc->restart;
}

GtkWidget *get_state_label(TREASUREHUNTCONTROLLER *thc, int number){
   assert(thc != NULL);

   return get_label(thc->thv, number);
}

void destroy_controller(TREASUREHUNTCONTROLLER* thc){
   assert(thc != NULL);

   /*if(thc->thv != NULL){
      destroy_view(thc->thv);
      thc->thv = NULL;
   }
   if(thc->thm != NULL){
      destroy_model(thc->thm);
      thc->thm = NULL;
   }
   if(thc->restart != NULL){
      free(thc->restart);
      thc->restart = NULL;
   }*/
   free(thc);
   thc = NULL;
}
