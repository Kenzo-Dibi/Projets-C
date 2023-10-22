/**
 * \file controller-treasurehunt.h
 * 
 * \brief This file contains the type definitions and functions for the treasure hunt program.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 19/04/2022
 * projet: INFO0030 Projet 3
 */

/**
 * Include guards to prevent include multiple times the same elements
 */
#ifndef __CONTROLLER_TREASUREHUNTER__
#define __CONTROLLER_TREASUREHUNTER__

#include <gtk/gtk.h>

#include "model-treasurehunt.h"
#include "view-treasurehunt.h"

/**
 * \brief The number of chests the game has.
 */
#define NUMBER_CHEST 3
/**
 * \brief The size of the images contained in the buttons.
 */
#define IMG_SIZE 100

/**
 * \brief The size of the images contained in the buttons.
 */
#define FIRST 0

/**
 * \brief The size of the images contained in the buttons.
 */
#define SECOND 1

/**
 * \brief The size of the images contained in the buttons.
 */
#define THIRD 2

/**
 * \enum chestcontent
 * \brief  Enumaration of the chests content.
 */
typedef enum chestcontent{empty /*!< empty chest*/, gold /*!< chest full of gold */}CHESTCONTENT;

/**
 * \enum cheststate
 * \brief Enumaration of the state of the chest (open/unopened)
 */
typedef enum cheststate{unopened  /*!< unopened chest*/, opened /*!< opened chest */}CHESTSTATE;

/**
 * \struct chest
 * \brief The structure used to represent a chest.
 */
typedef struct chest{
   CHESTCONTENT content; /*!< the content of the chest (empty/gold)*/
   CHESTSTATE state; /*!< the state of the chest (opened/unopened) */
   GtkWidget *pChest; /*!< The chest */
}CHEST;

/**
 * \struct controller_t
 * \brief Implementation of Treasurehunt controller.
 */
typedef struct controller_t TREASUREHUNTCONTROLLER;

/**
 * \fn TREASUREHUNTCONTROLLER* create_treasurehunt_controller(VIEWTREASUREHUNT *thv, TREASUREHUNTMODEL* thm)
 * \brief creates the controller
 * \param thv  the view of the treasure hunt to be used.
 * \param thm the model of the treasure hunt to be used.
 * \pre thv != NULL && thm != NULL
 * \post the controller has been created.
 * \return
 *       thc the controller
 */
TREASUREHUNTCONTROLLER* create_treasurehunt_controller(VIEWTREASUREHUNT *thv, TREASUREHUNTMODEL* thm);

/**
 * \fn void restart_click(GtkWidget* pW, gpointer data)
 * \brief links the restart button and the restart action
 * \brief the button used to start a new game
 * \param pW the window
 * \param data a pointer to the controller
 * \pre pW != NULL
 * \post a new game has started
 */
void restart_click(GtkWidget* pW, gpointer data);

/**
 * \fn void click_first_chest(GtkWidget* pW, gpointer data)
 * \brief opens the first chest or a random chest
 * \param pW the window
 * \param data a pointer to the controller
 * \pre pW != NULL
 * \post one the two other chest has been opened
 */
void click_first_chest(GtkWidget* pW, gpointer data);

/**
 * \fn void click_second_chest(GtkWidget* pW, gpointer data)
 * \brief opens the second chest or a random chest
 * \param pW the window
 * \param data a pointer to the controller
 * \pre pW != NULL
 * \post one the two other chest has been opened
 */
void click_second_chest(GtkWidget* pW, gpointer data);

/**
 * \fn void click_third_chest(GtkWidget* pW, gpointer data)
 * \brief opens the thirdd chest or a random chest
 * \param pW the window
 * \param data a pointer to the controller
 * \pre pW != NULL
 * \post one the two other chest has been opened
 */
void click_third_chest(GtkWidget* pW, gpointer data);

/**
 * \fn GtkWidget *get_chest(TREASUREHUNTCONTROLLER *thc, int number)
 * \brief returns the chest
 * \param thc a pointer to TREASUREHUNTCONTROLLER
 * \param number the wanted chest (first, second or third)
 * \pre thc != NULL && number >= 0 & number < 3
 * \post the chest button is returned
 * \return
 *    thc->chest[number].pChest the chest
 */
GtkWidget *get_chest(TREASUREHUNTCONTROLLER *thc, int number);

/**
 * \fn GtkWidget *get_restart(TREASUREHUNTCONTROLLER *thc)
 * \brief returns the restart button
 * \param thc a pointer to TREASUREHUNTCONTROLLER
 * \pre thc != NULL
 * \post the restart button is returned
 * \return
 *    thc->restart the restart button
 */
GtkWidget *get_restart(TREASUREHUNTCONTROLLER *thc);

/**
 * \fn GtkWidget *get_state_label(TREASUREHUNTCONTROLLER *thc, int number)
 * \brief
 * \param thc a pointer to TREASUREHUNTCONTROLLER
 * \param number the wanted label (score/game state)
 * \pre thc != NULL && number >= && number < 2
 * \post the restart button is returned
 * \return
 *    get_label(thc->thv, number)
 */
GtkWidget *get_state_label(TREASUREHUNTCONTROLLER *thc, int number);

/**
 * \fn void destroy_controller(TREASUREHUNTCONTROLLER* thc)
 * \brief frees the controller
 * \param thc a pointer to TREASUREHUNTCONTROLLER
 * \pre thc != NULL
 * \post the controller has been freed
 */
void destroy_controller(TREASUREHUNTCONTROLLER* thc);
#endif