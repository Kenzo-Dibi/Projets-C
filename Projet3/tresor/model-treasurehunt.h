/**
 * \file model-treasurehunt.h
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
#ifndef __MODEL_TREASUREHUNT__
#define __MODEL_TREASUREHUNT__

/**
 * \struct model_t
 * \brief Opaque definition of type TREASUREHUNTMODEL
 */
typedef struct model_t TREASUREHUNTMODEL;
/**
 * \struct score
 * \brief A structure containing the current score;
 */
typedef struct score{
   unsigned int wins;/*!< The current number of wins */
   unsigned int losses;/*!< The current number of loss */
}SCORE;

/**
 * \fn TREASUREHUNTMODEL* create_treasurehunt_model(void)
 * \brief Creates the model for the treasurehunt.
 * \pre /
 * \post the model has been created
 */
TREASUREHUNTMODEL* create_treasurehunt_model(void);
/**
 * \fn TREASUREHUNTMODEL* increment_wins(TREASUREHUNTMODEL* thm)
 * \brief increments the number of wins
 * \param thm a pointer to TREASUREHUNTMODEL
 * \pre: thm != NULL
 * \post: The number of wins has been incremented by one.
 * \return:
 *    thm
 */
TREASUREHUNTMODEL* increment_wins(TREASUREHUNTMODEL* thm);

/**
 * \fn TREASUREHUNTMODEL* increment_losses(TREASUREHUNTMODEL* thm)
 * \brief increments the number of losses
 * \param thm a pointer to TREASUREHUNTMODEL
 * \pre: thm != NULL
 * \post: The number of losses has been incremented by one.
 * \return:
 *    thm
 */
TREASUREHUNTMODEL* increment_losses(TREASUREHUNTMODEL* thm);

/**
 * \fn TREASUREHUNTMODEL* set_wins_score(TREASUREHUNTMODEL* thm, int numberWins)
 * \brief Sets the number of wins to a certain value?
 * \param thm a pointer to TREASUREHUNTMODEL
 * \param numberWins the wanted value
 * \pre: thm != NULL && numberWins >= 0
 * \post: The number of wins has been set to "numberWins".
 * \return:
 *    thm
 */
TREASUREHUNTMODEL* set_wins_score(TREASUREHUNTMODEL* thm, int numberWins);

/**
 * \fn TREASUREHUNTMODEL* set_losses_score(TREASUREHUNTMODEL* thm, int numberLosses)
 * \brief Sets the number of wins to a certain value?
 * \param thm a pointer to TREASUREHUNTMODEL
 * \param numberLosses the wanted value
 * \pre: thm != NULL && numberLosses >= 0
 * \post: The number of wins has been set to "numberLosses".
 * \return:
 *    thm
 */
TREASUREHUNTMODEL* set_losses_score(TREASUREHUNTMODEL* thm, int numberLosses);

/**
 * \fn unsigned int get_wins_score(TREASUREHUNTMODEL* thm)
 * \brief Gives the number current number of wins.
 * \param thm a pointer to TREASUREHUNTMODEL
 * \pre: thm != NULL
 * \post: The number of wins is returned.
 * \return:
 *       thm
 */
unsigned int get_wins_score(TREASUREHUNTMODEL* thm);

/**
 * \fn unsigned int get_losses_score(TREASUREHUNTMODEL* thm)
 * \brief Gives the number current number of losses.
 * \param thm a pointer to TREASUREHUNTMODEL
 * \pre: thm != NULL
 * \post: The number of losses is returned.
 * \return:
 *       thm
 */
unsigned int get_losses_score(TREASUREHUNTMODEL* thm);

/**
 * \fn void destroy_model(TREASUREHUNTMODEL* thm)
 * \brief frees a variable of type TREASUREHUNTMODEL.
 * \param thm a pointer to TREASUREHUNTMODEL
 * \pre: thm != NULL
 * \post: The variable is freed.
 * \return:
 *       thm
 */
void destroy_model(TREASUREHUNTMODEL* thm);
#endif