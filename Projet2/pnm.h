/**
 * \file pnm.h
 * 
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la manipulation d'images PNM.
 * 
 * \author: Dibi Kenzo s210122
 * \date: 4/04/2022
 * projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * \struct PNM_t
 * \brief Déclaration du type opaque PNM
 */
typedef struct PNM_t PNM;

/**
 * \enum magicnumber
 * \brief Enumaration for the magic number
 */
typedef enum magicnumber{P1, P2, P3}MagicNumber;

/**
 * \fn int load_pnm(PNM **image, char* filename)
 *
 * \brief Charge une image PNM depuis un fichier.
 *
 * \param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse de l'image chargée.
 * \param filename le chemin vers le fichier contenant l'image.
 *
 * \pre: image != NULL, filename != NULL
 * \post: image pointe vers l'image chargée depuis le fichier.
 *
 * \return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * \fn int write_pnm(PNM *image, char* filename)
 *
 * \brief Sauvegarde une image PNM dans un fichier.
 *
 * \param image un pointeur sur PNM.
 * \param filename le chemin vers le fichier de destination.
 *
 * \pre: image != NULL, filename != NULL
 * \post: le fichier filename contient l'image PNM image.
 *
 * \return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * \fn void free_pnm(PNM *image)
 *
 * \brief frees a variable of type PNM.
 * \param image a pointer on PNM.
 *
 * \pre: image != NULL
 * \post: image has been freed.
 *
 * \return: /
 *
 *
 */
void free_pnm(PNM *image);

/**
 * \fn void load_feedback(int result)
 *
 * \brief Gives the feedback of the load_pnm function
 * \param result the result.
 *
 * \pre: The result is an integer
 * \post: The success or error message is shown.
 *
 * \return: /
 *
 *
 */
void load_feedback(int result);

/**
 * \fn void write_feedback(int result)
 *
 * \brief Gives the feedback of the write_pnm function
 * \param result
 *
 * \pre: the result is an integer
 * \post: The success or error message is shown on screen
 *
 * \return: /
 *
 *
 */
void write_feedback(int result);

/**
 * \fn void format_feedback(int result)
 *
 * \brief Gives feedback on the input format and the input file format
 * \param result
 *
 * \pre: result is an integer
 * \post: The success or error message is shown on screen
 *
 * \return:/
 *
 *
 */
void format_feedback(int result);

/**
 * \fn int verify_format(char *inputFormat, char *inputFileformat)
 *
 * \brief Verifies if the input format and the input file format matches.
 * \param inputFormat -f's argument
 * \param inputFileformat -i's argument
 *
 * \pre: inputFormat != NULL && inputFileformat != NULL
 * \post: the result is returned.
 *
 * \return:
 *      0: success
 *     -1: failure
 *
 *
 */
int verify_format(char *inputFormat, char *inputFileformat);

/**
 * \fn void get_type(char **inputFormat, char *inputFileformat)
 *
 * \brief Stocks the extension of the image.
 * \param inputFormat format container
 * \param inputFileformat the format argument
 *
 * \pre: inputFormat != NULL && inputFileformat != NULL
 * \post: inputFormat contains the extension of the image
 *
 * \return: /
 *
 *
 */
void get_type(char **inputFormat, char *inputFileformat);

/**
 * \fn int **allocate_matrix(int lines,int columns)
 *
 * \brief allocates a matrix
 *
 * \param lines the number of lines the matrix will have.
 * \param columns the number of columns the matrix will have.
 * \author Mr.Donnet
 * \pre: lines > 0 && columns > 0
 * \post: the matrix has been created
 *
 * \return:the matrix
 *
 *
 */
int **allocate_matrix(int lines,int columns);

/**
 * \fn int verify_filename(char *outputFilename)
 *
 * \brief Checks is the file name doesnt contain unauthorized characters.
 * \param outputFilename the filename that'll be verfied
 *
 * \pre: outputFilename != NULL
 * \post: /
 *
 * \return:
 *      0: the filename is written correctly
 *     -1: the filename contains unauthorized characters
 *
 *
 */
int verify_filename(char *outputFilename);

/**
 * \fn void filename_feedback(int result)
 *
 * \brief Gives the feedback on the output file name
 * \param result
 *
 * \pre: result is an integer
 * \post: error message
 *
 * \return: /
 *
 *
 */
void filename_feedback(int result);

