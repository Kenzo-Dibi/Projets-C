/**
 * \file model-connect4.h
 * 
 * \brief This file contains the type definitions and for the Connect 4 game.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 16/07/2022
 * projet: INFO0030 Project 4
 */

/**
 * Include guards to prevent include multiple times the same elements
 */
#ifndef __MODEL_CONNECT4__
#define __MODEL_CONNECT4__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

/**
 * \brief the maximum length of a name a user can input
 */
#define MAXCHARACTER 301

/**
 * \brief the the of lines of the base game
 */
#define DEFAULT_LINES 6

/**
 * \brief the number of columns of the base game
 */
#define DEFAULT_COLUMNS 7

/**
 * \brief the minimum number of line of the game
 */
#define MINIMUM_LINES 4

/**
 * \brief the minimum number of columns of the game
 */
#define MINIMUM_COLUMNS 4

/**
 * \brief the top 10 best player
 */
#define BEST 10

/**
 * \enum players
 * \brief used to check whose turn it is to play
 */
typedef enum player{player1 = 1, AI}PLAYER;

/**
 * \enum gameState
 * \brief the state of the game
 */
typedef enum gamestate{
    won, /*< the player has won*/
    lost, /*< the player has lost*/
    drawn, /*< the match is draw*/
    ongoing /*< the game is not finished yet*/
}GAMESTATE;

/**
 * \struct score
 * \brief the score
 */
typedef struct score{
    char playerName[MAXCHARACTER]; /*< the name of the player*/
    int score; /*< the score of the player*/
}SCORE;

/**
 * \struct model_t
 * \brief the model of the connect 4 game
 */
typedef struct model_t MODELCONNECT4;

/**
 * \fn MODELCONNECT4 *create_model(int lines, int columns, char *playerName, char *bestScores)
 * \brief creates the model
 * 
 * \param lines the number of lines the board will have
 * \param columns the number of columns the board will have
 * \param playerName the name of the current player
 * \param bestScores the filed containing the top 10 scores and players
 * 
 * \pre lines > 0 && colums > 0 && playerName != NULL && bestScores != NULL
 * \post the model has been created
 */
MODELCONNECT4 *create_model(int lines, int columns, char *playerName, char *bestScores);

/**
 * \fn destroy_model(MODELCONNECT4 *MC4)
 * \brief
 * \param MC4 a pointer to MODELCONNECT4
 * \pre MC4 != NULL
 * \post the model has been destroyed
 */
void destroy_model(MODELCONNECT4 *MC4);

/**
 * \fn int **create_matrix(int lines, int columns)
 * \brief creates the matrix
 * 
 * \param lines the number of lines the board will have
 * \param columns the number of columns the board will have
 * 
 * \pre lines > 0 && columns > 0
 * \post the matrix has been created
 */
int **create_matrix(int lines, int columns);

/**
 * \fn int **create_matrix(int lines, int columns)
 * \brief frees the matrix
 * 
 * \param matrix the matrix
 * \param lines the number of lines the board has
 * \param columns the number of columns the board has
 * 
 * \pre lines > 0 && columns > 0
 * \post the matrix has been freed
 */
void free_matrix(int **matrix, int lines, int columns);

/**
 * \fn int get_matrix(MODELCONNECT4 *MC4, int lines, int columns)
 * \brief gives the content of case in the matrix
 * 
 * \param matrix the matrix
 * \param lines the number of lines the board has
 * \param columns the number of columns the board has
 * 
 * \pre MC4 != NULL && lines >= 0 && columns >= 0
 * \post the matrix has been freed
 */
//int get_matrix(MODELCONNECT4 *MC4, int lines, int columns); not utilized

/**
 * \fn void reset_matrix(MODELCONNECT4 *MC4, int lines, int columns)
 * \brief fills the matrix with 0s
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param lines the number of lines the board has
 * \param columns the number of columns the board has
 * 
 * \pre MC4 != NULL && lines >= 0 && columns >= 0
 * \post the matrix has been reset
 */
void reset_matrix(MODELCONNECT4 *MC4, int lines, int columns);

/**
 * \fn int get_lines(MODELCONNECT4 *MC4)
 * \brief gives the number of lines the board has
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the number of lines is returned
 */
int get_lines(MODELCONNECT4 *MC4);

/**
 * \fn int get_columns(MODELCONNECT4 *MC4)
 * \brief gives the number of columns the board has
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the number of columns is returned
 */
int get_columns(MODELCONNECT4 *MC4);

/**
 * \fn void put_pawn(MODELCONNECT4 *MC4, int line, int column, int players)
 * \brief puts a pawn in the board
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param lines the line where the pawn will fall
 * \param columns the column where the pawn will fall.
 * 
 * \pre MC4 != NULL && && line >= 0 && column >= 0 && (players == player1 || players == AI)
 * \post the pawn has fallen in the board
 */
void put_pawn(MODELCONNECT4 *MC4, int line, int column, int players);

/**
 * \fn int get_position_pawn(MODELCONNECT4 *MC4, int column)
 * \brief
 * \param MC4 a pointer to MODELCONNECT4
 * \param columns the column where the pawn will fall.
 * \pre MC4 != NULL &&column >= 0
 * \post
 */
int get_position_pawn(MODELCONNECT4 *MC4, int column);

