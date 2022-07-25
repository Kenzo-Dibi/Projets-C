/**
 * \file model-connect4.c
 * 
 * \brief This file contains the type definitions and for the Connect 4 game.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 16/07/2022
 * project: INFO0030 Projet 4
 */

#include "model-connect4.h"


struct model_t{
   int lines; /*< The number of lines of the matrix*/
   int columns; /*<The number of columns of the matrix*/
   int **board; /*< the matrix containg the pawns*/
   int numberMoves; /*< counts the number of moves played*/
   int playerCounts; /*< the number of playters in the best scores file*/
   SCORE currentPlayer; /*< the score of the current player*/
   SCORE bestPlayers[BEST + 1]; /*< the 10 best players and the current player*/
   GAMESTATE state; /*< the state of the game(won, lost, drawn, ongoing)*/
};

MODELCONNECT4 *create_model(int lines, int columns, char *playerName, char *bestScores){
   assert(lines > 0 && columns > 0 && playerName != NULL && bestScores != NULL);

   MODELCONNECT4 *MC4 = malloc(sizeof(MODELCONNECT4));
   if(MC4 == NULL){
      printf("Failed to create model\n");
      return NULL;
   }
   else{
      MC4->lines = lines;
      MC4->columns = columns;
      MC4->board = create_matrix(get_lines(MC4), get_columns(MC4));
      if(MC4->board == NULL){
         printf("Failed to create the model'sboard.\n");
         return NULL;
      }
      MC4->numberMoves = 0;
      MC4->state = ongoing;
      MC4->playerCounts = 0;
      load_top_10_score(MC4, bestScores);
      sort_top_10_score(MC4);
      strcpy(MC4->currentPlayer.playerName, playerName);
      MC4->currentPlayer.score = 0;
   }
   return MC4;
}//end create_model

void destroy_model(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);

   free_matrix(MC4->board,get_lines(MC4), get_columns(MC4));
   free(MC4);
}//end destroy_model

int **create_matrix(int lines, int columns){
   assert(lines > 0 && columns > 0);

   int **matrix = calloc(lines, sizeof(int *));
   if(matrix == NULL){
      printf("Failed to create matrix.\n");
      return NULL;
   }
   else{
      for(int i = 0; i < lines; i++){
         matrix[i] = calloc(columns, sizeof(int));
         if(matrix[i] == NULL){
            for(int j = 0; j < columns; j++){
               if(matrix[j] != NULL)
                  free(matrix[j]);
            }
            free(matrix);
            return NULL;
         }
      }
   }
   return matrix;
}//end create_matrix

void free_matrix(int **matrix, int lines, int columns){
   assert(lines > 0 && columns > 0);

   for(int i = 0; i < lines; i++){
      if(matrix[i] != NULL)
         free(matrix[i]);
   }
   free(matrix);
}//end free_matrix

void reset_matrix(MODELCONNECT4 *MC4, int lines, int columns){
   assert(MC4 != NULL && lines > 0 && columns > 0);

   for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         MC4->board[i][j] = 0;
      }//end for-j
   }//end for-i
}//end reset_matrix

int get_lines(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);
   return MC4->lines;
}//end get_lines


int get_columns(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);
   return MC4->columns;
}//end get_columns

int get_position_pawn(MODELCONNECT4 *MC4, int column){
   assert(MC4 != NULL && column >= 0);
   
   for(int i = get_lines(MC4) -1 ;i >= 0; i--){
      if(MC4->board[i][column] == 0){
         return i;
      } 
   }
   return -1; // means the column is already full, do nothing.
}//end get_position_pawn

int get_pawn(MODELCONNECT4 *MC4, int line, int column){
   assert(MC4 != NULL && line >= 0 && column >= 0);

   return MC4->board[line][column];
}// end get_pawn

void put_pawn(MODELCONNECT4 *MC4, int line, int column, int players){
   assert(MC4 != NULL && line >= 0 && column >= 0 && (players == 1 || players == 2));
   
   
   if(players == AI)
      MC4->board[line][column] = 2;// two is the ai
   else if(players == player1)
      MC4->board[line][column] = 1; //one is the players
   //check if the ai or the user has won
}//end put_pawn_model

void load_top_10_score(MODELCONNECT4 *MC4, char *BestScorers){
   assert(MC4 != NULL && BestScorers != NULL);

   FILE *fp = fopen(BestScorers, "r");
   if(fp == NULL){
      printf("Failed to load the file containing the best scores");
      return;
   }
   else{
      int i = 0, check;
      while((i < BEST) && (!feof(fp))){
         check = fscanf(fp, "%s %d\n", MC4->bestPlayers[i].playerName, &MC4->bestPlayers[i].score);
         if(check != 2){
            printf("Failed to parse data in %s.\n", BestScorers);
            return;
         }
         MC4->playerCounts++;
         i++;
      }//while -fp
   }
   printf("Number of player : %d\n", MC4->playerCounts);
   fclose(fp);
}//end load_top_10_score

