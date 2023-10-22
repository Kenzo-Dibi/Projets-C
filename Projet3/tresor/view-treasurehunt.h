/**
 * \file view-treasurehunt.h
 * 
 * \brief This file contains the type definitions and functions for the treasure hunt program.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 19/04/2022
 * projet: INFO0030 Projet 3
 */

/**
 * \brief Include guards to prevent include multiple times the same elements
 */
#ifndef __VIEW_TREASUREHUNT__
#define __VIEW_TREASUREHUNT__

#include <gtk/gtk.h>
#include "model-treasurehunt.h"
#include "controller-treasurehunt.h"

/**
 * \struct view_t
 * \brief Opaque definition of type VIEWTREASUREHUNT.
 */
typedef struct view_t VIEWTREASUREHUNT;

/**
 * \fn VIEWTREASUREHUNT* create_treasurehunt_view(TREASUREHUNTMODEL* thm)
 * \brief Creates the view for the treasurehunt based on a certain model.
 * \param thm the model
 * \pre thm != NULL
 * \post The treasurehunt view has been created.
 * \return
 *      vt the view
 */
VIEWTREASUREHUNT* create_treasurehunt_view(TREASUREHUNTMODEL* thm);

/**
 * \fn VIEWTREASUREHUNT *redraw_score(VIEWTREASUREHUNT* vt)
 * \brief Refreshes the current score.
 * \param vt the view
 * \pre vt != NULL
 * \post The score has been updated
 * \return
 *      vt the view
 */
VIEWTREASUREHUNT *redraw_score(VIEWTREASUREHUNT* vt);

/**
 * \fn GtkWidget *get_label(VIEWTREASUREHUNT *vt, int number)
 * \brief parses a label in in a VIEWTREASUREHUNT variable.
 * \param vt the view
 * \param number the wanted label
 * \pre vt != NULL && number >= 0 && number < 2
 * \post The label has been parsed.
 * \return
 *       vt->pLabel[number]
 */
GtkWidget *get_label(VIEWTREASUREHUNT *vt, int number);

/**
 * \fn void destroy_view(VIEWTREASUREHUNT* vt)
 * \brief frees a variable of type VIEWTREASUREHUNT.
 * \param vt the view
 * \pre vt != NULL
 * \post The  variable has been freed.
 */
void destroy_view(VIEWTREASUREHUNT* vt);
#endif