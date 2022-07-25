/**
 * \file controller-connect4.c
 * \brief connect-4's controller program
 * \author: Dan Gui s216374,Dibi Kenzo s210122 Group 12
 * \date: 10/05/2022
 * project: INFO0030 Project 4
 */

#include "controller-connect4.h"

struct controller_t{
   MODELCONNECT4 *MC4;
   VIEWCONNECT4 *VC4;

   GtkWidget *menuBar;

   GtkWidget *gameMenu;
   GtkWidget *gameItem;
   GtkWidget *newgameItem;
   GtkWidget *bestplayersItem;
   GtkWidget *quitItem;

   GtkWidget *helpMenu;
   GtkWidget *helpItem;
   GtkWidget *aboutItem;
   GtkWidget *gamerulesItem;

   GtkWidget **pbuttons;
};

CONTROLLERCONNECT4 *create_controller(void *VC4, MODELCONNECT4 *MC4){
   assert(VC4 != NULL && MC4 != NULL);

   CONTROLLERCONNECT4 *CC4 = malloc(sizeof(CONTROLLERCONNECT4));
   if(CC4 == NULL){
      printf("Failed to create controller.\n");
      return NULL;
   }
   else{
      CC4->MC4 = MC4;
      CC4->VC4 = VC4;

      CC4 = create_menu(get_window(CC4->VC4),CC4);
      //adds the elements inside the window
      gtk_box_pack_start(GTK_BOX(get_vbox(CC4->VC4)), CC4->menuBar, FALSE, FALSE, 2);
      for(int i = 0; i < get_lines(CC4->MC4); i++){
         gtk_box_pack_start(GTK_BOX(get_vbox(CC4->VC4)), get_hbox(CC4->VC4, i), TRUE, TRUE, 0);
         for(int j = 0; j < get_columns(CC4->MC4); j++){
            gtk_box_pack_start(GTK_BOX(get_hbox(CC4->VC4, i)), get_board(CC4->VC4)[i][j], TRUE, TRUE, 0);
         }
      }
      GtkWidget *pHbox = gtk_hbox_new(FALSE, 0);
      gtk_box_pack_start(GTK_BOX(get_vbox(CC4->VC4)), pHbox, TRUE, TRUE, 2);
      CC4->pbuttons = malloc(get_columns(CC4->MC4) * sizeof(GtkWidget *));
      if(CC4->pbuttons == NULL){
         printf("Failed to create buttons.\n");
         return NULL;
      }
      for(int i = 0; i < get_columns(CC4->MC4); i++){
         CC4->pbuttons[i] = gtk_button_new();
         gtk_box_pack_start(GTK_BOX(pHbox), GTK_WIDGET(CC4->pbuttons[i]), TRUE, TRUE, 0);
         g_signal_connect(G_OBJECT(CC4->pbuttons[i]), "clicked", G_CALLBACK(click_board_button), CC4);
      }

      gtk_container_add(GTK_CONTAINER(get_window(CC4->VC4)), get_vbox(CC4->VC4));
      gtk_widget_show_all(get_window(CC4->VC4));
   }
   return CC4;
}//end create_controller

 void destroy_controller(CONTROLLERCONNECT4 *CC4){
   assert(CC4 != NULL);

   destroy_buttons(CC4);
   free(CC4);
 }//end destroy_controller

void destroy_buttons(CONTROLLERCONNECT4 *CC4){
   assert(CC4 != NULL);
   
   free(CC4->pbuttons);
}//end destroy_buttons

