/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: Dibi Kenzo s210122
 * @date: 18/03/2022
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__



/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * Enumartion for the magic number
 *
 */
typedef enum{P1, P2, P3}MagicNumber;

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);


/**
 * free_pnm
 *
 * frees a variable of type PNM.
 * @param image a pointer on PNM.
 *
 * @pre: image != NULL
 * @post: image has been freed.
 *
 * @return: /
 *
 *
 */
void free_pnm(PNM *image);

/**
 * load_feedback
 *
 * Gives the feedback of the load_pnm function
 * @param result the result.
 *
 * @pre: The result is an integer
 * @post: The success or error message is shown.
 *
 * @return: /
 *
 *
 */
void load_feedback(int result);

/**
 * write_feedback
 *
 * Gives the feedback of the write_pnm function
 * @param result
 *
 * @pre: the result is an integer
 * @post: The success or error message is shown on screen
 *
 * @return: /
 *
 *
 */
void write_feedback(int result);

/**
 * formatFeedback
 *
 * Gives feedback on the input format and the input file format
 * @param result
 *
 * @pre: result is an integer
 * @post: The success or error message is shown on screen
 *
 * @return:/
 *
 *
 */
void format_feedback(int result);

/**
 * verify_format
 *
 * Verifies if the input format and the input file format matches.
 * @param inputFormat -f's argument
 * @param inputFileformat -i's argument
 *
 * @pre: inputFormat != NULL && inputFileformat != NULL
 * @post: the result is returned.
 *
 * @return:
 *      0: success
 *     -1: failure
 *
 *
 */
int verify_format(char *inputFormat, char *inputFileformat);

/**
 * get_type
 *
 * Stocks the extension of the image.
 * @param inputFormat format container
 * @param inputFileFormat the format argument
 *
 * @pre: inputFormat != NULL && inputFileformat != NULL
 * @post: inputFormat contains the extension of the image
 *
 * @return: /
 *
 *
 */
void get_type(char **inputFormat, char *inputFileformat);

/**
 * verify_filename
 *
 * Checks is the file name doesnt contain unauthorized characters.
 * @param outputFilename
 *
 * @pre: outputFilename != NULL
 * @post: /
 *
 * @return:
 *      0: the filename is written correctly
 *     -1: the filename contains unauthorized characters
 *
 *
 */
int verify_filename(char *outputFilename);

/**
 * filename_feedback
 *
 * Gives the feedback on the output file name
 * @param result
 *
 * @pre: result is an integer
 * @post: error message
 *
 * @return: /
 *
 *
 */
void filename_feedback(int result);

#endif // __PNM__
