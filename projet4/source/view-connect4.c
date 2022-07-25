/**
 * \file view-connect4.c
 * 
 * \brief This file contains the type definitions and for the Connect 4 game.
 * 
 * \author: Kenzo s210122
 * \date: 16/07/2022
 * project: INFO0030 Projet 4
 */

#include "view-connect4.h"  

struct view_t{
    MODELCONNECT4 *MC4; /*< a pointer to MODELCONNECT4*/
    
    GtkWidget ***board; /*< the board on screen*/
    GtkWidget **hBox; /*< horizontal boxes*/
    GtkWidget *vBox; /*< a vertical box*/
    GtkWidget *pWindow; /*< the game's window*/
};

/**
 * \fn static void destroy_window(GtkWidget *pWindow, gpointer data)
 * \brief destroys a window
 * 
 * \param pWindow a pointer to GtkWidget
 * 
 * \pre pWindow != NULL
 * \post the window has been destroyed
 */
static void destroy_window(GtkWidget *pWindow, gpointer data){
   assert(pWindow != NULL);

   GtkWidget *pW = GTK_WIDGET(data);
   gtk_widget_destroy(GTK_WIDGET(pW));
}//end destroy_window

VIEWCONNECT4 *create_view(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);

   VIEWCONNECT4 *VC4 = malloc(sizeof(VIEWCONNECT4));
   if(VC4 == NULL){
      printf("Failed to create view.\n");
      return NULL;
   }
   else{
      VC4->MC4 = MC4;
      //board creation
      VC4->board = create_board(VC4);
      if(VC4->board == NULL){
         printf("Failed to create the view's board.\n");
         return NULL;
      }
      //the window's creation
      VC4->pWindow = create_window();
      VC4->vBox = gtk_vbox_new(FALSE, 0);
      VC4->hBox = malloc((get_lines(VC4->MC4)) * sizeof(GtkWidget *));
      if(VC4->hBox == NULL){
         printf("Failed to create horizontal boxes.\n");
         return NULL;
      }
      for(int i = 0; i < get_lines(VC4->MC4); i++){
         VC4->hBox[i] = gtk_hbox_new(FALSE, 0);
      }
   }

   return VC4;
}//end create_view

void destroy_view(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);
   
   //free_board(VC4); causes a segmentation fault
   free(VC4);
}//end destroy_view

GtkWidget *create_window(){

   GtkWidget *pW = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   //title
   gtk_window_set_title(GTK_WINDOW(pW), "Connect 4");
   //the app's icon
   gtk_window_set_icon_from_file(GTK_WINDOW(pW), "source/pions/icon.png", NULL);
   //window size
   gtk_window_set_default_size(GTK_WINDOW(pW), CUSTOM_WINDOW_SIZE, CUSTOM_WINDOW_SIZE);
   //close action
   g_signal_connect(G_OBJECT(pW), "destroy", G_CALLBACK(gtk_main_quit), NULL);
   
   return pW;
}//end create_window

GtkWidget *get_window(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);

   return VC4->pWindow;
}//end get_window

GtkWidget *load_image(char *image){
   assert(image != NULL);

   //loads the image and resizes it
   GdkPixbuf *pbTemp = gdk_pixbuf_new_from_file(image, NULL);
   if(!pbTemp){
      printf("Failed to load image %s.\n", image);
      return NULL;
   }
   GdkPixbuf *pb = gdk_pixbuf_scale_simple(pbTemp, IMG_SIZE, IMG_SIZE, GDK_INTERP_NEAREST);
   GtkWidget *img = gtk_image_new_from_pixbuf(pb);//Assigns image to the button
   
   return img;
}//end load_image

void update_image(GtkWidget *pCase,char *image){
   assert(pCase != NULL && image != NULL);

   GdkPixbuf *pbTemp = gdk_pixbuf_new_from_file(image, NULL);
   if(!pbTemp){
      printf("Failed to load image %s.\n", image);
      return;
   }
    GdkPixbuf *pb = gdk_pixbuf_scale_simple(pbTemp, IMG_SIZE, IMG_SIZE, GDK_INTERP_NEAREST);
   gtk_image_set_from_pixbuf(GTK_IMAGE(pCase), pb);
}//end update_image

