/**
 * \file codeBarre.h
 * 
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la manipulation des codes barres.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 4/04/2022
 * projet: INFO0030 Projet 2
 */

#ifndef __CODEBARRE__
#define __CODEBARRE__

#include "pnm.h"

/**
 * \brief Le nombre de case maximale d'un tableau
 */
#define N 1000

/**
 * \brief The default size of a qrcode
 */
#define SIZE_MINI_MATRIX 7

/**
 * \brief the upscaled size of a qrcode
 */
#define SIZE_MATRIX 70

/**
 * \brief the maximum encodable number
 */
#define MAX_REG_NUMBER 99999999

/**
 * \brief the minimum encodable number
 */
#define MIN_REG_NUMBER 00000000

/**
 * \brief the maxium size of an array of char
 */
#define MAX_CHAR 10001

/**
 * \brief the number of characters needed for the format of the output file 
 */
#define FILE_EXTENSION 4

/**
 * \brief the number of characters needed for the name of the output file
 */
#define SIZE_REG 8

/**
 * \fn int generate_qrcode(PNM **qrcode, char *filename, char* output)
 *
 * \brief generates a 70x70 qrcode for all the registration numbers contained in filename
 * \param qrcode a pointer to the PNM_t structure.
 * \param filename the name of the file containing the the registration numbers
 * \param output the folder that will contain the QR codes
 * \pre: qrcode != NULL && filename != NULL && output != NULL.
 * \post: The qrcodes have been created.
 *
 * \return:
 *      0 succes
 *     -1 failure
 *
 *
 */
int generate_qrcode(PNM **qrcode, char *filename, char* output);

/**
 * \fn int fix_qrcode(PNM **qrcode, char* input, char* output)
 *
 * \brief a pointer to the PNM_t structure.
 * \param qrcode 
 * \param input the qrcode that needs to be fixed
 * \param output the fixed qrcode
 * \pre:  qrcode != NULL && input != NULL && output != NULL
 * \post: 
 *
 * \return:
 *      0 succes
 *     -1 failure
 *
 *
 */
int fix_qrcode(PNM **qrcode, char* input, char* output);


#endif