/**
 * \file view-connect4.h
 * 
 * \brief This file contains the type definitions and for the Connect 4 game.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 16/07/2022
 * project: INFO0030 Projet 4
 */

/**
 * Include guards to prevent include multiple times the same elements
 */
#ifndef __VIEW_CONNECT4__
#define __VIEW_CONNECT4__

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <stdlib.h>

#include "model-connect4.h"
#include "controller-connect4.h"

/**
 * \brief the default image size
 */
#define IMG_SIZE 80

/**
 * \brief the size of the window
 */
#define CUSTOM_WINDOW_SIZE 0

/**
 * \struct view_t
 * \brief the view
 */
typedef struct view_t VIEWCONNECT4;

/**
 * \fn VIEWCONNECT4 *create_view(MODELCONNECT4 *MC4)
 * \brief creates the view
 * 
 * \param MC4 a pointer to MODELCONNECT4
 * 
 * \pre MC4 != NULL
 * \post the view has been created
 */
VIEWCONNECT4 *create_view(MODELCONNECT4 *MC4);

/**
 * \fn void destroy_view(VIEWCONNECT4 *VC4)
 * \brief destroys the view
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * 
 * \pre VC4 != NULL
 * \post the view has been destroyed
 */
void destroy_view(VIEWCONNECT4 *VC4);

/**
 * \fn GtkWidget *create_window(void)
 * \brief creates the game's window
 * 
 * \param void
 * 
 * \pre /
 * \post the window has been created
 * \return the window (pW)
 */
GtkWidget *create_window(void);

/**
 * \fn GtkWidget *get_window(VIEWCONNECT4 *VC4)
 * \brief return the address to the window
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \pre VC4 != NULL
 * 
 * \post the window has been returned
 * 
 * \return pWindow
 */
GtkWidget *get_window(VIEWCONNECT4 *VC4);

/**
 * \fn GtkWidget *load_image(char *image)
 * \brief puts an image on top of a GtkWidget
 * 
 * \param image the path to the image
 * 
 * \pre image != NULL
 * \post the image is loaded onto the board
 * 
 * \return -1 : error,
 *         image : success
 */
GtkWidget *load_image(char *image);

/**
 * \fn void update_image(GtkWidget *pCase,char *image)
 * \brief updates an image on the board
 * 
 * \param pCase the widget that needs to be updated
 * \param image the path to the image
 * 
 * \pre case != NULL &&image != NULL
 * \post the newimage is loaded onto the board
 * 
 * \return -1 : error,
 *         image : success
 */
void update_image(GtkWidget *pCase,char *image);

/**
 * \fn GtkWidget ***create_board(VIEWCONNECT4 * VC4)
 * \brief create the matrix showing the in the window
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \pre VC4 != NULL
 * \post the matrix has been created
 * 
 * \return visualBoard || NULL
 */
GtkWidget ***create_board(VIEWCONNECT4 * VC4);

/**
 * \fn GtkWidget ***get_board(VIEWCONNECT4 *VC4)
 * \brief give the address of the matrix
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \pre VC4 != NULL
 * \post the board has been returned
 * 
 * \return visualBoard
 */
GtkWidget ***get_board(VIEWCONNECT4 *VC4);

/**
 * \fn void free_board(VIEWCONNECT4 *VC4)
 * \brief frees the matrix in the view
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \pre VC4 != NULL
 * \post the matrix has been freed
 */
void free_board(VIEWCONNECT4 *VC4);

/**
 * \fn GtkWidget *get_vbox(VIEWCONNECT4 *VC4)
 * \brief returns the view's vbox
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \pre VC4 != NULL
 * \post the vbox has been returned
 */
GtkWidget *get_vbox(VIEWCONNECT4 *VC4);

/**
 * \fn GtkWidget **get_hbox(VIEWCONNECT4 *VC4, int line)
 * \brief returns the view's hbox
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * \param line the position of the hbox
 * \pre VC4 != NULL
 * \post the hbox has been returned
 */
GtkWidget *get_hbox(VIEWCONNECT4 *VC4, int line);

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
 * \fn void update_board(VIEWCONNECT4 *VC4)
 * \brief updates the board so that it reflects the current state of the game
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * 
 * \pre VC4 != NULL
 * \post the board has updated
 */
void update_board(VIEWCONNECT4 *VC4);

/**
 * \fn void create_board_box(VIEWCONNECT4 *VC4)
 * \brief creates a the box containing the board
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * 
 * \pre VC4 != NULL
 * \post the board has updated
 */
void create_board_box(VIEWCONNECT4 *VC4);

/**
 * \fn GtkWidget *create_about(void)
 * \brief creates the about window
 * 
 * \param void
 * 
 * \post the about section has been creted
 */
void create_about(void);

/**
 * \fn void create_rule(void)
 * \brief creates the rule window
 * 
 * \param void
 * 
 * \post the rule section has been creted
 */
void create_rule(void);

/**
 * \fn void create_best_scores()
 * \brief creates the rule window
 * 
 * \param VC4 a pointer to VIEWCONNECT4
 * 
 * \post the 'best scores' section has been creted
 */
void create_best_scores(VIEWCONNECT4 *VC4);
#endif