void write_top_10_score(MODELCONNECT4 *MC4, char *BestScorers){
   assert(MC4 != NULL && BestScorers != NULL);

   FILE *fp = fopen(BestScorers, "w");
   if(fp == NULL){
      printf("Failed to load the file containing the best scores");
      return;
   }
   else{
   for(int i = 0; i < MC4->playerCounts + (get_game_state(MC4) != ongoing) && i < BEST; i++)
      fprintf(fp, "%s %d\n", MC4->bestPlayers[i].playerName, MC4->bestPlayers[i].score);
   }
   fclose(fp);
}//end write_top_10_score



void sort_top_10_score(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);

   //quick sort
   int min, tmp;
   char tmpName[MAXCHARACTER];
   for(int i = 0; i < (MC4->playerCounts) -1; i++){
      min = i;
      for(int j = i + 1; j < (MC4->playerCounts) ; j++){
         if(MC4->bestPlayers[j].score < MC4->bestPlayers[min].score){
            min = j;
         }
         if(i != min){
            strcpy(tmpName, MC4->bestPlayers[i].playerName);
            tmp = MC4->bestPlayers[i].score;
            MC4->bestPlayers[i].score = MC4->bestPlayers[min].score;
            strcpy(MC4->bestPlayers[i].playerName, MC4->bestPlayers[min].playerName);
            MC4->bestPlayers[min].score = tmp;
            strcpy(MC4->bestPlayers[min].playerName, tmpName);
         }
      }
   }
   for(int i = 0; i < MC4->playerCounts; i++){
      printf("joueur: %s coups: %d\n", MC4->bestPlayers[i].playerName, MC4->bestPlayers[i].score);
   }
}//end sort_top_10_score

unsigned int get_game_state(MODELCONNECT4* MC4){
   assert(MC4 != NULL);

   return MC4->state;
}// end get_game_state

void set_game_state(MODELCONNECT4* MC4, GAMESTATE state){
   assert(MC4 != NULL);

   MC4->state = state;
}//end set_game_state

void increment_number_of_moves(MODELCONNECT4 *MC4, int inc){
   assert(MC4 != NULL && inc >= 0);

   MC4->numberMoves += inc;
}//end incrment_number_of_moves

void set_number_of_moves(MODELCONNECT4 *MC4, int n){
   assert(MC4 != NULL && n >= 0);

   MC4->numberMoves = n;
}//end set_number_of_moves

int get_number_of_players(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);

   return MC4->playerCounts;
}//end get_number_of_players

int get_players_score(MODELCONNECT4 *MC4, int n){
   assert(MC4 != NULL && n >= 0);
   return MC4->bestPlayers[n].score;
}//end get_players_score

char *get_player_name(MODELCONNECT4 *MC4, int n){
   assert(MC4 != NULL && n >= 0);
   return MC4->bestPlayers[n].playerName;
}//end get_player_name

/*for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         
      }
   }*/

void ai_response(MODELCONNECT4 *MC4){
   //check if it has 3 pawns already aligned
   for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         if(three_pawns_aligned(MC4, i , j, AI)){
            printf("The ai has won.\n");
            // window pop
            MC4->state = lost;
            return;
         }

      }
   }
   //check if the player has 3 pawns already aligned
   for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         if(three_pawns_aligned(MC4, i , j, player1)){
            if(four_pawns_aligned(MC4, i , j, AI)){
               printf("The ai has won.\n");
               // window pop
               MC4->state = lost;
               return;
            }
            return;
         }

      }
   }
   //check if it has 2 pawns already aligned
   for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         if(two_pawns_aligned(MC4, i , j, AI)){
            if(four_pawns_aligned(MC4, i , j, AI)){
               printf("The ai has won.\n");
               // window pop
               MC4->state = lost;
               return;
            }
            return;
         }
      }
   }
   //check if the player has 2 pawns already aligned
   for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         if(two_pawns_aligned(MC4, i , j, player1)){
            if(four_pawns_aligned(MC4, i , j, AI)){
               printf("The ai has won.\n");
               // window pop
               MC4->state = lost;
               return;
            }
            return;
         }
      }
   }
   //if none of the above
   //play a random move
   pick_random_move(MC4);
}//end ai response

int four_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn){
   assert(MC4 != NULL);

   if(MC4->state == ongoing){
      if(column - 3 >= 0){
         if(get_pawn(MC4, line, column - 3) == turn && get_pawn(MC4, line, column - 2) == turn && get_pawn(MC4, line, column - 1) == turn && get_pawn(MC4, line, column) == turn)
               return 1;// 
      }
      if(column - 3 >= 0 && line - 3 >= 0){
         if(get_pawn(MC4, line - 3, column - 3) == turn && get_pawn(MC4, line - 2, column - 2) == turn && get_pawn(MC4, line - 1, column - 1) == turn && get_pawn(MC4, line, column) == turn)
            return 1;
      }
      if(line - 3 >= 0){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line - 1, column) == turn && get_pawn(MC4, line - 2, column) == turn && get_pawn(MC4, line - 3, column) == turn)
               return 1;// 
      }
      if(line - 3 >= 0 && column + 3 < get_columns(MC4)){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line - 1, column + 1) == turn && get_pawn(MC4, line -2, column + 2) == turn && get_pawn(MC4, line - 3, column + 3) == turn)
               return 1;// 
      }
      if(column + 3 < get_columns(MC4)){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line, column + 1) == turn && get_pawn(MC4, line, column + 2) == turn && get_pawn(MC4, line, column + 3) == turn)
               return 1;// 
         }
      }
   return 0;
}//end four_pawns_aligned

