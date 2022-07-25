/**
 * \file controller-connect4.h
 * \brief Controller (pattern MVC) for a connect-4's game management
 * \author: Dan Gui s216374,Dibi Kenzo s210122 Group 12
 * \date: 10/05/2022
 * project: INFO0030 Project 4
 */

/**
 * include guard to avoid the problems due to  multiple inclusions
 */
#ifndef __CONTROLLER_CONNECT4__
#define __CONTROLLER_CONNECT4__

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "model-connect4.h"
#include "view-connect4.h"

/**
 * \brief the game board's minimun size
 */
#define MIN_SIZE 4

/**
 * \struct controller_t
 * \brief the controller
 */
typedef struct controller_t CONTROLLERCONNECT4;

/**
 * \fn CONTROLLERCONNECT4 *create_controller(VIEWCONNECT4 *VC4, MODELCONNECT4 *MC4)
 * \brief creates the game controller
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre  VC4 != NULL && MC4 != NULL
 * \post the controller has been created
 * 
 * \return  CC4 or NULL
 */
CONTROLLERCONNECT4 *create_controller(void *VC4, MODELCONNECT4 *MC4);

/**
 * \fn void destroy_controller(CONTROLLERCONNECT4 *CC4)
 * \brief destroys the model
 * \param CC4 a pointer to CONTROLLERCONNECT4
 * \pre CC4 != NULL
 * \post the model has been destroyed
 */
 void destroy_controller(CONTROLLERCONNECT4 *CC4);

/**
 * \fn  void destroy_buttons(CONTROLLERCONNECT4 *CC4)
 * \brief destroys the buttons
 * \param CC4 a pointer to CONTROLLERCONNECT4
 * \pre CC4 != NULL
 * \post the buttons has been destroyed
 */
 void destroy_buttons(CONTROLLERCONNECT4 *CC4);

/**
 * \fn CONTROLLERCONNECT4 *create_menu(GtkWidget *pWindow, CONTROLLERCONNECT4 *CC4)
 * \brief creates the menu and all the sub menus
 * 
 * \param pWindow a pointer to GtkWidget
 * \param CC4 a pointer to CONTROLLERCONNECT4
 * 
 * \pre pWidnow != NULL
 * \post the menus have been added to the window
 * \return menuBar
 */
CONTROLLERCONNECT4 *create_menu(GtkWidget *pWindow, CONTROLLERCONNECT4 *CC4);

/**
 * \fn void click_board_button(GtkWidget* pWindow, gpointer data)
 * \brief puts a pawn in the selected row
 * \param pWidnow a pointer to GtkWidget
 * \param data a pointer to the controller
 * \pre pWindonw != NULL
 * \post
 */
void click_board_button(GtkWidget *pWindow, gpointer data);

/**
 * \fn void new_game(GtkWidget *pWindow, gpointer data)
 * \brief starts a new game
 * \param pWidnow a pointer to GtkWidget
 * \param data a pointer to the controller
 * \pre pWindonw != NULL
 * \post a new game has started
 */
void new_game(GtkWidget *pWindow, gpointer data);

/**
 * \fn void best_scores(GtkWidget *pWindow, gpointer data)
 * \brief creates a popup with a list of the top 10 players
 * 
 * \param pWidnow a pointer to GtkWidget
 * \param data a pointer to the controller
 * 
 * \pre pWindonw != NULL
 * \post the best scores are shown
 */
//void best_scores(GtkWidget *pWindow, gpointer data);

/**
 * \fn void about(GtkWidget *pWindow, gpointer data)
 * \brief shows the credits
 * 
 * \param pWidnow a pointer to GtkWidget
 * \param data a gpointer
 * 
 * \pre pWindonw != NULL
 * \post the credits are shown
 */
void about(GtkWidget *pWindow, gpointer data);

/**
 * \fn void rules(GtkWidget *pWindow, gpointer data)
 * \brief shows the rules
 * 
 * \param pWidnow a pointer to GtkWidget
 * \param data a gpointer
 * 
 * \pre pWindonw != NULL
 * \post the rules are shown
 */
void rules(GtkWidget *pWindow, gpointer data);

/**
 * \fn void best_scores(GtkWidget *pWindow, gpointer data)
 * \brief show the top ten scores
 * 
 * \param pWidnow a pointer to GtkWidget
 * \param data a gpointer
 * 
 * \pre pWindonw != NULL
 * \post the best scores are shown
 */
void best_scores(GtkWidget *pWindow, gpointer data);

/**
 * \fn GtkWidget *get_button(CONTROLLERCONNECT4 *CC4, int column)
 * \brief return the address to the button
 * 
 * \param CC4 a pointer to CONTROLLERCONNECT4
 * \param column the column wher the button is located
 * \pre CC4 != NULL && column >= 0
 * 
 * \post the button has been returned
 * 
 * \return pWindow
 */
GtkWidget *get_button(CONTROLLERCONNECT4 *cC4, int column);
#endif