CONTROLLERCONNECT4 *create_menu(GtkWidget *pWindow, CONTROLLERCONNECT4 *CC4){
   assert(pWindow != NULL && CC4 != NULL);

   CC4->menuBar = gtk_menu_bar_new();
   CC4->gameMenu = gtk_menu_new();
   CC4->helpMenu = gtk_menu_new();
   CC4->gameItem = gtk_menu_item_new_with_mnemonic("game");
   CC4->helpItem = gtk_menu_item_new_with_mnemonic("help");

   gtk_menu_item_set_submenu(GTK_MENU_ITEM(CC4->gameItem), CC4->gameMenu);
   gtk_menu_item_set_submenu(GTK_MENU_ITEM(CC4->helpItem), CC4->helpMenu);

   CC4->aboutItem = gtk_menu_item_new_with_label("about");
   CC4->gamerulesItem = gtk_menu_item_new_with_label("rules");
   CC4->newgameItem = gtk_menu_item_new_with_label("new game");
   CC4->bestplayersItem = gtk_menu_item_new_with_label("best scores");
   CC4->quitItem = gtk_menu_item_new_with_label("quit");
   //signal connects
   g_signal_connect(G_OBJECT(CC4->quitItem), "activate", G_CALLBACK(gtk_main_quit), NULL);
   //about
   g_signal_connect(G_OBJECT(CC4->aboutItem), "activate", G_CALLBACK(about), CC4);
   //rules
   g_signal_connect(G_OBJECT(CC4->gamerulesItem), "activate", G_CALLBACK(rules), CC4);
   //best scores
   g_signal_connect(G_OBJECT(CC4->bestplayersItem), "activate", G_CALLBACK(best_scores), CC4);
   //new game
   g_signal_connect(G_OBJECT(CC4->newgameItem), "activate", G_CALLBACK(new_game), CC4);

   GtkAccelGroup *accelerator = gtk_accel_group_new();
   gtk_window_add_accel_group(GTK_WINDOW(get_window(CC4->VC4)), accelerator);

   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->gameMenu),CC4->newgameItem);
   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->gameMenu), CC4->bestplayersItem);
   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->gameMenu), CC4->quitItem);
   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->menuBar), CC4->gameItem);
   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->helpMenu),CC4->aboutItem);
   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->helpMenu),CC4->gamerulesItem);
   gtk_menu_shell_append(GTK_MENU_SHELL(CC4->menuBar),CC4->helpItem);
   
   return CC4;
}//end create_menu

void click_board_button(GtkWidget* pWindow, gpointer data){
   assert(pWindow != NULL);
  
   CONTROLLERCONNECT4 *CC4 = (CONTROLLERCONNECT4 *)data;

   int column;
   for(int i = 0; i < get_columns(CC4->MC4); i++){
      if(pWindow == CC4->pbuttons[i]){
         column = i;
      }
   }
   if(get_game_state(CC4->MC4) != ongoing){
      printf("The game has already ended start a new one if you wish to keep playing.\n");
      return;
   }
   else{
      int line = get_position_pawn(CC4->MC4, column);
      if(line != -1){//if the line isn't full put a pawn
         put_pawn(CC4->MC4, line, column, player1);
         //check if player has won
         printf("a pawn has been placed at :(%d, %d)\n", line, column);
         for(int i = 0; i < get_lines(CC4->MC4); i++){
            for(int j = 0; j < get_columns(CC4->MC4); j++){
               if(four_pawns_aligned(CC4->MC4, i, j, player1)){
                  increment_number_of_moves(CC4->MC4, 1);
                  set_game_state(CC4->MC4, won);
                  printf("You won!.\n");
                  update_board(CC4->VC4);
                  //window popup

                  //update top 10 score if needed
                  return;
               }
            }
         }
         //ai repsonse
         ai_response(CC4->MC4);
         //check if it's a draw
         draw(CC4->MC4);
         //increment number of moves
         increment_number_of_moves(CC4->MC4, 2);
         //refresh the board
         update_board(CC4->VC4);
      }
   }
   return;
}//end click_button

void new_game(GtkWidget *pWindow, gpointer data){
   assert(pWindow != NULL);

   CONTROLLERCONNECT4 *CC4 = (CONTROLLERCONNECT4 *)data;
   if(get_game_state(CC4->MC4) != ongoing){
      set_number_of_moves(CC4->MC4, 0);
      set_game_state(CC4->MC4, ongoing);
      reset_matrix(CC4->MC4, get_lines(CC4->MC4), get_columns(CC4->MC4));
      update_board(CC4->VC4);
      printf("A new game has started.\n");
   }
}//end new_game

void about(GtkWidget *pWindow, __attribute__((unused)) gpointer data){
   assert(pWindow != NULL);
   
   create_about();
}//end about

void rules(GtkWidget *pWindow, __attribute__((unused)) gpointer data){
   assert(pWindow != NULL);

   create_rule();
}//end rules

void best_scores(GtkWidget *pWindow, gpointer data){
   assert(pWindow != NULL);

   CONTROLLERCONNECT4 *CC4 = (CONTROLLERCONNECT4 *)data;
   create_best_scores(CC4->VC4);
}//end best_scores

GtkWidget *get_button(CONTROLLERCONNECT4 *CC4, int column){
   assert(CC4 != NULL && column >= 0);

   return CC4->pbuttons[column];
}//end get_button