int three_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn){
   assert(MC4 != NULL);

   int pos;
   if(MC4->state == ongoing){
      if(column - 3 >= 0){
         if(get_pawn(MC4, line, column - 2) == turn && get_pawn(MC4, line, column - 1) == turn && get_pawn(MC4, line, column) == turn){
            pos = get_position_pawn(MC4, column - 3);
            if(pos != - 1 && pos  == line){
               put_pawn(MC4, pos, column - 3, AI);
               return 1;// ai win
            }
         }
      }
      if(column - 3 >= 0 && line - 3 >= 0){
         if(get_pawn(MC4, line - 2, column - 2) == turn && get_pawn(MC4, line - 1, column - 1) == turn && get_pawn(MC4, line, column) == turn){
            pos = get_position_pawn(MC4, column - 3);
            if(pos != - 1 && pos == line - 3){
               put_pawn(MC4, pos, column - 3, AI);
               return 1;// ai win
            }
         }
      }
      if(line - 3 >= 0){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line - 1, column) == turn && get_pawn(MC4, line - 2, column) == turn){
            pos = get_position_pawn(MC4, column);
            if(pos != - 1 && pos == line - 3){
               put_pawn(MC4, pos, column, AI);
               return 1;// ai win
            }
         }
      }
      if(line - 3 >= 0 && column + 3 < get_columns(MC4)){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line - 1, column + 1) == turn && get_pawn(MC4, line - 2, column + 2) == turn){
            pos = get_position_pawn(MC4, column + 3);
            if(pos != - 1 && pos == line - 3){
               put_pawn(MC4, pos, column + 3, AI);
               return 1;// ai win
            }
         }
      }
      if(column + 3 < get_columns(MC4)){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line, column + 1) == turn && get_pawn(MC4, line, column + 2) == turn){
            pos = get_position_pawn(MC4, column + 3);
            if(pos != - 1 && pos == line){
               put_pawn(MC4, pos, column + 3, AI);
               return 1;// ai win
            }
         }
      }
   }
   return 0;
}//end three_pawns_aligned

int two_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn){
   assert(MC4 != NULL);

   int pos;
   if(MC4->state == ongoing){
      if(column - 2 >= 0){
         if(get_pawn(MC4, line, column - 1) == turn && get_pawn(MC4, line, column) == turn){
            pos = get_position_pawn(MC4, column - 2);
            if(pos != -1 && pos  == line){
               put_pawn(MC4, pos, column - 2, AI);
               return 1;
            }
         }
      }
      if(column - 2 >= 0 && line - 2 >= 0){
         if(get_pawn(MC4, line - 1, column - 1) == turn && get_pawn(MC4, line, column) == turn){
            pos = get_position_pawn(MC4, column - 2);
            if(pos != -1 && pos == line - 2){
               put_pawn(MC4, pos, column - 2, AI);
               return 1;
            }
         }
      }
      if(line - 2 >= 0){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line - 1, column) == turn){
            pos = get_position_pawn(MC4, column);
            if(pos != -1 && pos == line - 2){
               put_pawn(MC4, pos, column, AI);
               return 1;
            }
         }
      }
      if(line - 2 >= 0 && column + 2 < get_columns(MC4)){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line - 1, column + 1) == turn){
            pos = get_position_pawn(MC4, column + 2);
            if(pos != -1 && pos == line - 2){
               put_pawn(MC4, pos, column + 2, AI);
               return 1;
            }
         }
      }
      if(column + 2 < get_columns(MC4)){
         if(get_pawn(MC4, line, column) == turn && get_pawn(MC4, line, column + 1) == turn){
            pos = get_position_pawn(MC4, column + 2);
            if(pos != -1 && pos == line){
               put_pawn(MC4, pos, column + 2, AI);
               return 1;
            }
         }
      }
   }
   return 0;
}//end two_pawns_aligned

void pick_random_move(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);

   int line, column;
   srand(time(NULL));
   if(MC4->state == ongoing){
      do{
         column = rand() %((get_columns(MC4) - 1) -0 + 1) + 0;
         line = get_position_pawn(MC4, column);
      }while(line == -1);

      put_pawn(MC4, line, column, 2);
   }
   //printf("le pion: %d\n", get_pawn(MC4, line, column));
   //printf("Ai has put a pawn at :(%d, %d)\n", line, column);
}//end pick_random_move

void draw(MODELCONNECT4 *MC4){
   assert(MC4 != NULL);

   for(int i = 0; i < get_lines(MC4); i++){
      for(int j = 0; j < get_columns(MC4); j++){
         if(MC4->board[i][j] == 0)
            return;
      }
   }
   MC4->state = drawn;
}