/**
 * \fn int get_pawn(MODELCONNECT4 *MC4, int line, int column)
 * \brief
 * \param MC4 a pointer to MODELCONNECT4
 * \param columns the column where the pawn will fall.
 * \pre MC4 != NULL && && line >= 0 && column >= 0 
 * \post
 */
int get_pawn(MODELCONNECT4 *MC4, int line, int column);

/**
 * \fn void load_top_10_score(MODELCONNECT4 *MC4, char *BestScorers)
 * \brief loads the list containing the top 10 scorers
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param BestScorers the list containing the top scorers
 * 
 * \pre MC4 != NULL && BestScorers != NULL
 * \post
 */
void load_top_10_score(MODELCONNECT4 *MC4, char *BestScorers);

/**
 * \fn void write_top_10_score(MODELCONNECT4 *MC4, char *BestScorers)
 * \brief writes the top 10 scorers in the file before closing the game
 * \param MC4 a pointer to MODELCONNECT4
 * \param BestScorers the list containing the top scorers
 * \pre MC4 != NULL && BestScorers != NULL
 * \post
 */
void write_top_10_score(MODELCONNECT4 *MC4, char *BestScorers);

/**
 * \fn void (MODELCONNECT4 *MC4)
 * \brief sorts the top 10 scorers
 * \param MC4 a pointer to MODELCONNECT4
 * \pre MC4 != NULL && BestScorers != NULL
 * \post
 */
void sort_top_10_score(MODELCONNECT4 *MC4);

/**
 * \fn unsigned int get_game_state(MODELCONNECT4* MC4)
 * \brief returns the current state of the game
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the state of the game is returned
 */
unsigned int get_game_state(MODELCONNECT4* MC4);

/**
 * \fn void set_game_state(MODELCONNECT4* MC4, GAMESTATE state)
 * \brief sets state of the game
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param state the state of the game (won, lost, drawn, ongoing)
 * 
 * \pre MC4 != NULL
 * \post the state of the game has been set
 */
void set_game_state(MODELCONNECT4* MC4, GAMESTATE state);

/**
 * \fn void increment_number_of_moves(MODELCONNECT4 *MC4)
 * \brief the number of moves played has been increased
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param inc the increment
 * 
 * \pre MC4 != NULL && increment >= 0
 * \post the number of moves played has been incremented
 */
void increment_number_of_moves(MODELCONNECT4 *MC4, int inc);

/**
 * \fn void set_number_of_moves(MODELCONNECT4 *MC4, int n)
 * \brief sets the number of move to the wanted value
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param n the number of moves
 * 
 * \pre MC4 != NULL && n >= 0
 * \post the number of moves played has been set
 */
void set_number_of_moves(MODELCONNECT4 *MC4, int n);

/**
 * \fn int get_number_of_players(MODELCONNECT4 *MC4)
 * \brief gives the number of players
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the number of players played has been returned
 */
int get_number_of_players(MODELCONNECT4 *MC4);

/**
 * \fn int get_players_score(MODELCONNECT4 *MC4, int n)
 * \brief gives a player's score
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param n the wanted player
 * 
 * \pre MC4 != NULL && n >= 0
 * \post the player's score has been returned
 */
int get_players_score(MODELCONNECT4 *MC4, int n);

/**
 * \fn char *get_player_name(MODELCONNECT4 *MC4, int n)
 * \brief gives a player's name
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param n the wanted player
 * 
 * \pre MC4 != NULL && n >= 0
 * \post the player's name has been returned
 */
char *get_player_name(MODELCONNECT4 *MC4, int n);

/**
 * \fn void ai_response(MODELCONNECT4 *MC4)
 * \brief the ai response to the player's turn
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL && n >= 0
 * \post the player's name has been returned
 */
void ai_response(MODELCONNECT4 *MC4);

/**
 * \fn int two_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn)
 * \brief the ai tries to align three pawn
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param line the line where the first of the four pawn is
 * \param column the column where the first of the four pawn is
 * \param turn the ai's turn
 * 
 * \pre MC4 != NULL
 * \post the ai has made a move or not
 */
int two_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn);

/**
 * \fn int three_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn)
 * \brief the ai tries to find the winning move
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param line the line where the first of the four pawn is
 * \param column the column where the first of the four pawn is
 * \param turn the ai's turn
 * 
 * \pre MC4 != NULL
 * \post the ai has made a move or not
 */
int three_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn);

/**
 * \fn int four_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn)
 * \brief checks if someone has won
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * \param line the line where the first of the four pawn is
 * \param column the column where the first of the four pawn is
 * \param turn the ai's turn or the player's turn
 * 
 * \pre MC4 != NULL
 * \post the state of the game is return
 * \return 
 *     0 : didn't win yet
 *     1 : won
 */
int four_pawns_aligned(MODELCONNECT4 *MC4, int line, int column, int turn);


/**
 * \fn void pick_random_move(MODELCONNECT4 *MC4)
 * \brief picks a random place to put the ai's pawn
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the ai has made a random move
 */
void pick_random_move(MODELCONNECT4 *MC4);

/**
 * \fn void draw(MODELCONNECT4 *MC4)
 * \brief checks if the game has been drawn
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the state of the game is changed to drawn if the board is full an no one won
 */
void draw(MODELCONNECT4 *MC4);
#endif