/**
 * \fn PNM* create_pnm(void)
 *
 * \brief allocates a point to the PNM structure
 * \param void no argument is taken
 * 
 * \pre: /
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
PNM* create_pnm(void);

/**
 * \fn PNM get_pnm(PNM* image)
 *
 * \brief accessor to the PNM structure
 * \param image a pointer to PNM.
 *
 * \pre: image != NULL
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
PNM* get_pnm(PNM* image);

/**
 * \fn PNM* set_magicnumber(PNM* image, MagicNumber magicNumber)
 *
 * \brief accessor to the PNM structure
 * \param image a pointer to PNM.
 * \param magicNumber an enmuartion containing the magic number.
 *
 * \pre: image != NULL && (magicNumber == P3 || magicNumber == P2 || magicNumber == P1)
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
PNM* set_magicnumber(PNM* image, MagicNumber magicNumber);

/**
 * \fn PNM* set_lines_columns(PNM* image, int size)
 *
 * \brief  accessor to the PNM structure
 * \param image a pointer to PNM.
 * \param size the the lines and columns of the matrix will be set to.
 *
 * \pre: image != NULL && size > 0
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
PNM* set_lines_columns(PNM* image, int size);

/**
 * \fn PNM* set_value_matrix(PNM* image, int** binaryNumber,  int lines, int columns)
 *
 * \brief accessor to the PNM structure
 * \param image a pointer to PNM.
 * \param binaryNumber the matrix containing a number reprensented in binary.
 * \param lines the number of lines the matrix has.
 * \param columns the number of columns the matrix has.
 *
 * \pre: image != NULL && binaryNumber != NULL && lines > 0 && columns > 0
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
PNM* set_value_matrix(PNM* image, int** binaryNumber,  int lines, int columns);

/**
 * \fn void destroy_matrix(PNM* image)
 *
 * \brief frees a pointer to the PNM structure
 * \param image a pointer to PNM.
 *
 * \pre: image != NULL
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
void destroy_matrix(PNM* image);

/**
 * \fn PNM* create_matrix(PNM* image, int lines ,int columns)
 *
 * \brief frees a pointer to the PNM structure
 * \param image a pointer to PNM.
 * \param lines the number of lines wanted for the matrix
 * \param columns the number of columns wanted for the matrix
 * \pre: image != NULL && lines > 0 && columns > 0
 * \post: /
 *
 * \return: NULL or the allocated zone
 *
 *
 */
PNM* create_matrix(PNM* image, int lines ,int columns);

/**
 * \fn int get_value_matrix(PNM* qrcode, int lines, int columns)
 *
 * \brief gives the value of the element contained at matrix[lines][columns]
 * \param qrcode a pointer to PNM.
 * \param lines the number of lines the matrix has
 * \param columns the number of columns the matrix has
 * \pre: qrcode != NULL && lines > 0 && columns > 0
 * \post: /
 *
 * \return: the value of matrix[lines][columns] is returned
 *
 *
 */
int get_value_matrix(PNM* qrcode, int lines, int columns);

/**
 * \fn MagicNumber get_magic_number(PNM* qrcode)
 *
 * \brief gives the magic numbe of qrcode, a pointer to PNM
 * \param qrcode a pointer to PNM.
 * \pre: qrcode != NULL
 * \post: /
 *
 * \return: the magic number is returned
 *
 *
 */
MagicNumber get_magic_number(PNM* qrcode);

/**
 * \fn int get_lines(PNM* qrcode)
 *
 * \brief gives the field lines of qrcode, a pointer to PNM
 * \param qrcode a pointer to PNM.
 * \pre: qrcode != NULL
 * \post: /
 *
 * \return: the field lines is returned
 *
 *
 */
int get_lines(PNM* qrcode);

/**
 * \fn int get_columns(PNM* qrcode)
 *
 * \brief gives the field columns of qrcode, a pointer to PNM
 * \param qrcode a pointer to PNM.
 * \pre: qrcode != NULL
 * \post: /
 *
 * \return: the field columns is returned
 *
 *
 */
int get_columns(PNM* qrcode);

/**
 * \fn void free_matrix(int **matrix, int size)
 *
 * \brief gives the field columns of qrcode, a pointer to PNM
 * \param matrix a 2d array
 * \param size the size of the matrix (size x size)
 * \pre: matrix != NULL
 * \post: /
 *
 * \return: the matrix has been freed
 *
 *
 */
void free_matrix(int **matrix, int size);

#endif // __PNM__