GtkWidget ***create_board(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);

   
   GtkWidget ***board = malloc(get_lines(VC4->MC4) * sizeof(GtkWidget **));
   if(board == NULL){
      return NULL;
   }
   for(int i = 0; i < get_lines(VC4->MC4); i++){
      board[i] = malloc(get_columns(VC4->MC4) * sizeof(GtkWidget *));
      if(board[i] == NULL){
         for(int j = 0; j < get_lines(VC4->MC4); j++){
            if(board[j] != NULL){
               free(board[j]);
               board[j] = NULL;
            }
         }
         free(board);
         board = NULL;
         return NULL;
      }
   }
   for(int i = 0; i < get_lines(VC4->MC4); i++){
      for(int j = 0; j < get_columns(VC4->MC4); j++){
         board[i][j] = load_image("source/pions/bleu.gif"); //Default board with no pawns in yet
      }
   }

   return board;
}//end create_matrix

GtkWidget ***get_board(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);

   return VC4->board;
}//end get_board

void free_board(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);

   for(int i = 0; i < get_lines(VC4->MC4); i++){
      if(VC4->board[i] != NULL){
         free(VC4->board[i]);
         VC4->board[i] = NULL;
      }
   }
   free(VC4->board);
   VC4->board = NULL;
}//end free_matrix_view

GtkWidget *get_vbox(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);
   return VC4->vBox;
}//end get_vbox

GtkWidget *get_hbox(VIEWCONNECT4 *VC4, int line){
   assert(VC4 != NULL && line >= 0);
   return VC4->hBox[line];
}//end get_hbox

void update_board(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);

   for(int i = 0; i < get_lines(VC4->MC4); i++){
      printf("[ ");
      for(int j = 0; j < get_columns(VC4->MC4); j++){
         
            if(get_pawn(VC4->MC4, i, j) == player1){
               update_image(VC4->board[i][j], "source/pions/jaune.gif");
               printf("1 ");
            }
            else if(get_pawn(VC4->MC4, i, j) == AI){
               update_image(VC4->board[i][j], "source/pions/rouge.gif");
               printf("2 ");
            }
            else if(get_pawn(VC4->MC4, i, j) == 0){
               update_image(VC4->board[i][j], "source/pions/bleu.gif");
               printf("0 ");
            }
         }
         printf("]\n");
      }
   gtk_widget_show_all(get_window(VC4));
}//end update_board

void create_about(){
   GtkWidget *pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
   GtkWidget *pGame = gtk_label_new("game: Connect-4\n");
   GtkWidget *pCredits = gtk_label_new("credits: Kenzo Dibi s210122");

   gtk_window_set_default_size(GTK_WINDOW(pWindow), 200, 100);
   gtk_window_set_title(GTK_WINDOW(pWindow), "about");

   g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(destroy_window), pWindow);

   gtk_box_pack_start(GTK_BOX(vBox), pGame, TRUE, TRUE, 0);
   gtk_box_pack_start(GTK_BOX(vBox), pCredits, TRUE, TRUE, 0);
   

   gtk_container_add(GTK_CONTAINER(pWindow), vBox);
   gtk_widget_show_all(pWindow);
}//end create_about

void create_rule(){
   GtkWidget *pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
   GtkWidget *pRule = gtk_label_new("\t\tAlign 4 pawns to win!\n diagonally vertically or horizontaly");

   gtk_window_set_default_size(GTK_WINDOW(pWindow), 250, 150);
   gtk_window_set_title(GTK_WINDOW(pWindow), "rules");

   g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(destroy_window), pWindow);

   gtk_box_pack_start(GTK_BOX(vBox), pRule, TRUE, TRUE, 0);

   gtk_container_add(GTK_CONTAINER(pWindow), vBox);
   gtk_widget_show_all(pWindow);
}//end create_rule

void create_best_scores(VIEWCONNECT4 *VC4){
   assert(VC4 != NULL);

   GtkWidget *pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
   GtkWidget *pLabel[get_number_of_players(VC4->MC4)];
   char message[MAXCHARACTER];
   gtk_window_set_default_size(GTK_WINDOW(pWindow), 250, 350);
   gtk_window_set_title(GTK_WINDOW(pWindow), "best scores");

   g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(destroy_window), pWindow);
   
   GtkWidget *pScores = gtk_label_new("Best scores:\n");
   gtk_box_pack_start(GTK_BOX(vBox), pScores, FALSE, FALSE, 0);
   int cnt = 1;
   for(int i = 0; i < get_number_of_players(VC4->MC4); i++){
      sprintf(message, "%d. %s  %d\n", cnt, get_player_name(VC4->MC4, i), get_players_score(VC4->MC4, i));
      pLabel[i] = gtk_label_new(message);
      gtk_box_pack_start(GTK_BOX(vBox), pLabel[i], FALSE, FALSE, 0);
      cnt++;
   }

   gtk_container_add(GTK_CONTAINER(pWindow), vBox);
   gtk_widget_show_all(pWindow);
}//end create_best_scores